#include <iostream>
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
int main()
{

    string input;
    int tid;
    do
    {
        cout << "Add || Print || Third-Last || End " << endl;
        cin >> input;
        if (input == "Add")
        {
            cout << "Enter the number: " << endl;
            cin >> tid;
            insertAtEnd(tid);
        }
        else if (input == "Print")
        {
            printList();
        }
        else if (input == "Third-Last")
        {
            cout << "Third Last Element is : " << thirdLastFinder() << endl;
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