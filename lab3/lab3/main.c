// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab3.h"

int main()
{
	FILE* inputBMP;

	String inputBMPname = getStringFromKayboard("--Enter filename--");

	while (fopen_s(&inputBMP, inputBMPname.String, "rb") != 0)
	{
		printf("Error opening file.\n");
		inputBMPname = getStringFromKayboard("--Enter filename--");
		rewind(stdin);
	}

	BMPfile BMP = initBMPstruct(inputBMP);
	
	menu(BMP);

	FILE* outputBMP;

	String outputBMPname = getStringFromKayboard("--Enter output filename--");

	while (fopen_s(&outputBMP, outputBMPname.String, "wb") != 0)
	{
		printf("Error opening file.\n");
		outputBMPname = getStringFromKayboard("--Enter outout filename--");
		rewind(stdin);
	}
;
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
