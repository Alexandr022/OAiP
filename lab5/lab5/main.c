// lab5.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "lab5.h"

void findIP(HashTable* cache) 
{
    char dns[MAX_LENGTH_SIZE];
    printf("Write DNS\n");
    printf(">");
    scanf("%99s", dns);

    lookHashTable(cache, dns);

    unsigned int index = hashFunction(dns, cache->size, cache);
    HashEntry* current = cache->table[index];
    while (current != NULL)
    {
        if (strcmp(current->key, dns) == 0)
        {
            printf("IP: %s\n", current->value);
            break;
        }
        current = current->next;
    }
}

void addIPadress() 
{
    char dns[MAX_LENGTH_SIZE];
    printf("Write DNS\n");
    printf(">");
    scanf("%99s", dns);

    char ip[MAX_LENGTH_SIZE];
    printf("Write IP\n");
    printf(">");
    scanf("%15s", ip);

    writeDNS("dns.txt", dns, ip);
}

void getAllip() 
{
    char ip[MAX_LENGTH_SIZE];
    printf("Write IP: ");
    scanf("%15s", ip);
    printDNSbyIP(ip, "dns.txt");
}

void printHashTable(const HashTable* cache)
{
    printf("\nCache contents:\n");
    HashEntry* current = NULL;
    for (int i = 0; i < cache->size; i++)
    {
        current = cache->table[i];
        while (current != NULL)
        {
            printf("Key: %s, Value: %s\n", current->key, current->value);
            current = current->next;
        }
    }
}

void main() 
{
    HashTable* cache = createHashTable();

    while (1) 
    {
        int choice;

        printf("-----Menu-----\n1 - Find\n2 - Add\n3 - Get all IP\n4 - Clear Cache\n5 - Write Cache\n6 - Exit\n");

        while (scanf_s("%d", &choice) == 0 || choice < 1 || choice > 6) 
        {
            printf("Invalid choice\n");
            rewind(stdin);
        }

        switch (choice) 
        {
        case 1:
            findIP(cache);
            break;
        case 2:
            addIPadress();
            break;
        case 3:
            getAllip();
            break;
        case 4:
            freeHashTable(cache);
            cache = createHashTable();
            break;
        case 5:
            printHashTable(cache);
            break;
        default:
            freeHashTable(cache);
            return;
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
