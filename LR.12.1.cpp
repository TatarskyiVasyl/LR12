// LR.12.1.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.1
// Форматування і знищення динамічної мережної структури даних
// Варіант 26

#include <iostream>
#include <Windows.h>

using namespace std;

struct Elem {
    Elem* link1;
    Elem* link2;
    int info;
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Elem* p;

    // Блок 1
    p = new Elem;             // 1
    p->info = 1;              // 2

    // Блок 2
    p->link1 = new Elem;      // 3: верхня комірка Блоку 1 → Блок 2
    p->link1->info = 2;       // 4
    p->link1->link1 = NULL;   // 5: верхня комірка Блоку 2 — перекреслено

    // Блок 3
    p->link2 = new Elem;      // 6: нижня комірка Блоку 1 → Блок 3
    p->link2->info = 3;       // 7
    p->link2->link1 = p->link1; // 8: верхня комірка Блоку 3 → Блок 2
    p->link2->link2 = NULL;     // 9: нижня комірка Блоку 3 — перекреслено

    // Блок 4
    p->link1->link2 = new Elem;         // 10: нижня комірка Блоку 2 → Блок 4
    p->link1->link2->info = 4;          // 11
    p->link1->link2->link1 = p;         // 12: верхня комірка Блоку 4 → Блок 1
    p->link1->link2->link2 = p->link2;  // 13: нижня комірка Блоку 4 → Блок 3

    cout << "Мережну структуру успішно створено!" << endl;

    // Знищення у зворотному порядку
    delete p->link1->link2;   // 14: Блок 4
    delete p->link2;          // 15: Блок 3
    delete p->link1;          // 16: Блок 2
    delete p;                 // 17: Блок 1

    cout << "Пам'ять успішно очищено." << endl;

    return 0;
}