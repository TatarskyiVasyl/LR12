// LR.12.3.iter.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.3.iter
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

Node* createList(Node*& head, Node*& tail, int n) {
    head = NULL;
    tail = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        cout << "Введіть елемент " << (i + 1) << ": ";
        cin >> val;
        addToEnd(head, tail, val);
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->info;
        if (curr->next != NULL) cout << " <-> ";
        curr = curr->next;
    }
    cout << endl;
}

void insertAfterV1(Node*& tail, int V1, int V2) {
    if (tail == NULL)
        return;
    Node* stopAt = tail;
    Node* curr = tail;

    Node* head = tail;
    while (head->prev != NULL)
        head = head->prev;

    curr = head;
    while (curr != NULL) {
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

            curr = newNode->next;
        }
        else {
            curr = nextNode;
        }
    }
}

void deleteList(Node*& head, Node*& tail) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
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

    insertAfterV1(tail, V1, V2);

    cout << "Список після змін: ";
    printList(head);

    deleteList(head, tail);

    return 0;
}