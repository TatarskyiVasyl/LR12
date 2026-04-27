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
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->info;
        if (curr->next != NULL) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

void increaseAll(Node* head, int delta) {
    Node* curr = head;
    while (curr != NULL) {
        curr->info += delta;
        curr = curr->next;
    }
}

void deleteList(Node*& head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
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