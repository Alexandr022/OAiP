// library.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "lab4.h"
#include "log.h"

Node* createNode(const char* word, Node* left, Node* right)
{
    Node* node = malloc(sizeof(*node));
    *node = (Node){ .word = "" };
    strcpy(node->word, word);
    node->left = left;
    node->right = right;
    return node;
}

void initNewTree(Node* root, FILE* outputFile)
{
    if (root == NULL) 
    {
        fprintf(outputFile, "%s\n", ZERO_STRING);
        return;
    }

    fprintf(outputFile, "%s\n", root->word);
    initNewTree(root->left, outputFile);
    initNewTree(root->right, outputFile);
}

char* deleteEndString(char* str)
{
    if (str == NULL)
    {
        return NULL;
    }

    for (size_t i = strlen(str); i > 0 && isspace(str[i - 1]); i--)
    {
        str[i - 1] = '\0';
    }

    return str;
}

Node* initTree(FILE* inputFile)
{
    Node* node = malloc(sizeof(*node));
    *node = (Node){ .word = "" };

    if (fgets(node->word, LENGTH, inputFile) == NULL)
    {
        free(node);
        return NULL;
    }

    deleteEndString(node->word);

    if (strcmp(node->word, ZERO_STRING) == 0) 
    {
        free(node);
        return NULL;
    }

    node->left = initTree(inputFile);
    node->right = initTree(inputFile);

    return node;
}

void rewriteDatabased(Node* node) 
{
    printf("\nI give up. Tell me what you wished for.\n>");

    String answer = getStringFromKayboard("");

    createLog(">%s", logOutput, answer.String);

    printf("\nWhat question would you advise to ask?\n>");

    String question = getStringFromKayboard("");

    createLog(">%s", logOutput, question.String);

    node->left = createNode(node->word, NULL, NULL);
    node->right = createNode(answer.String, NULL, NULL);

    strcpy(node->word, question.String);
}

void gameTree(Node* root) 
{
    createLog("Question: %s", root->word);

    printf("%s?\n1.No\n2.Yes\n>", root->word);

    int choice = getIntFromKayboard("");

    createLog(">%d", choice);

    if (!(root->right == NULL || root->left == NULL)) 
    {
        if (choice == 1)
        {
            gameTree(root->left);
        }
        if (choice == 2)
        {
            gameTree(root->right);
        }
    }

    if (root->right == NULL && root->left == NULL) 
    {

        if (choice == 1)
        {
            rewriteDatabased(root);
        }
        if (choice == 2)
        {
            printf("\nEnd!!!\n");
        }
    }
}

void freeTree(Node* node) 
{
    if (node == NULL) 
    {
        return;
    }

    freeTree(node->left);
    freeTree(node->right);
    free(node);
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
