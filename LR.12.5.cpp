// LR.12.5.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.5
// Стеки
// Варіант 26

#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
    int info;
    Node* next;
};

bool isEmpty(Node* top) {
    return top == NULL;
}

void printStack(Node* top) {
    if (isEmpty(top)) {
        cout << "Стек порожній" << endl;
        return;
    }
    Node* curr = top;
    cout << "Вершина -> ";
    while (curr != NULL) {
        cout << curr->info;
        if (curr->next != NULL) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

void pushStack(Node*& top, int value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->next = top;
    top = newNode;
}

bool popStack(Node*& top, int& value) {
    if (isEmpty(top))
        return false;
    Node* temp = top;
    value = top->info;
    top = top->next;
    delete temp;
    return true;
}

bool searchStack(Node* top, int value) {
    Node* curr = top;
    while (curr != NULL) {
        if (curr->info == value)
            return true;
        curr = curr->next;
    }
    return false;
}

void clearStack(Node*& top) {
    while (!isEmpty(top)) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Node* top = NULL;
    int choice, value;

    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Перевірити стек на пустоту\n";
        cout << "2. Вивести стек\n";
        cout << "3. Додати елемент у вершину\n";
        cout << "4. Витягти елемент з вершини\n";
        cout << "5. Пошук значення в стеку\n";
        cout << "6. Очистити стек\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (isEmpty(top))
                cout << "Стек порожній." << endl;
            else
                cout << "Стек не порожній." << endl;
            break;

        case 2:
            printStack(top);
            break;

        case 3:
            cout << "Введіть значення: ";
            cin >> value;
            pushStack(top, value);
            cout << "Елемент " << value << " додано." << endl;
            break;

        case 4:
            if (popStack(top, value))
                cout << "Витягнуто елемент: " << value << endl;
            else
                cout << "Стек порожній — витягти неможливо." << endl;
            break;

        case 5:
            cout << "Введіть значення для пошуку: ";
            cin >> value;
            if (searchStack(top, value))
                cout << "Значення " << value << " знайдено в стеку." << endl;
            else
                cout << "Значення " << value << " не знайдено." << endl;
            break;

        case 6:
            clearStack(top);
            cout << "Стек очищено." << endl;
            break;

        case 0:
            cout << "Вихід." << endl;
            break;

        default:
            cout << "Невірний вибір." << endl;
        }
    } while (choice != 0);

    clearStack(top);
    return 0;
}