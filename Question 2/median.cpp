#include <iostream>
#include <fstream>
using namespace std;

struct doubleLinkedList
{
    float data;
    int index;
    struct doubleLinkedList *next;
    struct doubleLinkedList *prev;
} *start = NULL;

int currentIndex = 0;
int noOfElements = 0;
float median = 0.00;

struct doubleLinkedList *mid = NULL;
struct doubleLinkedList *midSecond = NULL;

void insert(float data)
{
    struct doubleLinkedList *temp = new struct doubleLinkedList;
    temp->next = NULL;
    temp->prev = NULL;

    temp->data = data;
    temp->index = currentIndex++;

    if (start == NULL || temp->data < start->data)
    {
        // Insert at the beginning of the list or when the list is empty.
        temp->next = start;
        if (start != NULL)
        {
            start->prev = temp;
        }
        start = temp;
        mid = start;
        midSecond = start;
    }
    else
    {
        struct doubleLinkedList *curr = start;
        while (curr->next != NULL && temp->data >= curr->next->data)
        {
            curr = curr->next;
        }

        // Insert after 'curr'.
        temp->next = curr->next;
        temp->prev = curr;
        if (curr->next != NULL)
        {
            curr->next->prev = temp;
        }
        curr->next = temp;
    }
    noOfElements++;
}
struct doubleLinkedList *getElementByIndex(int index)
{
    struct doubleLinkedList *curr = start;
    while (curr != NULL)
    {
        if (curr->index == index)
        {
            return curr;
        }
        curr = curr->next;
    }
    cout << "Element with index " << index << " not found." << endl;
}

void handleMid()
{
    if (noOfElements == 1)
    {
        median = start->data;
    }
    else if (noOfElements % 2 == 0)
    {
        struct doubleLinkedList *fast = start;
        struct doubleLinkedList *slow = start;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        median = (slow->data + slow->next->data) / 2;
    }
    else
    {
        struct doubleLinkedList *slow = start;
        struct doubleLinkedList *fast = start;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        median = slow->data;
    }
}

void print()
{
    struct doubleLinkedList *curr = start;
    while (curr != NULL)
    {
        cout << "Data: " << curr->data << endl;
        curr = curr->next;
    }
}

int main()
{
    ifstream inputFile("Test04.txt"); // Open the input file
    if (!inputFile)
    {
        cerr << "Error: Cannot open input file." << endl;
        return 1;
    }

    float data;
    while (inputFile >> data)
    {
        insert(data);
        handleMid();
        cout << "Median: " << median << endl;
    }

    inputFile.close(); // Close the input file
    print();

    return 0;
}
