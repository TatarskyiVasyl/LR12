// LR.12.3.rec.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.3.rec
// Опрацювання лінійного двонаправленого списку
// Варіант 26

#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
    int info;
    Node* next;
    Node* prev;
};

void addToEnd(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->next = NULL;
    newNode->prev = tail;

    if (tail == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void createList(Node*& head, Node*& tail, int n, int i = 1) {
    if (i > n)
        return;
    int val;
    cout << "Введіть елемент " << i << ": ";
    cin >> val;
    addToEnd(head, tail, val);
    createList(head, tail, n, i + 1);
}

void printList(Node* head) {
    if (head == NULL) {
        cout << endl;
        return;
    }
    cout << head->info;
    if (head->next != NULL) cout << " <-> ";
    printList(head->next);
}

void insertAfterV1(Node* curr, Node*& tail, int V1, int V2) {
    if (curr == NULL)
        return;

    Node* nextNode = curr->next;

    if (curr->info == V1) {
        Node* newNode = new Node;
        newNode->info = V2;
        newNode->next = curr->next;
        newNode->prev = curr;

        if (curr->next != NULL)
            curr->next->prev = newNode;
        else
            tail = newNode;

        curr->next = newNode;

        insertAfterV1(newNode->next, tail, V1, V2);
    }
    else {
        insertAfterV1(nextNode, tail, V1, V2);
    }
}

void deleteList(Node*& head, Node*& tail) {
    if (head == NULL) {
        tail = NULL;
        return;
    }
    Node* temp = head->next;
    delete head;
    head = temp;
    if (head != NULL)
        head->prev = NULL;
    deleteList(head, tail);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;
    cout << "Введіть кількість елементів: ";
    cin >> n;

    Node* head = NULL;
    Node* tail = NULL;
    createList(head, tail, n);

    cout << "\nСписок до змін:    ";
    printList(head);

    int V1, V2;
    cout << "Введіть V1 (після якого вставляти): ";
    cin >> V1;
    cout << "Введіть V2 (значення нового елемента): ";
    cin >> V2;

    insertAfterV1(head, tail, V1, V2);

    cout << "Список після змін: ";
    printList(head);

    deleteList(head, tail);

    return 0;
}