// lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab.h"

lapTopArrayStruct* initLapTopArrayStruct(int size)
{
    lapTopArrayStruct* memory = (lapTopArrayStruct*)malloc(sizeof(lapTopArrayStruct));
    memory->size = size;
    memory->laptops = (lapTopStruct*)malloc(size * sizeof(lapTopStruct));
    if (memory == NULL)
    {
        printf("Error. Failed to allocate memory.\n");
        return NULL;
    }
    if (memory->laptops == NULL)
    {
        printf("Error. Failed to allocate memory.\n");
        return NULL;
    }
    return memory;
}

void printLapTops(lapTopArrayStruct* laptops)
{
    for (size_t i = 0; i < laptops->size; i++)
    {
        printf("%d.Name: %s\n  Display size: %d\'%d\n  Resolution: %dx%d\n  Frequency: %d Hz\n  Cpu: %s\n  Ram size and type: %d Gb %s\n  Storage type and size: %s %d Gb\n  GPU: %s %d Gb\n",
            i + 1, laptops->laptops[i].name, laptops->laptops[i].displaysize[0], laptops->laptops[i].displaysize[1], laptops->laptops[i].resolution[0], laptops->laptops[i].resolution[1],
            laptops->laptops[i].frequency, laptops->laptops[i].cpu, laptops->laptops[i].ramsize, laptops->laptops[i].ramtype, laptops->laptops[i].storagetype, laptops->laptops[i].storagesize,
            laptops->laptops[i].gpu, laptops->laptops[i].vram);

        switch (laptops->laptops[i].OC)
        {
        case Windows_10:
            printf("  OC: Windows 10\n");
            break;
        case Windows_11:
            printf("  OC: Windows 11\n");
            break;
        case Linux:
            printf("  OC: Linux\n");
            break;
        case None:
            printf("  OC: None\n");
            break;
        }

        switch (laptops->laptops[i].color)
        {
        case Black:
            printf("  Color: Black\n");
            break;
        case Grey:
            printf("  Color: Grey\n");
            break;
        case White:
            printf("  Color: White\n");
            break;
        case Dark_Gray: 
            printf("  Color: Dark gray\n");
            break;
        case Dark_Blue:
            printf("  Color: Dark blue\n");
            break;
        case Silver:
            printf("  'Color: Silver\n");
            break;
        }

        printf("Price: %f\n", laptops->laptops[i].price);
    }
}

void initializeStructByParser(char* filename)
{
    FILE* fileStreamPtr = fopen(filename, "r");
    if (fileStreamPtr == NULL) 
    {
        printf("Error opening file.\n");
        return 0;
    }

    char* countString = "<span data-bind=";
    char stopReading = "</";
    char buffer[1000];
    int count = 0;

    while (!feof(filename))
    {
        read(filename, buffer, 1000);
        if (buffer == countString[count])
        {
            count++;
        }
        else
        {
            count = 0;
        }
        if (count = strlen(countString))
        {
            break;
        }

        printf("Number initialising laptops : %d", &count);

    }

    fclose(fileStreamPtr);
}

int sortCount;

int arraySort(lapTopArrayStruct* laptops)
{
    sortCount = getIntFromKayboard("Select the parameters by which sorting will be performed.\n1.Name\n2.Display size\n3.Resolution.\n4.Frequency\n5.CPU\n6.RAM size\n7.RAM type\n8.Storage size\n9.Storage type\n10.GPU\n11.VRAM\n12.Price");

    while (sortCount > 12 && sortCount < 1)
    {
        printf("Wrong input.\n");
        rewind(stdin);
        sortCount = getIntFromKayboard("Select the parameters by which sorting will be performed.\n1.Name\n2.Display size\n3.Resolution.\n4.Frequency\n5.CPU\n6.RAM size\n7.RAM type\n8.Storage size\n9.Storage type\n10.GPU\n11.VRAM\n12.Price");
    }

    qsort(laptops->laptops, laptops->size, sizeof(lapTopStruct), compareForSort);

    printf("Sorted list.\n");
    printLapTops(laptops);
    menu(laptops);
}

int compareForSort(void* a,void* b) 
{
    lapTopStruct* laptops = (lapTopStruct*)a;
    lapTopStruct* laptops2 = (lapTopStruct*)b;

    switch (sortCount)
    {
    case 1:
        return strcmp(laptops->name, laptops2->name);
    case 2:
        return (laptops->displaysize - laptops2->displaysize);
    case 3:
        return (laptops->resolution - laptops2->resolution);
    case 4:
        return (laptops->frequency - laptops2->frequency);
    case 5:
        return strcmp(laptops->cpu, laptops2->cpu);
    case 6:
        return (laptops->ramsize - laptops2->ramsize);
    case 7:
        return strcmp(laptops->ramtype, laptops2->ramtype);
    case 8:
        return (laptops->storagesize - laptops2->storagesize);
    case 9:
        return strcmp(laptops->storagetype, laptops2->storagetype);
    case 10:
        return strcmp(laptops->gpu, laptops2->gpu);
    case 11:
        return (laptops->vram - laptops2->vram);
    case 12:
        return (laptops->price - laptops2->price);
    }
}

int twoFieldsArraySort()
{
    
}

int deleteStruct(lapTopArrayStruct* laptops)
{
    for (int i = 0; i < laptops->size; i++) 
    {
        free(laptops[i].laptops);
    }

    free(laptops);
    printf("Choose the next action you want to take.\n");
    printf("1.At the begining.\n");
    int count = getIntFromKayboard("2.Close programm.");

    while (count > 2 && count < 1)
    {
        printf("Enter 1 or 2.\n");
        rewind(stdin);
    }

    switch (count)
    {
    case 1:
        main();
        system("cls");
    case 2:
        return 0;
    }
}

int parsedHTML()
{
    
}

void initializeStructByHand()
{
    int size = getIntFromKayboard("Write a number of laptops.");
    lapTopArrayStruct* laptops = initLapTopArrayStruct(size);

    for (size_t i = 0; i < size; i++)
    {
        printf("%d laptop.\n", i + 1);
        printf("Enter a name.\n");
        scanf_s("%s", laptops->laptops[i].name, sizeof(laptops->laptops[i].name));

        while (laptops->laptops[i].name, sizeof(laptops->laptops[i].name) > '9' && laptops->laptops[i].name, sizeof(laptops->laptops[i].name) < '1')
        {
            printf("Wrong input. Enter a name.\n");
            rewind(stdin);
            scanf_s("%s", laptops->laptops[i].name, sizeof(laptops->laptops[i].name));
        }

        printf("Enter a displaysize ?.?.\n");
        scanf_s("%d", &laptops->laptops[i].displaysize[0]);

        while (laptops->laptops[i].displaysize[0] != 13 && laptops->laptops[i].displaysize[0] != 14 && laptops->laptops[i].displaysize[0] != 15 && laptops->laptops[i].displaysize[0] != 16 && laptops->laptops[i].displaysize[0] != 17)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            scanf_s("%d", &laptops->laptops[i].displaysize[0]);
        }

        switch (laptops->laptops[i].displaysize[0])
        {
        case 13:
            laptops->laptops[i].displaysize[1] = 3;
            break;
        case 14:
            laptops->laptops[i].displaysize[1] = 0;
            break;
        case 15:
            laptops->laptops[i].displaysize[1] = 6;
            break;  
        case 16:
            laptops->laptops[i].displaysize[1] = 0;
            break;
        case 17:
            laptops->laptops[i].displaysize[1] = 3;
            break;
        default:
            printf("Wrong input. Enter a name.\n");
            rewind(stdin);
        }

        printf("Enter a resolution ?x?.\n");
        scanf_s("%d", &laptops->laptops[i].resolution[0]);

        while (laptops->laptops[i].resolution[0] != 1024 && laptops->laptops[i].resolution[0] != 1920 && laptops->laptops[i].resolution[0] != 2560)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            scanf_s("%d", &laptops->laptops[i].resolution[0]);
        }
        
        switch (laptops->laptops[i].resolution[0])
        {
        case 1024:
            laptops->laptops[i].resolution[1] = 720;
            break;
        case 1920:
            laptops->laptops[i].resolution[1] = 1080;
            break;
        case 2560:
            laptops->laptops[i].resolution[1] = 1140;
            break;
        }
        
        printf("Enter a frequency.\n");
        scanf_s("%d", &laptops->laptops[i].frequency);

        while (laptops->laptops[i].frequency != 60 && laptops->laptops[i].frequency != 120 && laptops->laptops[i].frequency != 144 && laptops->laptops[i].frequency != 160)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            scanf_s("%d", &laptops->laptops[i].frequency);
        }

        printf("Enter a CPU.\n");
        scanf_s("%s", laptops->laptops[i].cpu, sizeof(laptops->laptops[i].cpu));
        
        printf("Enter a RAM size.\n");
        scanf_s("%d", &laptops->laptops[i].ramsize);

        while (laptops->laptops[i].ramsize != 4 && laptops->laptops[i].ramsize != 8 && laptops->laptops[i].ramsize != 16 && laptops->laptops[i].ramsize != 32 && laptops->laptops[i].ramsize != 64)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            scanf_s("%d", &laptops->laptops[i].ramsize);
        }
       
        printf("Enter a RAM type.\n");
        scanf_s("%s", laptops->laptops[i].ramtype, sizeof(laptops->laptops[i].ramtype));

        printf("Enter a storage size.\n");
        scanf_s("%d", &laptops->laptops[i].storagesize);

        while (laptops->laptops[i].storagesize != 128 && laptops->laptops[i].storagesize != 256 && laptops->laptops[i].storagesize != 512 && laptops->laptops[i].storagesize != 1024)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            scanf_s("%d", &laptops->laptops[i].storagesize);
        }

        printf("Enter a storage type.\n");
        scanf_s("%s", laptops->laptops[i].storagetype, sizeof(laptops->laptops[i].storagetype));

        printf("Enter a GPU.\n");
        scanf_s("%s", laptops->laptops[i].gpu, sizeof(laptops->laptops[i].gpu));

        printf("Enter a VRAM.\n");
        scanf_s("%d", &laptops->laptops[i].vram);

        while (laptops->laptops[i].vram != 4 && laptops->laptops[i].vram != 6 && laptops->laptops[i].vram != 8 && laptops->laptops[i].vram != 12)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            scanf_s("%d", &laptops->laptops[i].vram);
        }

        printf("Enter OC.\n");
        printf("1.Windows 10\n2.Windows 11\n3.Linux\n4.None.\n");
        int OC = getIntFromKayboard("Enter a number from 1 to 4.");

        while (OC > 4 && OC < 1)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            int OC = getIntFromKayboard("Enter a number from 1 to 4.");
        }

        switch (OC)
        {
        case 1:
            laptops->laptops[i].OC = Windows_10;
            break;
        case 2:
            laptops->laptops[i].OC = Windows_11;
            break;
        case 3:
            laptops->laptops[i].OC = Linux;
            break;
        case 4:
            laptops->laptops[i].OC = None;
            break;
        }

        printf("Enter color.\n");
        printf("1.Black\n2.Grey\n3.White\n4.Dark grey\n5.Dark blue\n6.Silver\n");
        int color = getIntFromKayboard("Enter a number from 1 to 6.");

        while (color > 4 && color < 1)
        {
            printf("Wrong input.\n");
            rewind(stdin);
            int color = getIntFromKayboard("Enter a number from 1 to 6.");
        }

        switch (color)
        {
        case 1:
            laptops->laptops[i].color = Black;
            break;
        case 2:
            laptops->laptops[i].color = Grey;
            break;
        case 3:
            laptops->laptops[i].color = White;
            break;
        case 4:
            laptops->laptops[i].color = Dark_Gray;
            break;
        case 5:
            laptops->laptops[i].color = Dark_Blue;
            break;
        case 6:
            laptops->laptops[i].color = Silver;
            break;
        }

        laptops->laptops[i].price = getFloatFromKayboard("Enter a price.");
    }
    
    printLapTops(laptops);
    menu(laptops);
}

int menu(lapTopArrayStruct* laptops)
{
    printf("----------------------------------------------------------------\n");
    printf("Select an action.\n");
    printf("1. Sort the array by each field of the structure.\n");
    printf("2. Sorting by two fields at the same time.\n");
    printf("3. Remove the structure from the array.\n");
    printf("4. Parsing HTML file.\n");
    int count = getIntFromKayboard("Write a number from 1 to 4.");
    printf("----------------------------------------------------------------\n");
    switch (count)
    {
    case 1:
        arraySort(laptops);
    case 2:
        twoFieldsArraySort();
    case 3:
        deleteStruct(laptops);
    case 4:
        parsedHTML();
    }
}

int main()
{
    int count = getIntFromKayboard("Enter how you want to fill in the structure.\n1.By hand.\n2.With parser.\n3.Random init");
    if (count > 1 && count < 2)
    {
        printf("Wrong input. Enter 1 or 2.\n");
        rewind(stdin);
    }
    switch (count)
    {
    case 1:
        system("cls");
        initializeStructByHand();
        break;
    case 2:
        initializeStructByParser("LapTop.html");
        break;
    case 3:
        break;
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







