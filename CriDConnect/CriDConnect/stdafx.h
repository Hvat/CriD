//+------------------------------------------------------------------+
//|                                                     DLL for CriD |
//|                                  Copyright 2019, Artem Evdokimov |
//|                                                  obhvat@inbox.ru |
//+------------------------------------------------------------------+
#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // "secure" CRT недоступен на всех платформах
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN     // Исключите редко используемые компоненты из заголовков Windows

// Файлы заголовков Windows
#include <windows.h>
#include <cstdio>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CNTKLibrary.h"
using namespace CNTK;
//---
#define _DLLAPI extern "C" __declspec(dllexport)
//+------------------------------------------------------------------+