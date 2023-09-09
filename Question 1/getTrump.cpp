#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct doubleLinkedList
{
    int data;
    struct doubleLinkedList *next;
    struct doubleLinkedList *prev;
};

struct doubleLinkedList *start = NULL;
struct doubleLinkedList *middleElement = NULL;
struct doubleLinkedList *secondMiddleElement = NULL;
int noOfElements = 0;

void insert(int data)
{
    struct doubleLinkedList *temp = new doubleLinkedList();
    temp->next = NULL;
    temp->prev = NULL;

    temp->data = data;

    if (start == NULL)
    {
        start = temp;
    }
    else
    {
        struct doubleLinkedList *curr = start;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = temp;
        temp->prev = curr;
    }

    noOfElements++;
}

void deleteAtEnd()
{
    if (start == NULL)
    {
        cout << "List is empty." << endl;
        cout << "No of elements: " << noOfElements << endl;
        return;
    }
    if (noOfElements % 2 != 0)
    {
        middleElement = middleElement->prev;
    }
    else if (noOfElements % 2 == 0)
    {
        secondMiddleElement = secondMiddleElement->prev;
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
        middleElement = start;
        secondMiddleElement = start;
        noOfElements--;
    }
    else
    {

        temp->prev->next = NULL; // Update previous node's 'next'
        delete temp;
        noOfElements--;
    }

    // cout << "No of elements: " << noOfElements << endl;
    if (start == NULL)
    {
        cout << "No elements Present " << endl;
        return;
    }
    // if (noOfElements % 2 != 0)
    // {

    //     cout << "Middle element : "
    //          << "Data: " << middleElement->data << endl;
    // }
    // else if (noOfElements % 2 == 0)
    // {
    //     cout << "Middle element : "
    //          << "Data: " << middleElement->data << endl;

    //     cout << "Second Middle element : "
    //          << "Data: " << secondMiddleElement->data << endl;
    // }
}

void print()
{
    struct doubleLinkedList *curr = start;
    while (curr != NULL)
    {
        cout << "Data: " << curr->data << endl;
        curr = curr->next;
    }
    return;
    cout << "No elements to display" << endl;
}

void getTrump()
{
    if (noOfElements == 1)
    {
        middleElement = start;
        secondMiddleElement = start;
    }
    else if (noOfElements % 2 != 0)
    {
        middleElement = middleElement->next;
    }
    else if (noOfElements % 2 == 0)
    {
        secondMiddleElement = middleElement->next;
    }
}
void printMiddleElement()
{
    if (noOfElements == 1)
    {
        cout << "Middle element : "
             << "Data: " << middleElement->data << endl;
    }
    else if (noOfElements % 2 != 0)
    {
        cout << "Middle element : "
             << "Data: " << middleElement->data << endl;
    }
    else if (noOfElements % 2 == 0)
    {
        cout << "Middle element : "
             << "Data: " << middleElement->data << " | "
             << "Second Middle element : "
             << "Data: " << secondMiddleElement->data << endl;
    }
}
int main()
{
    string inputChoice;
    int inputdata;

    ifstream inputFile("Test04.txt"); // Open the input file
    if (!inputFile)
    {
        cerr << "Error: Cannot open input file." << endl;
        return 1;
    }

    while (inputFile >> inputChoice)
    {
        if (inputChoice == "ADD")
        {
            inputFile >> inputdata;
            insert(inputdata);
            getTrump();
        }
        else if (inputChoice == "DELETE")
        {
            deleteAtEnd();
        }
        else if (inputChoice == "END")
        {
            break;
        }
        else
        {
            cerr << "Invalid command in input file: " << inputChoice << endl;
        }
    }

    inputFile.close(); // Close the input file
    printMiddleElement();

    return 0;
}