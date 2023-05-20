// main.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "lab3.h"

int main()
{
	FILE* inputBMP;
	printf("--Enter filename--");
	char inputBMPname[MAX_LENGTH_SIZE]; 
	scanf("%s", inputBMPname);
	while (fopen_s(&inputBMP, inputBMPname, "rb") != 0)
	{
		printf("Error opening file.\n");
		scanf("%s", inputBMPname);
		rewind(stdin);
	}

	BMPfile BMP = initBMPstruct(inputBMP);
	
	menu(BMP);

	FILE* outputBMP;
	printf("--Enter output filename--");
	char outputBMPname[MAX_LENGTH_SIZE];
	scanf("%s", outputBMPname);

	while (fopen_s(&outputBMP, outputBMPname, "wb") != 0)
	{
		printf("Error opening file.\n");
		scanf("%s", outputBMPname);
		rewind(stdin);
	}
;
	outputBMPfile(outputBMP, BMP);
	printf("New image successfully saved.\n");

	fclose(inputBMP);
	fclose(outputBMP);
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
