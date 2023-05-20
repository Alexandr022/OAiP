// lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab4.h"
#include "log.h"

int main() 
{
    char log[LENGTH];
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    strftime(log, sizeof(log), "log_%Y-%m-%d_%H-%M-%S.txt", timeinfo);
    logOpen(log);

    String filename = getStringFromKayboard("Enter file name");

    FILE* input = fopen(filename.String, "r");
    Node* root = initTree(input);

    fclose(input);

    printf("Hi! Make a guess and I'll try to guess it.\n");

    gameTree(root);

    initNewTree(root, fopen(filename.String, "w"));
  
    freeTree(root);

    return 0;
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
