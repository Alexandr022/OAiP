// lab2.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab2.2.h"

int replaysment(FILE* file, Words* wordsArrOne, Words* wordsArrTwo, int size, char* word)
{
	int bool_ = 0;

	for (int i = 0; i < size; i++)
	{
		if (!strcmp(wordsArrOne[i].word, word))
		{
			fprintf(file, "%s", wordsArrTwo[i].word);
			bool_ = 1;
		}
		else if (!strcmp(wordsArrTwo[i].word, word))
		{
			fprintf(file, "%s", wordsArrOne[i].word);
			bool_ = 1;
		}
	}
	return bool_;
}

void initializeArr(FILE* file, Words** wordsArrayOne, Words** wordsArrayTwo, int* size, Words* words)
{
	for (int i = 0; !feof(file); i++)
	{
		char* word1 = malloc(100);
		char* word2 = malloc(100);

		fscanf_s(file, "%s", word1, 100);

		if (strcmp(word1, "<!>") == 0)
		{
			(*wordsArrayOne) = realloc(*wordsArrayOne, (--(*size)) * sizeof(Words));
			(*wordsArrayTwo) = realloc(*wordsArrayTwo, (*size) * sizeof(Words));
			break;
		}
		fscanf_s(file, "%s", word2, 100);

		(*wordsArrayOne)[(*size) - 1].word = malloc(100);
		(*wordsArrayOne)[(*size) - 1].word = word1;

		(*wordsArrayTwo)[(*size) - 1].word = malloc(100);
		(*wordsArrayTwo)[(*size) - 1].word = word2;

		(*wordsArrayOne) = realloc(*wordsArrayOne, (++(*size)) * sizeof(Words));
		(*wordsArrayTwo) = realloc(*wordsArrayTwo, (*size) * sizeof(Words));

		printf("%d: %s -> %s\n", i + 1, (*wordsArrayOne)[i].word, (*wordsArrayTwo)[i].word);
	}
}

void fillFile(FILE* file, FILE* newFile, Words* wordsArrayOne, Words* wordsArrayTwo, int size)
{
	for (int i = 0; !feof(file); i++)
	{
		char c;
		char* word = malloc(100);
		fscanf_s(file, "%s%c", word, 100, &c, 1);
		if (!replaysment(newFile, wordsArrayOne, wordsArrayTwo, size, word) && !feof(file))
		{
			fprintf(newFile, "%s", word);
		}
		if (!feof(file)) fprintf(newFile, "%c", c);
		free(word);
	}
}

void displaySize(FILE* inputFilename, FILE* outputFilename)
{
	fseek(inputFilename, 0, SEEK_END);
	long inputSize = ftell(inputFilename);

	fseek(outputFilename, 0, SEEK_END);
	long outputSize = ftell(outputFilename);

	printf("Input file size: %ld bytes\n", inputSize);
	printf("Output file size: %ld bytes\n", outputSize);
}

int main()
{
	FILE* filename;
	FILE* outputFilename;
	fopen_s(&outputFilename, "C:/Users/Asus/Desktop/lab2/decompressed.txt", "w+");

	if (fopen_s(&filename, "C:/Users/Asus/Desktop/lab2/compressed.txt", "r") != 0)
	{
		printf("File is not open or does not exist!!!\n");
	}

	int size = 1;
	Words* words = (Words*)malloc(size * sizeof(Words));
	Words* wordsOne = (Words*)malloc(size * sizeof(Words));
	Words* wordsTwo = (Words*)malloc(size * sizeof(Words));

	initializeArr(filename, &wordsOne, &wordsTwo, &size, words);
	fillFile(filename, outputFilename, wordsOne, wordsTwo, size);
	displaySize(filename, outputFilename);

	free(wordsOne);
	free(wordsTwo);

	fclose(filename);
	fclose(outputFilename);
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
