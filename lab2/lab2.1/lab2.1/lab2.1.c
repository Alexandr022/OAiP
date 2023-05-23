// lab2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab2.1.h"

int isThereWord(Words* words, const char* word, int size) {
    int bool_ = 0;
    for (int i = 0; i < size; i++) {
        if (words[i].word != NULL && strcmp(words[i].word, word) == 0) {
            words[i].countWords++;
            bool_ = 1;
        }
    }
    return bool_;
}


void frequency(Words* words, int size)
{
    if (words == NULL)
    {
        printf("Invalid pointer: words is NULL.\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (words[i].word != NULL)
        {
            words[i].freq = words[i].countWords * words[i].wordSize;
        }
        else
        {
            printf("Invalid pointer: word is NULL at index %d.\n", i);
        }
    }
}

void distribution(Words* words, int* size, Words** wordsArrayOne, Words** wordsArrayTwo)
{
    int countWords = averageCount(words, *size);
    int wordSize = averageLength(words, *size);
    int sizeOne = 0;
    int sizeTwo = 0;
    
    Words* tempOne = NULL;
    Words* tempTwo = NULL;
    
    for (int i = 0; i < *size; i++)
    {
        if (wordsArrayTwo != NULL && *wordsArrayTwo != NULL && words[i].countWords > countWords && words[i].wordSize > wordSize)
        {
            tempTwo = realloc(*wordsArrayTwo, (sizeTwo + 1) * sizeof(Words));
            if (tempTwo == NULL)
            {
                printf("Memory reallocation failed.\n");
                break;
            }
            *wordsArrayTwo = tempTwo;
            (*wordsArrayTwo)[sizeTwo] = words[i];
            sizeTwo++;
        }
        else if (wordsArrayOne != NULL && *wordsArrayOne != NULL && words[i].countWords < countWords && words[i].wordSize < wordSize)
        {
            tempOne = realloc(*wordsArrayOne, (sizeOne + 1) * sizeof(Words));
            if (tempOne == NULL)
            {
                printf("Memory reallocation failed.\n");
                break;
            }
            *wordsArrayOne = tempOne;
            (*wordsArrayOne)[sizeOne] = words[i];
            sizeOne++;
        }
    }
    
    if (wordsArrayTwo != NULL && sizeTwo > 0)
    {
        tempTwo = realloc(*wordsArrayTwo, sizeTwo * sizeof(Words));
        if (tempTwo != NULL)
        {
            *wordsArrayTwo = tempTwo;
        }
    }
    
    if (wordsArrayOne != NULL && sizeOne > 0)
    {
        tempOne = realloc(*wordsArrayOne, sizeOne * sizeof(Words));
        if (tempOne != NULL)
        {
            *wordsArrayOne = tempOne;
        }
    }
    
    *size = sizeOne;
}


int replaceWords(FILE* file, Words* wordsArrayOne, Words* wordsArrayTwo, int size, char* word)
{
    int bool_ = 0;
    for (int i = 0; i < size; i++)
    {
        if (wordsArrayOne[i].word != NULL && !strcmp(wordsArrayOne[i].word, word))
        {
            fprintf(file, "%s", wordsArrayTwo[i].word);
            bool_ = 1;
        }
        else if (wordsArrayTwo[i].word != NULL && !strcmp(wordsArrayTwo[i].word, word))
        {
            fprintf(file, "%s", wordsArrayOne[i].word);
            bool_ = 1;
        }
    }
    return bool_;
}



void initializeArr(FILE* file, Words** words, int* size)
{
    int maxWordLength = 100;
    *size = 0;
    *words = NULL;
    char* word = malloc(maxWordLength);
    if (word == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    
    int fscanfResult;
    while ((fscanfResult = fscanf(file, "%99s", word)) == 1)
    {
        if (!isThereWord(*words, word, *size) && strlen(word) > 0)
        {
            Words* temp = realloc(*words, (*size + 1) * sizeof(Words));
            if (temp == NULL)
            {
                printf("Memory reallocation failed.\n");
                break;
            }
            *words = temp;
            
            (*words)[*size].word = malloc(strlen(word) + 1);
            if ((*words)[*size].word == NULL)
            {
                printf("Memory allocation failed.\n");
                break;
            }
            
            strcpy((*words)[*size].word, word);
            (*words)[*size].wordSize = strlen(word);
            (*words)[*size].countWords = 1;
            (*size)++;
        }
    }
    
    free(word);
}


int main()
{
    FILE* inputFilename;
    if (fopen_s(&inputFilename, "C:/Users/Asus/Desktop/lab2/input.txt", "r") != 0)
    {
        printf("Error opening input file.\n");
        return 0;
    }

    FILE* outputFilename;
    if (fopen_s(&outputFilename, "C:/Users/Asus/Desktop/lab2/compressed.txt", "w+") != 0)
    {
        printf("Error opening output file.\n");
        fclose(inputFilename);
        return 0;
    }

    int size = 0;
    Words* words = NULL;
    Words* wordsOne = NULL;
    Words* wordsTwo = NULL;

    initializeArr(inputFilename, &words, &size);
    distribution(words, &size, &wordsOne, &wordsTwo);
    frequency(wordsOne, size);
    frequency(wordsTwo, size);
    qsort(wordsTwo, size, sizeof(Words), compareLong);
    qsort(wordsOne, size, sizeof(Words), compareLong);
    for (int i = 0; i < size; i++)
    {
        fprintf(outputFilename, "%s\n", wordsOne[i].word);
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(outputFilename, "%s\n", wordsTwo[i].word);
    }

    char wordToReplace[] = "word";
    replaceWords(outputFilename, wordsOne, wordsTwo, size, wordToReplace);

    fclose(inputFilename);
    fclose(outputFilename);
    free(words);
    free(wordsOne);
    free(wordsTwo);

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
