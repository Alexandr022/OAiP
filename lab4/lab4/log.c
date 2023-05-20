// log.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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

    va_list args;
    va_start(args, format);

    if (!logOutput)
    {
        logOutput = stderr;
        fprintf(logOutput, "[%s]Log file is not installed!", buffer);
    }
    else
    {
        fprintf(logOutput, "[%s]", buffer);
    }

    vfprintf(logOutput, format, args);
    va_end(args);

    fprintf(logOutput, "\n");
}

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
