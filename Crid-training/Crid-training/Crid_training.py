#-------------------
from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
import time
from sklearn.preprocessing import MinMaxScaler
from datetime import datetime
import MetaTrader5 as mt5
import pytz
import cntk as C
import cntk.tests.test_utils
cntk.tests.test_utils.set_device_from_pytest_env()
np.random.seed(0)

# Global variables
EXPORT_BARS = 6720
INPUT_DIM = 72
OUTPUT_DIM = 1
SIZE = INPUT_DIM + OUTPUT_DIM
EPOCHS = 1000
LOSS = 0.00038
LEARNING_RATE = 0.1

# display data about the MetaTrader 5 package
print("MetaTrader5 package author: ", mt5.__author__)
print("MetaTrader5 package version: ", mt5.__version__)
print("----------------------------")
print("CNTK package version: ", cntk.__version__)

# establish a connection to the MetaTrader 5 terminal
if not mt5.initialize():
    print("initialize() failed")
    quit()

# set the timezone to UTC
timezone = pytz.timezone("Etc/UTC")

# create a datetime object in the UTC timezone
utc_from = datetime(2019, 1, 11, tzinfo=timezone)

# get data on the selected instrument
rates = mt5.copy_rates_from("ED Splice", mt5.TIMEFRAME_M30, utc_from, EXPORT_BARS)

# finish connecting to the MetaTrader 5 terminal
mt5.shutdown()

# Data generation
def generate_data(data_source, input, output):

	values = data_source['close']
	
	start = input
	end = len(values) - output

	raw_data = []
	for i in range(start, end):
	   input_output = values[(i - input):(i + output)]
	   raw_data.append(list(input_output))
	
	input_columns = []
	for i in range(input):
		input_columns.append("input_{}".format(i))

	output_columns = []
	for i in range(output):
		output_columns.append("output_{}".format(i))

	scaler = MinMaxScaler(feature_range=(-1, 1))
	raw_data = scaler.fit_transform(raw_data)

	df = pd.DataFrame(raw_data, columns = (input_columns + output_columns), dtype = np.float32)

	X = df[input_columns]
	Y = df[output_columns]

	X = np.array(X)
	Y = np.array(Y)

	X = np.array([X])
	Y = np.array([Y])

	return X, Y

X, Y = generate_data(rates, INPUT_DIM, OUTPUT_DIM)

