// lab2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab2.1.h"

int isThereWord(Words* words, char* word, int size)
{
	int bool_ = 0;
	for (int i = 0; i < size - 1; i++)
	{

		if (!strcmp(words[i].word, word))
		{
			words[i].countWords++;
			bool_ = 1;
		}
	}

	return bool_;
}

void frequency(Words* words, int size)
{
	for (int i = 0; i < size; i++)
	{
		words[i].freq = words[i].countWords * strlen(words[i].word);
	}
}

void distribution(Words* words, int* size, Words** wordsArrayOne, Words** wordsArrayTwo)
{
	int countWords = averageCount(words, *size);
	int wordSize = averageLength(words, *size);
	int newSize = 0, sizeOne = 1, sizeTwo = 1;

	for (int i = 0; i < *size; i++)
	{
		if (words[i].countWords > countWords && words[i].wordSize > wordSize)
		{
			(*wordsArrayTwo)[(sizeTwo++) - 1] = words[i];
			*wordsArrayTwo = realloc(*wordsArrayTwo, sizeTwo * sizeof(Words));
		}
		if (words[i].countWords < countWords && words[i].wordSize < wordSize)
		{
			(*wordsArrayOne)[(sizeOne++) - 1] = words[i];
			*wordsArrayOne = realloc(*wordsArrayOne, sizeOne * sizeof(Words));
		}
	}

	newSize = sizeTwo - 1;
	*wordsArrayTwo = realloc(*wordsArrayTwo, newSize * sizeof(Words));
	*wordsArrayOne = realloc(*wordsArrayOne, newSize * sizeof(Words));
	*size = newSize;
}

int replaceWords(FILE* file, Words* wordsArrayOne, Words* wordsArrayTwo, int size, char* word)
{
	int bool_ = 0;

	for (int i = 0; i < size; i++)
	{
		if (!strcmp(wordsArrayOne[i].word, word))
		{
			fprintf(file, "%s", wordsArrayTwo[i].word);
			bool_ = 1;
		}
		else if (!strcmp(wordsArrayTwo[i].word, word))
		{
			fprintf(file, "%s", wordsArrayOne[i].word);
			bool_ = 1;
		}
	}

	return bool_;
}

int averageCount(Words* words, int size)
{
	int average = 0;

	for (int i = 0; i < size; i++)
	{
		average += words[i].countWords;
	}

	return (average / size);
}

int averageLength(Words* words, int size)
{
	int average = 0;

	for (int i = 0; i < size; i++)
	{
		average += words[i].wordSize;
	}

	return (average / size);
}

void initializeArr(FILE* file, Words** words, int* size)
{
	for (int i = 0; !feof(file); i++)
	{
		char* word = malloc(100);
		fscanf_s(file, "%s", word, 100);
		if (!isThereWord((*words), word, (*size)) && strlen(word) > 0)
		{
			(*words)[(*size) - 1].word = malloc(100);
			(*words)[(*size) - 1].word = word;
			(*words)[(*size) - 1].wordSize = strlen(word);
			(*words)[(*size) - 1].countWords = 1;
			(*words) = realloc(*words, (++(*size)) * sizeof(Words));
		}
	}
	words = realloc(*words, ((*size)--) * sizeof(Words));
	rewind(file);
}

int compareLong(void *a, void *b)
{
	Words* wordsA = (Words*)a;
	Words* wordsB = (Words*)b;
	return (wordsB->freq - wordsA->freq);
}

int compareShort(void* a, void* b)
{
	Words* wordsA = (Words*)a;
	Words* wordsB = (Words*)b;
	return (wordsA->freq - wordsB->freq);
}

void fillFile(FILE* file, FILE* newFile, Words* wordsArrayOne, Words* wordsArrayTwo, int size)
{
	while (!feof(file))
	{
		char c;
		char* word = malloc(100);
		fscanf_s(file, "%s%c", word, 100, &c, 1);

		if (!replaceWords(newFile, wordsArrayOne, wordsArrayTwo, size, word) && !feof(file))
		{
			fprintf(newFile, "%s", word);
		}

		if (!feof(file))
		{
			fprintf(newFile, "%c", c);
		}
		free(word);
	}
}

void printWords(Words* words1, Words* words2, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d: %s -> %s\n", i + 1, words1[i].word, words2[i].word);
	}
}

void fillWordLibrary(FILE* newFile, Words* wordsArrayTwo, Words* wordsArrayOne, int size)
{
	for (int i = 0; i < size; i++)
	{
		fprintf(newFile, "%s %s ", wordsArrayTwo[i].word, wordsArrayOne[i].word);
	}

	fprintf(newFile, "%s\n", "<!>");
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
	FILE* inputFilename;
	fopen_s(&inputFilename, "C:/Users/Asus/Desktop/lab2/input.txt", "r");

	if (fopen_s(&inputFilename, "C:/Users/Asus/Desktop/lab2/input.txt", "r") != 0)
	{
		printf("Error opening file.\n");
		return 0;
	}

	FILE* outputFilename;
	fopen_s(&outputFilename, "C:/Users/Asus/Desktop/lab2/compressed.txt", "w+");

	int size = 1;
	Words* words = (Words*)malloc(size * sizeof(Words));
	Words* wordsOne = (Words*)malloc(size * sizeof(Words));
	Words* wordsTwo = (Words*)malloc(size * sizeof(Words));

	initializeArr(inputFilename, &words, &size);
	distribution(words, &size, &wordsOne, &wordsTwo);

	frequency(wordsOne, size);
	frequency(wordsTwo, size);

	qsort(wordsTwo, size, sizeof(Words), compareLong);
	qsort(wordsOne, size, sizeof(Words), compareShort);
	
	for (int i = 0; i < size; i++)
	{
		printf("%d\n", wordsOne[i].freq);
	}
	printf("-----------------------------------------");
	for (int i = 0; i < size; i++)
	{
		printf("%d\n", wordsTwo[i].freq);
	}
	
	fillWordLibrary(outputFilename, wordsTwo, wordsOne, size);
	fillFile(inputFilename, outputFilename, wordsOne, wordsTwo, size);

	printWords(wordsOne, wordsTwo, size);
	displaySize(inputFilename, outputFilename);

	free(words);
	free(wordsOne);
	free(wordsTwo);

	fclose(inputFilename);
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
