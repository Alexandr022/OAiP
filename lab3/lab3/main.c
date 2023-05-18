// main.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
