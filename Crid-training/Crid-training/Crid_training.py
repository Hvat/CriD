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
