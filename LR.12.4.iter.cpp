// LR.12.4.iter.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.4.iter
// Опрацювання кільцевого однонаправленого списку
// Варіант 26

#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
    int info;
    Node* next;
};

void addToEnd(Node*& tail, int value) {
    Node* newNode = new Node;
    newNode->info = value;

    if (tail == NULL) {
        newNode->next = newNode;
        tail = newNode;
        return;
    }

    newNode->next = tail->next;
    tail->next = newNode;
    tail = newNode;
}

void createList(Node*& tail, int n) {
    tail = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        cout << "Введіть елемент " << (i + 1) << ": ";
        cin >> val;
        addToEnd(tail, val);
    }
}

void printList(Node* tail) {
    if (tail == NULL) {
        cout << "Список порожній" << endl;
        return;
    }
    Node* curr = tail->next;
    do {
        cout << curr->info;
        if (curr->next != tail->next) cout << " -> ";
        curr = curr->next;
    } while (curr != tail->next);
    cout << " (кільце)" << endl;
}

void splitList(Node* tail, Node*& tail1, Node*& tail2) {
    tail1 = NULL;
    tail2 = NULL;

    if (tail == NULL)
        return;

    Node* curr = tail->next;
    do {
        if (curr->info > 0)
            addToEnd(tail1, curr->info);
        else if (curr->info < 0)
            addToEnd(tail2, curr->info);
        curr = curr->next;
    } while (curr != tail->next);
}

void deleteList(Node*& tail) {
    if (tail == NULL)
        return;

    Node* head = tail->next;
    Node* curr = head;
    do {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    } while (curr != head);

    tail = NULL;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;
    cout << "Введіть кількість елементів: ";
    cin >> n;

    Node* tail = NULL;
    createList(tail, n);

    cout << "\nСписок L:  ";
    printList(tail);

    Node* tail1 = NULL;
    Node* tail2 = NULL;
    splitList(tail, tail1, tail2);

    cout << "Список L1 (додатні):  ";
    printList(tail1);

    cout << "Список L2 (від'ємні): ";
    printList(tail2);

    deleteList(tail);
    deleteList(tail1);
    deleteList(tail2);

    return 0;
}