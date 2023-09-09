#include <iostream>
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
    string input;
    int tid;
    do
    {
        cout << "Add || Delete || Print || End " << endl;
        cin >> input;
        if (input == "Add")
        {
            cout << "Enter the transaction id: " << endl;
            cin >> tid;
            insertAtEnd(tid);
        }
        else if (input == "Delete")
        {
            cout << "Enter the fraudulent transaction id: " << endl;
            cin >> tid;
            deleteANode(tid);
        }
        else if (input == "Print")
        {
            printList();
        }
        else if (input == "End")
        {
        }
        else
        {
            cout << "Invalid Choice" << endl;
        }
    } while (input != "End");
    return 0;
}