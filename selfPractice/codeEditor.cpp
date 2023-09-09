#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
struct doubleLinkedList
{
    int data;
    int index;
    struct doubleLinkedList *next;
    struct doubleLinkedList *prev;
} *start = nullptr;
int ind = 0;
int cursorPosition = 0;
stack<doubleLinkedList *> history;
// functions :

// saves the last state of list
void saveState()
{
    doubleLinkedList *copy = nullptr;
    doubleLinkedList *current = start;
    doubleLinkedList *prevCopy = nullptr;

    while (current != nullptr)
    {
        struct doubleLinkedList *newNode = (struct doubleLinkedList *)malloc(sizeof(struct doubleLinkedList));
        newNode->data = current->data;
        newNode->index = current->index;
        newNode->next = nullptr;
        newNode->prev = prevCopy;

        if (prevCopy != nullptr)
        {
            prevCopy->next = newNode;
        }
        else
        {
            copy = newNode;
        }

        prevCopy = newNode;
        current = current->next;
    }

    history.push(copy);
}
// insert at end
void insert(int data)
{
    saveState();
    if (start == nullptr)
    {
        struct doubleLinkedList *temp = (struct doubleLinkedList *)malloc(sizeof(struct doubleLinkedList));
        temp->next = nullptr;
        temp->prev = nullptr;
        temp->data = data;
        temp->index = ind;
        ind++;
        start = temp;
    }
    else
    {
        struct doubleLinkedList *curr = start;
        struct doubleLinkedList *temp = (struct doubleLinkedList *)malloc(sizeof(struct doubleLinkedList));
        temp->next = nullptr;
        temp->prev = nullptr;
        temp->data = data;
        temp->index = ind;
        ind++;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = temp;
        temp->prev = curr;
    }
}
// print the whole list
void print()
{
    struct doubleLinkedList *curr = start;
    while (curr != nullptr)
    {
        cout << "[ " << curr->index << curr->data << ",";
        curr = curr->next;
    }
    cout << "]" << endl;
}
// search the linked list by index and return node
struct doubleLinkedList *search(int toSearchIndex)
{
    struct doubleLinkedList *curr = start;
    while (curr != nullptr)
    {
        if (curr->index == toSearchIndex)
        {
            return curr;
        }
        cout << curr->index << endl;
        curr = curr->next;
    }
    cout << "Element with index : " << toSearchIndex << " not found in list" << endl;
    return nullptr;
}
// insert at a specific index
void insertAtIndex(int index, int data)
{
    saveState();

    struct doubleLinkedList *curr = search(index);
    if (curr->prev == nullptr)
    {
        struct doubleLinkedList *temp = (struct doubleLinkedList *)malloc(sizeof(struct doubleLinkedList));
        temp->next = start;
        temp->prev = nullptr;
        temp->data = data;
        temp->index = index;
        start->prev = temp;
        start = temp;
        ind++;
    }
    else
    {
        struct doubleLinkedList *temp = (struct doubleLinkedList *)malloc(sizeof(struct doubleLinkedList));
        temp->data = data;
        temp->index = index;
        temp->next = curr;
        temp->prev = curr->prev;
        curr->prev->next = temp;
        curr->prev = temp;
        curr->next = curr->next;
        ind++;
    }
    while (curr != nullptr)
    {
        curr->index++;
        curr = curr->next;
    }
}
// delete at a specific index
void deleteNode(int deleteIndex)
{
    saveState();
    int searchFlag = 0;
    doubleLinkedList *temp = search(deleteIndex);
    if (temp != nullptr)
    {
        if (temp->index == start->index)
        {
            start = start->next;
            cursorPosition = 0;
        }
        else
        {
            if (temp->prev != nullptr)
            {
                temp->prev->next = temp->next;
            }
            else
            {
                start = temp->next;
            }

            if (temp->next != nullptr)
            {
                temp->next->prev = temp->prev;
            }
        }
        while (temp != nullptr)
        {
            temp->index--;
            temp = temp->next;
        }
        free(temp);
        ind--;
    }
}
// delete at end
void deleteAtEnd()
{
    saveState();
    if (start == nullptr)
    {
        cout << "List is empty." << endl;
        return;
    }

    struct doubleLinkedList *temp = start;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    if (temp == start)
    {
        // Only one node in the list
        delete start;
        start = nullptr;
    }
    else
    {
        temp->prev->next = nullptr; // Update previous node's 'next'
        delete temp;
    }
}
// insert just after the current cursor position
void insertImmediate(int data)
{
    saveState();
    insertAtIndex(cursorPosition + 1, data);
}
// delete the current cursor position
void deleteImmediate()
{
    saveState();
    deleteNode(cursorPosition);
}
// move the cursor forward by index
void moveCursorForward(int steps)
{
    saveState();
    int count = 0;
    if (cursorPosition + steps < ind)
    {
        cursorPosition += steps;
    }
    else
    {
        cout << "index out of bound" << endl;
    }
}
// move the cursor backward by index
void moveCursorBackward(int steps)
{
    saveState();
    int count = 0;
    if (cursorPosition - steps >= 0)
    {
        cursorPosition -= steps;
    }
    else
    {
        cout << "index out of bound" << endl;
    }
}
// update the data of given index
void updateData(int index, int data)
{
    saveState();
    struct doubleLinkedList *curr = search(index);
    curr->data = data;
}
// update the data of cursor position
void updateImmediate(int data)
{
    saveState();
    updateData(cursorPosition, data);
}
// print the data of current cursor position
void printCursor()
{
    struct doubleLinkedList *curr = search(cursorPosition);
    if (curr != nullptr)
    {
        cout << "[ " << curr->index << "] "
             << "Data: " << curr->data << endl;
    }
}
// shift the data of cursor with mentioned index
void shift(int index)
{
    saveState();
    struct doubleLinkedList *curr = search(index);
    struct doubleLinkedList *temp = search(cursorPosition);
    int tempData;
    tempData = curr->data;
    curr->data = temp->data;
    temp->data = tempData;
}

// undo
void undo()
{
    if (!history.empty())
    {
        doubleLinkedList *previousState = history.top();
        history.pop();

        while (start != nullptr)
        {
            doubleLinkedList *temp = start;
            start = start->next;
            delete temp;
        }

        start = previousState;
    }
    else
    {
        cout << "No history to undo." << endl;
    }
}
//
void readFromFile(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    // Initialize your linked list and cursor as needed

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "Add")
        {
            int arg1;
            iss >> arg1;

            if (iss.eof())
            {
                insert(arg1);
            }
            else
            {
                int arg2;
                iss >> arg2;
                insertAtIndex(arg1, arg2);
            }
        }
        else if (command == "Delete")
        {

            if (iss.eof())
            {
                deleteAtEnd();
            }
            else
            {
                int arg1;
                iss >> arg1;
                deleteNode(arg1);
            }
        }
        else if (command == "MoveForward")
        {
            int arg1;
            iss >> arg1;
            moveCursorForward(arg1);
        }
        else if (command == "MoveBackward")
        {
            int arg1;
            iss >> arg1;
            moveCursorBackward(arg1);
        }
        else if (command == "AddImmediate")
        {
            int arg1;
            iss >> arg1;
            insertImmediate(arg1);
        }
        else if (command == "DeleteImmediate")
        {
            deleteImmediate();
        }
        else if (command == "UpdateImmediate")
        {
            int arg1;
            iss >> arg1;
            updateImmediate(arg1);
        }
        else if (command == "Update")
        {
            int arg1;
            iss >> arg1;
            int arg2;
            iss >> arg2;
            updateData(arg1, arg2);
        }
        else if (command == "Print")
        {
            printCursor();
        }
        else if (command == "Shift")
        {
            int arg1;
            iss >> arg1;
            shift(arg1);
        }
        else if (command == "Undo")
        {
            undo();
        }

        // Add more conditions for other commands as needed
    }

    inputFile.close();
}

// prints a menu
void printMenu()
{
    cout << "Menu:\n";
    cout << "1. Insert a node\n";
    cout << "2. Delete a node\n";
    cout << "3. Search for a node\n";
    cout << "4. Print the linked list\n";
    cout << "7.Move cursor forward\n";
    cout << "8.Move cursor backward\n";
    cout << "9.add a node at a specific index\n";
    cout << "10.add immediate\n";
    cout << "11.delete immediate\n";
    cout << "12.print the whole list\n";
    cout << "13.update the data at a specific index\n";
    cout << "14.update data immediate\n";
    cout << "15.shift \n";
    cout << "16.undo \n";
    cout << "5.See the Menu again.\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    int input;
    int inputdata;
    int searchIndex;
    int deleteIndex;
    int step;
    int indexInput;
    cout << "For Menu Press 5 To Exit Press 6\n";
    cin >> input;
    if (input == 5)
    {
        printMenu();
    }
    cin >> input;
    while (input != 6)
    {
        if (input == 1)
        {
            while (input == 1)
            {
                cout << "Enter the data" << endl;
                cin >> inputdata;
                insert(inputdata);
                cout << "Do you want to enter a node if yes press 1" << endl;
                cin >> input;
            }
        }
        else if (input == 4)
        {
            printCursor();
        }
        else if (input == 2)
        {
            cout << "Enter the index of element you want to delete " << endl;
            cin >> deleteIndex;
            deleteNode(deleteIndex);
        }
        else if (input == 3)
        {
            cout << "Enter the index you want to search" << endl;
            cin >> searchIndex;
            doubleLinkedList *temp = search(searchIndex);
            if (temp != nullptr)
            {
                cout << "Data : " << temp->data << endl;
            }
        }
        else if (input == 6)
        {
            break;
        }
        else if (input == 5)
        {
            printMenu();
        }
        else if (input == 7)
        {
            cout << "Enter the number of you want to move forward: " << endl;
            cin >> step;
            moveCursorForward(step);
        }
        else if (input == 8)
        {
            cout << "Enter the number of you want to move backward: " << endl;
            cin >> step;
            moveCursorBackward(step);
        }
        else if (input == 9)
        {
            cout << "Enter the index where you want add a node : " << endl;
            cin >> indexInput;
            cout << "Enter the data : " << endl;
            cin >> inputdata;
            insertAtIndex(indexInput, inputdata);
        }
        else if (input == 10)
        {
            cout << "Enter the data : " << endl;
            cin >> inputdata;
            insertImmediate(inputdata);
        }
        else if (input == 11)
        {
            deleteImmediate();
        }
        else if (input == 12)
        {
            print();
        }
        else if (input == 13)
        {
            cout << "Enter the index where you want to update data : " << endl;
            cin >> indexInput;
            cout << "Enter the updated data : " << endl;
            cin >> inputdata;
            updateData(indexInput, inputdata);
        }
        else if (input == 14)
        {
            cout << "Enter the updated data : " << endl;
            cin >> inputdata;
            updateImmediate(inputdata);
        }
        else if (input == 15)
        {
            cout << "Enter the index you want to shift the data of with data of cursor : " << endl;
            cin >> indexInput;
            shift(indexInput);
        }
        else if (input == 16)
        {

            undo();
        }

        else
        {
            cout << "Invalid Choice.." << endl;
        }
        cout << "For Menu Press 5 To Exit Press 6\n";
        cin >> input;
    }
    return 0;
}