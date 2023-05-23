// log.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "log.h"

FILE* logOutput;

void logOpen(char* file)
{
    logOutput = fopen(file, "w");
}

void createLog(char* format, ...)
{
    time_t now = time(NULL);
    char buffer[26];
    struct tm* timeinfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    if (!logOutput)
    {
        logOutput = stderr;
        fprintf(logOutput, "[%s]Log file is not installed!", buffer);
    }
    else
    {
        fprintf(logOutput, "[%s]", buffer);
    }
    
    va_list args;
    va_start(args, format);
    vfprintf(logOutput, format, args);
    va_end(args);
    
    fprintf(logOutput, "\n");
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
