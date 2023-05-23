// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab3.h"

int main()
{
	FILE* inputBMP;
	printf("--Enter filename--");
	char inputBMPname[MAX_LENGTH_SIZE]; 
	scanf("%99s", inputBMPname);
	while (fopen_s(&inputBMP, inputBMPname, "rb") != 0)
	{
		printf("Error opening file.\n");
		scanf("%99s", inputBMPname);
		rewind(stdin);
	}

	BMPfile BMP = initBMPstruct(inputBMP);
	
	menu(BMP);

	FILE* outputBMP;
	printf("--Enter output filename--");
	char outputBMPname[MAX_LENGTH_SIZE];
	scanf("%99s", outputBMPname);

	while (fopen_s(&outputBMP, outputBMPname, "wb") != 0)
	{
		printf("Error opening file.\n");
		scanf("%99s", outputBMPname);
		rewind(stdin);
	}

	outputBMPfile(outputBMP, BMP);
	printf("New image successfully saved.\n");

	fclose(inputBMP);
	fclose(outputBMP);
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
