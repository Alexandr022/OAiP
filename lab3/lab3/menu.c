// menu.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab3.h"

void menu(BMPfile BMP)
{
	while (1)
	{
		printf("-----------------------------------------------\n");
		printf("Choose which image you wanna get.\n");
		printf("1.Conversion from image to negative.\n");
		printf("2.Conversion image into black and white.\n");
		printf("3.Median filtration.\n");
		printf("4.Gamma correction.\n");
		printf("5.Save image.\n");
		printf("-----------------------------------------------\n");

		int choose = 0;
		scanf("%d", &choose);
		double countGamma = 0;
		int countMedian = 0;


		switch (choose)
		{
		case 1:
			convertToNegative(BMP);
			break;
		case 2:
			convertToBlackAndWhite(BMP);
			break;
		case 3:
			countMedian = 0;
			printf("Enter median filtering value.(must be odd)");
			scanf("%d", countMedian);
			medianFilter(&BMP, countMedian);
			break;
		case 4:
			printf("Enter the gamma correction value.");
			countGamma = 0;
			scanf("%d", countGamma);
			gammaCorrection(BMP, countGamma);
			break;
		default:
			break;
		}

		if (choose == 5)
		{
			break;
		}
	}
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