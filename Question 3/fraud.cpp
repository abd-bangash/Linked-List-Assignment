#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct node
{
    int transactionId;
    struct node *next;
} *start = NULL;

void insertAtEnd(int tid)
{
    struct node *newNode = new node();
    newNode->transactionId = tid;
    newNode->next = NULL;
    if (start == NULL)
    {
        start = newNode;
    }
    else
    {
        struct node *temp = start;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void deleteANode(int deleteTransactionId)
{
    int searchFlag = 0;
    struct node *curr = start;
    if (deleteTransactionId == start->transactionId)
    {
        start = start->next;
        free(curr);
        searchFlag = 1;
    }
    else
    {
        struct node *prev = start;
        curr = start->next;
        while (curr != NULL)
        {
            if (curr->transactionId == deleteTransactionId)
            {
                prev->next = curr->next;
                free(curr);
                searchFlag = 1;
                break;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        if (searchFlag == 0)
        {
            cout << "Element you are trying to delete is not present" << endl;
        }
    }
}

void printList()
{
    struct node *temp = start;
    while (temp != NULL)
    {
        cout << "Transaction Id :" << temp->transactionId << endl;
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    ifstream inputFile("Test05.txt"); // Open the input file
    string line;
    int numTransactions, numFraudulent;

    if (inputFile.is_open())
    {
        getline(inputFile, line);
        stringstream ss(line);
        ss >> numTransactions >> numFraudulent;

        for (int i = 0; i < numTransactions; i++)
        {
            getline(inputFile, line);
            stringstream ss(line);
            int tid;
            ss >> tid;
            insertAtEnd(tid);
        }

        for (int i = 0; i < numFraudulent; i++)
        {
            int tid;
            inputFile >> tid; // Read fraudulent transaction IDs from the file
            deleteANode(tid);
        }

        inputFile.close(); // Close the input file
    }
    else
    {
        cout << "Error opening the file." << endl;
    }
    printList();
    return 0;
}
