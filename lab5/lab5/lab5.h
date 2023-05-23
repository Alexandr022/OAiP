#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CACHE_SIZE 3
#define MAX_LENGTH_SIZE 256

typedef struct HashEntry
{
    char* key;
    char* value;
    struct HashEntry* prev;
    struct HashEntry* next;
} HashEntry;

typedef struct HashTable
{
    int size;
    HashEntry** table;
} HashTable;

unsigned int hash(const char* str, unsigned int seed);

unsigned int hashFunction(const char* key, int table_size);

HashTable* createHashTable();

void freeHashTable(HashTable* table);

void removeTail(HashTable* table, unsigned int index);

void moveToHead(HashTable* table, unsigned int index, HashEntry* entry);

int internalLookup(HashTable* table, const char* key);

void hashtableAdd(HashTable* table, const char* key, const char* value);

int checkIPaddress(const char* ip);

void searchIPinFile(HashTable* cache, const char* filename, const char* dns, const char* head);

void printDNS(const char* ip_address, FILE* file);

void printDNSbyIP(const char* ip_address, const char* filename);

void writeDNS(const char* filename, const char* dns_name, const char* ip_address);

void lookHashTable(HashTable* cache, const char* key);