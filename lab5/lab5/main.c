// lab5.cpp : Ýòîò ôàéë ñîäåðæèò ôóíêöèþ "main". Çäåñü íà÷èíàåòñÿ è çàêàí÷èâàåòñÿ âûïîëíåíèå ïðîãðàììû.
//

#include "lab5.h"

void findIP(HashTable* cache) 
{
    char dns[MAX_LENGTH_SIZE];
    printf("Write DNS\n");
    printf(">");
    scanf("%99s", dns);

    lookHashTable(cache, dns);
}

void addIPadress() 
{
    char dns[MAX_LENGTH_SIZE];
    printf("Write DNS\n");
    printf(">");
    scanf("%s", dns);

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
    printf("\n");
    HashEntry* current = NULL;
    for (int i = cache->size - 1; i >= 0; i--)
    {
        current = cache->table[i];
        while (current != NULL)
        {
            printf("%s %s\n", current->key, current->value);
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
            return;
        }
    }

}
// Çàïóñê ïðîãðàììû: CTRL+F5 èëè ìåíþ "Îòëàäêà" > "Çàïóñê áåç îòëàäêè"
// Îòëàäêà ïðîãðàììû: F5 èëè ìåíþ "Îòëàäêà" > "Çàïóñòèòü îòëàäêó"

// Ñîâåòû ïî íà÷àëó ðàáîòû 
//   1. Â îêíå îáîçðåâàòåëÿ ðåøåíèé ìîæíî äîáàâëÿòü ôàéëû è óïðàâëÿòü èìè.
//   2. Â îêíå Team Explorer ìîæíî ïîäêëþ÷èòüñÿ ê ñèñòåìå óïðàâëåíèÿ âåðñèÿìè.
//   3. Â îêíå "Âûõîäíûå äàííûå" ìîæíî ïðîñìàòðèâàòü âûõîäíûå äàííûå ñáîðêè è äðóãèå ñîîáùåíèÿ.
//   4. Â îêíå "Ñïèñîê îøèáîê" ìîæíî ïðîñìàòðèâàòü îøèáêè.
//   5. Ïîñëåäîâàòåëüíî âûáåðèòå ïóíêòû ìåíþ "Ïðîåêò" > "Äîáàâèòü íîâûé ýëåìåíò", ÷òîáû ñîçäàòü ôàéëû êîäà, èëè "Ïðîåêò" > "Äîáàâèòü ñóùåñòâóþùèé ýëåìåíò", ÷òîáû äîáàâèòü â ïðîåêò ñóùåñòâóþùèå ôàéëû êîäà.
//   6. ×òîáû ñíîâà îòêðûòü ýòîò ïðîåêò ïîçæå, âûáåðèòå ïóíêòû ìåíþ "Ôàéë" > "Îòêðûòü" > "Ïðîåêò" è âûáåðèòå SLN-ôàéë.
