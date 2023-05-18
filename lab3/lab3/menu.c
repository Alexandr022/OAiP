// menu.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "lab3.h"
#include "InputManager.h"

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

		int choose = getIntFromKayboard("");
		double countGamma = 0;
		int countMedian = 0;

		while (choose > 5 && choose < 1)
		{
			printf("Error. Write number from 1 to 4.\n");
			rewind(stdin);
		}

		switch (choose)
		{
		case 1:
			convertToNegative(BMP);
			break;
		case 2:
			convertToBlackAndWhite(BMP);
			break;
		case 3:
			countMedian = getIntFromKayboard("Enter median filtering value.(must be odd)");

			while (countMedian % 2 == 0 && countMedian > 7 && countMedian < 1)
			{
				printf("Enter odd value.\n");
				countMedian = getIntFromKayboard("Enter median filtering value.(must be odd)");
				rewind(stdin);
			}
			
			medianFilter(&BMP, countMedian);
			break;
		case 4:
			countGamma = getFloatFromKayboard("Enter the gamma correction value.");
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

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.