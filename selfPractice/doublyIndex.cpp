#include <iostream>
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

void insert()
{
    struct doubleLinkedList *temp = new struct doubleLinkedList;
    temp->next = NULL;
    temp->prev = NULL;
    cout << "Enter data: " << endl;
    cin >> temp->data;
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
void handleMid()
{
    if (noOfElements == 1)
    {
        median = start->data;
        return;
    }
    else if (noOfElements == 2)
    {
        median = (start->data + start->next->data) / 2;
        return;
    }
    else
    {
        struct doubleLinkedList *fast = start;
        struct doubleLinkedList *slow = start;
        while (fast->next != NULL && fast->next->next != NULL)

        {
            fast = fast->next->next;
            slow = slow->next;
        }

        if (noOfElements % 2 == 0)
        {
            median = (slow->data + fast->data) / 2;
        }
        else if (noOfElements % 2 != 0)
        {
            median = slow->data;
        }
    }
}

void getElementByIndex(int index)
{
    struct doubleLinkedList *curr = start;
    while (curr != NULL)
    {
        if (curr->index == index)
        {
            cout << "Data: " << curr->data << " | Index: " << curr->index << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Element with index " << index << " not found." << endl;
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

void deleteAtEnd()
{
    if (start == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }

    struct doubleLinkedList *temp = start;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    if (temp == start)
    {
        // Only one node in the list
        delete start;
        start = NULL;
    }
    else
    {
        temp->prev->next = NULL; // Update previous node's 'next'
        delete temp;
    }
}

void search()
{
    int toSearchData;
    int searchFlag = 0;
    cout << "Enter the data of element you want to search: " << endl;
    cin >> toSearchData;
    struct doubleLinkedList *curr = start;
    while (curr != NULL)
    {
        if (curr->data == toSearchData)
        {
            searchFlag = 1;
            break;
        }
        curr = curr->next;
    }
    if (searchFlag == 0)
    {
        cout << "Element not present in list" << endl;
    }
    else
    {
        cout << "Found | Data: " << curr->data << endl;
    }
}

void printMenu()
{
    cout << "Menu:\n";
    cout << "1. Insert a node\n";
    cout << "2. Delete a node\n";
    cout << "3. Search for a node\n";
    cout << "4. Print the linked list\n";
    cout << "5. Access element through index\n";
    cout << "6. See the Menu again\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    int input;
    cout << "For Menu Press 6 To Exit Press 7\n";
    cin >> input;
    if (input == 6)
    {
        printMenu();
    }
    cin >> input;
    while (input != 7)
    {
        if (input == 1)
        {
            while (input == 1)
            {
                insert();
                handleMid();
                cout << " Meidan: " << median << endl;
                cout << "Do you want to enter a node if yes press 1" << endl;
                cin >> input;
            }
        }
        else if (input == 4)
        {
            print();
        }
        else if (input == 2)
        {
            deleteAtEnd();
        }
        else if (input == 3)
        {
            search();
        }
        else if (input == 7)
        {
            break;
        }
        else if (input == 6)
        {
            printMenu();
        }
        else if (input == 5)
        {
            int indexInput;
            cout << "Enter the Index You Want to Access : \n";
            cin >> indexInput;
            getElementByIndex(indexInput);
        }
        else
        {
            cout << "Invalid Choice.." << endl;
        }
        cout << "For Menu Press 6 To Exit Press 7\n";
        cin >> input;
    }
    handleMid();
    return 0;
}