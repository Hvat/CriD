//+------------------------------------------------------------------+
//|                                                     DLL for CriD |
//|                                  Copyright 2019, Artem Evdokimov |
//|                                                  obhvat@inbox.ru |
//+------------------------------------------------------------------+
#include "stdafx.h"
//+------------------------------------------------------------------+
void convertSystemString(wchar_t* dest, const char* src)
{
	if (src != nullptr)
	{
		memcpy(dest, src, strnlen(src, 1000) * sizeof(const char));
		dest[strnlen(src, 1000)] = L'\0';
	}
	else
	{
		dest[0] = L'\0';
	}
}
//+------------------------------------------------------------------+
_DLLAPI void _stdcall ArrayResponse(float& Res, float* Arr, const int arr_size,  wchar_t* modelFile, wchar_t* err)
{
	try
	{
		Res = 0;
		// Выбор устройства (CPU или GPU)
		const DeviceDescriptor& device = DeviceDescriptor::CPUDevice();
		// Загрузка обученой модели
		FunctionPtr modelFunc = Function::Load(modelFile, device);
		// Получение входной переменной. Модель имеет только один вход.
		Variable inputVar = modelFunc->Arguments()[0];
		// Модель имеет только один выход.
		Variable outputVar = modelFunc->Output();
		// В цикле из входящего массива передаем данные входного вектора 
		std::vector<float> inputData(inputVar.Shape().TotalSize());
		for (size_t i = 0; i < arr_size; ++i)
		{
			inputData[i] = Arr[i];
		}
		// Создание карты входных данных
		ValuePtr inputVal = Value::CreateSequence(inputVar.Shape(), inputData, device);
		std::unordered_map<Variable, ValuePtr> inputDataMap = {{inputVar, inputVal}};
		// Использование null в качестве значения для указания использования системной памяти.
		std::unordered_map<Variable, ValuePtr> outputDataMap = {{outputVar, nullptr}};
		// Запуск функции прогноза
		modelFunc->Evaluate(inputDataMap, outputDataMap, device);
		// Получение результата
		ValuePtr outputVal = outputDataMap[outputVar];
		std::vector<std::vector<float>> outputData;
		outputVal->CopyVariableValueTo(outputVar, outputData);
		// Передача результата
		for (size_t i = 0; i < outputData.size(); i++)
		{
			auto res = outputData[i];
			for (size_t j = 0; j < res.size(); j++)
			{
				Res = res[0];
			}

		}
	}
	catch (const std::exception& e)
	{
		convertSystemString(err, e.what());
	}
}
//+------------------------------------------------------------------+