// LR.12.2.rec.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.2.rec
// Опрацювання лінійного однонаправленого списку
// Варіант 26

#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
    int info;
    Node* next;
};

void addToEnd(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = newNode;
}

Node* createList(int n) {
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        cout << "Введіть елемент " << (i + 1) << ": ";
        cin >> val;
        addToEnd(head, val);
    }
    return head;
}

void printList(Node* head) {
    if (head == NULL) {
        cout << endl;
        return;
    }
    cout << head->info;
    if (head->next != NULL) cout << " -> ";
    printList(head->next);
}

void increaseAll(Node* head, int delta) {
    if (head == NULL)
        return;
    head->info += delta;
    increaseAll(head->next, delta);
}

void deleteList(Node*& head) {
    if (head == NULL)
        return;
    Node* temp = head->next;
    delete head;
    head = temp;
    deleteList(head);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;
    cout << "Введіть кількість елементів: ";
    cin >> n;

    Node* head = createList(n);

    cout << "\nСписок до змін:    ";
    printList(head);

    int delta;
    cout << "Введіть величину збільшення: ";
    cin >> delta;

    increaseAll(head, delta);

    cout << "Список після змін: ";
    printList(head);

    deleteList(head);

    return 0;
}