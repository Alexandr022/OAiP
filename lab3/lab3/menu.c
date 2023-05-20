// menu.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.