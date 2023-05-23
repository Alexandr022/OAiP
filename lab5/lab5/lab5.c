// lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab5.h"

unsigned int hash(const char* str, unsigned int seed)
{
    unsigned int hash = seed;
    for (int i = 0; str[i] != '\0'; i++)
    {
        hash = hash * 31 + str[i];
    }
    return hash;
}

unsigned int hashFunction(const char* key, int table_size)
{
    unsigned int seed = 0;
    unsigned int hashVal = hash(key, seed);
    return hashVal % table_size;
}

HashTable* createHashTable()
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = MAX_CACHE_SIZE;
    table->table = malloc(sizeof(HashEntry*) * table->size);

    for (int i = 0; i < table->size; i++)
    {
        table->table[i] = NULL;
    }
    return table;
}

void freeHashTable(HashTable* table)
{
    for (int i = 0; i < table->size; i++)
    {
        HashEntry* items = table->table[i];

        while (items != NULL)
        {
            HashEntry* next = items->next;
            free(items->key);
            free(items->value);
            free(items);
            items = next;
        }
    }

    free(table->table);
    free(table);
}

void removeTail(HashTable* table, unsigned int index) 
{
    HashEntry* tail = table->table[index];

    while (tail->next != NULL) 
    {
        tail = tail->next;
    }

    if (tail->prev != NULL) 
    {
        tail->prev->next = NULL;
    }
    else 
    {
        table->table[index] = NULL;
    }
    free(tail->key);
    free(tail->value);
    free(tail);
}

void moveToHead(HashTable* table, unsigned int index, HashEntry* entry)
{
    if (entry->prev != NULL) {
        entry->prev->next = entry->next;

        if (entry->next != NULL) {
            entry->next->prev = entry->prev;
        }

        entry->prev = NULL;
        entry->next = table->table[index];

        if (table->table[index] != NULL) {
            table->table[index]->prev = entry;
        }

        table->table[index] = entry;
    }
}

int internalLookup(HashTable* table, const char* key)
{
    unsigned int index = hashFunction(key, table->size);
    HashEntry* current = table->table[index];
    HashEntry* prev = NULL;

    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0) 
        {
            moveToHead(table, index, current);

            if (countEntries(table) > MAX_CACHE_SIZE) 
            {
                removeTail(table, index);
            }

            return 1;
        }

        prev = current;
        current = current->next;
    }
    return 0;
}

int countEntries(const HashTable* table)
{
    int count = 0;
    for (int i = 0; i < table->size; i++) 
    {
        HashEntry* current = table->table[i];
        while (current != NULL) 
        {
            count++;
            current = current->next;
        }
    }
    return count;
}


void hashtableAdd(HashTable* table, const char* key, const char* value)
{
    unsigned int index = hashFunction(key, table->size);
    HashEntry* entry = malloc(sizeof(HashEntry));
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);
    strcpy(entry->key, key);
    strcpy(entry->value, value);

    entry->next = table->table[index];
    entry->prev = NULL;

    if (table->table[index] != NULL) {
        table->table[index]->prev = entry;
    }
    /*else
    {
        HashEntry* current = table->table[index];
        while (current->next!= NULL)
        {
            current = current->next;
        }
        current->next = entry;
        entry->prev = current;
    }*/
    table->table[index] = entry;
}

int checkIPaddress(const char* ip)
{
    int octets[4] = { 0 };
    int numOctets = sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);

    if (numOctets != 4)
    {
        return 0;
    }

    for (int i = 0; i < 4; i++)
    {
        if (octets[i] < 0 || octets[i] > 255 || (i == 0 && octets[i] == 0))
        {
            return 0;
        }
    }

    return 1;
}

void searchIPinFile(HashTable* cache, const char* filename, const char* dns, const char* head)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open file\n");
        return;
    }

    char line[MAX_LENGTH_SIZE];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char found_dns[MAX_LENGTH_SIZE];
        char ip[MAX_LENGTH_SIZE];
        int i = 0;
        int line_length = strlen(line);

        while (i < line_length && line[i] != ' ' && line[i] != '\n')
        {
            found_dns[i] = line[i];
            i++;
        }
        found_dns[i] = '\0';

        while (i < line_length && line[i] == ' ')
        {
            i++;
        }

        int j = 0;

        while (i < line_length && line[i] != ' ' && line[i] != '\n')
        {
            ip[j] = line[i];
            i++;
            j++;
        }
        ip[j] = '\0';

        if (strcmp(found_dns, dns) == 0)
        {
            if (checkIPaddress(ip) == 0)
            {
                fclose(file);
                searchIPinFile(cache, filename, ip, found_dns);
                return;
            }
            else if (head != NULL)
            {
                hashtableAdd(cache, head, ip);
            }
            else
            {
                hashtableAdd(cache, dns, ip);
            }
        }
    }
    fclose(file);
}

void printDNS(const char* ip_address, FILE* file)
{
    char line[MAX_LENGTH_SIZE];
    rewind(file);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int i = 0;
        char foundDNS[MAX_LENGTH_SIZE];
        char ip[MAX_LENGTH_SIZE];

        while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
        {
            foundDNS[i] = line[i];
            i++;
        }
        foundDNS[i] = '\0';

        while (line[i] == ' ')
        {
            i++;
        }

        int j = 0;

        while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
        {
            ip[j] = line[i];
            i++;
            j++;
        }
        ip[j] = '\0';

        if (strcmp(ip, ip_address) == 0)
        {
            printf("%s\n", foundDNS);
            long pos = ftell(file);
            printDNS(foundDNS, file);
            fseek(file, pos, SEEK_SET);
        }
    }
}

void printDNSbyIP(const char* ip_address, const char* filename)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    printDNS(ip_address, file);
    fclose(file);
}

void writeDNS(const char* filename, const char* dns_name, const char* ip_address)
{
    if (checkIPaddress(ip_address) == 0)
    {
        printf("Invalid IP Address\n");
        return;
    }

    FILE* file = fopen(filename, "r+");

    if (file == NULL)
    {
        printf("Error: could not open file '%s'\n", filename);
        return;
    }

    char line[MAX_LENGTH_SIZE];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        const char* current_dns = strtok(line, " ");
        if (strcmp(current_dns, dns_name) == 0)
        {
            printf("Error: IP address '%s' already exists in file\n", dns_name);
            fclose(file);
            return;
        }
    }

    fprintf(file, "\n%s %s", dns_name, ip_address);
    fclose(file);
}

void lookHashTable(HashTable* table, const char* key)
{
    if (internalLookup(table, key) == 0)
    {
        searchIPinFile(table, "dns.txt", key, NULL);
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
