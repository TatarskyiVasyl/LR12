// LR.12.4.rec.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.4.rec
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

void createList(Node*& tail, int n, int i = 1) {
    if (i > n)
        return;
    int val;
    cout << "Введіть елемент " << i << ": ";
    cin >> val;
    addToEnd(tail, val);
    createList(tail, n, i + 1);
}

void printList(Node* curr, Node* head, bool first = true) {
    if (!first && curr == head) {
        cout << " (кільце)" << endl;
        return;
    }
    cout << curr->info;
    if (curr->next != head) cout << " -> ";
    printList(curr->next, head, false);
}

void printListWrapper(Node* tail) {
    if (tail == NULL) {
        cout << "Список порожній" << endl;
        return;
    }
    printList(tail->next, tail->next);
}

void splitList(Node* curr, Node* head, Node*& tail1, Node*& tail2) {
    if (curr->info > 0)
        addToEnd(tail1, curr->info);
    else if (curr->info < 0)
        addToEnd(tail2, curr->info);

    if (curr->next != head)
        splitList(curr->next, head, tail1, tail2);
}

void splitListWrapper(Node* tail, Node*& tail1, Node*& tail2) {
    tail1 = NULL;
    tail2 = NULL;
    if (tail == NULL)
        return;
    splitList(tail->next, tail->next, tail1, tail2);
}

void deleteList(Node* curr, Node* head, Node*& tail) {
    if (curr->next == head) {
        delete curr;
        tail = NULL;
        return;
    }
    Node* next = curr->next;
    delete curr;
    deleteList(next, head, tail);
}

void deleteListWrapper(Node*& tail) {
    if (tail == NULL)
        return;
    deleteList(tail->next, tail->next, tail);
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
    printListWrapper(tail);

    Node* tail1 = NULL;
    Node* tail2 = NULL;
    splitListWrapper(tail, tail1, tail2);

    cout << "Список L1 (додатні):  ";
    printListWrapper(tail1);

    cout << "Список L2 (від'ємні): ";
    printListWrapper(tail2);

    deleteListWrapper(tail);
    deleteListWrapper(tail1);
    deleteListWrapper(tail2);

    return 0;
}