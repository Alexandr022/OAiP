#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define LENGTH 256

FILE* logOutput;

void logOpen(const char* file);

void createLog(const char* format, ...);