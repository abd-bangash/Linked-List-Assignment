#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node
{
    int data;
    struct node *next;
} *start = NULL;

struct node *thirdLastElement = nullptr;
int noOfElements = 0;

void insertAtEnd(int data)
{
    struct node *newNode = new node();
    newNode->data = data;
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
    noOfElements++;

    // maintaining the third last element
    if (noOfElements == 3)
    {
        thirdLastElement = start;
    }
    else if (noOfElements > 3)
    {
        thirdLastElement = thirdLastElement->next;
    }
}

int thirdLastFinder()
{
    if (noOfElements < 3)
    {
        return -1;
    }
    else
    {
        return thirdLastElement->data;
    }
}

void printList()
{
    struct node *temp = start;
    while (temp != NULL)
    {
        cout << "Number : " << temp->data << endl;
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void insertFromFile(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    int data;
    while (inputFile >> data)
    {
        insertAtEnd(data);
    }

    inputFile.close();
}

int main()
{
    insertFromFile("Test05.txt"); // Replace "input.txt" with your input file name

    cout << thirdLastFinder();

    return 0;
}
