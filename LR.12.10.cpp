// LR.12.10.cpp
// Татарський Василь Петрович
// Лабораторна робота №12.10
// Дерева
// Варіант 26

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <Windows.h>

struct Node {
    std::string identifier;
    int         count;
    Node* left;
    Node* right;

    Node(const std::string& id)
        : identifier(id), count(1), left(nullptr), right(nullptr) {
    }
};

const std::set<std::string> KEYWORDS = {
    "alignas","alignof","and","and_eq","asm","auto","bitand","bitor","bool",
    "break","case","catch","char","char8_t","char16_t","char32_t","class",
    "compl","concept","const","consteval","constexpr","constinit","const_cast",
    "continue","co_await","co_return","co_yield","decltype","default","delete",
    "do","double","dynamic_cast","else","enum","explicit","export","extern",
    "false","float","for","friend","goto","if","inline","int","long","mutable",
    "namespace","new","noexcept","not","not_eq","nullptr","operator","or",
    "or_eq","private","protected","public","register","reinterpret_cast",
    "requires","return","short","signed","sizeof","static","static_assert",
    "static_cast","struct","switch","template","this","thread_local","throw",
    "true","try","typedef","typeid","typename","union","unsigned","using",
    "virtual","void","volatile","wchar_t","while","xor","xor_eq","override",
    "final","import","module"
};

Node* insertNode(Node* root, const std::string& id) {
    if (root == nullptr)
        return new Node(id);

    if (id < root->identifier)
        root->left = insertNode(root->left, id);
    else if (id > root->identifier)
        root->right = insertNode(root->right, id);
    else
        root->count++;

    return root;
}

Node* searchNode(Node* root, const std::string& id) {
    if (root == nullptr || root->identifier == id)
        return root;

    if (id < root->identifier)
        return searchNode(root->left, id);
    else
        return searchNode(root->right, id);
}

Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, const std::string& id) {
    if (root == nullptr) {
        std::cout << "Ідентифікатор \"" << id << "\" не знайдено.\n";
        return nullptr;
    }

    if (id < root->identifier) {
        root->left = deleteNode(root->left, id);
    }
    else if (id > root->identifier) {
        root->right = deleteNode(root->right, id);
    }
    else {
        if (root->left == nullptr) {
            Node* tmp = root->right;
            delete root;
            return tmp;
        }
        else if (root->right == nullptr) {
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        Node* successor = findMin(root->right);
        root->identifier = successor->identifier;
        root->count = successor->count;
        root->right = deleteNode(root->right, successor->identifier);
    }
    return root;
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    std::cout << root->identifier << " : " << root->count << "\n";
    inOrder(root->right);
}

void destroyTree(Node* root) {
    if (root == nullptr) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

bool isIdentifier(const std::string& s) {
    if (s.empty()) return false;
    if (!std::isalpha((unsigned char)s[0]) && s[0] != '_') return false;
    for (char c : s)
        if (!std::isalnum((unsigned char)c) && c != '_') return false;
    return true;
}

Node* parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Помилка: не вдалося відкрити файл \"" << filename << "\"\n";
        return nullptr;
    }

    Node* root = nullptr;
    std::string token;
    char c;
    bool inLineComment = false;
    bool inBlockComment = false;
    bool inString = false;
    bool inChar = false;

    auto flush = [&]() {
        if (!token.empty()) {
            if (isIdentifier(token) && KEYWORDS.find(token) == KEYWORDS.end())
                root = insertNode(root, token);
            token.clear();
        }
        };

    char prev = '\0';
    while (file.get(c)) {
        if (inLineComment) {
            if (c == '\n') inLineComment = false;
            prev = c;
            continue;
        }
        if (inBlockComment) {
            if (prev == '*' && c == '/') inBlockComment = false;
            prev = c;
            continue;
        }
        if (inString) {
            if (c == '"' && prev != '\\') inString = false;
            prev = c;
            continue;
        }
        if (inChar) {
            if (c == '\'' && prev != '\\') inChar = false;
            prev = c;
            continue;
        }

        if (prev == '/' && c == '/') { flush(); inLineComment = true; prev = c; continue; }
        if (prev == '/' && c == '*') { flush(); inBlockComment = true; prev = c; continue; }
        if (c == '"') { flush(); inString = true; prev = c; continue; }
        if (c == '\'') { flush(); inChar = true; prev = c; continue; }

        if (std::isalnum((unsigned char)c) || c == '_') {
            token += c;
        }
        else {
            flush();
        }
        prev = c;
    }
    flush();
    file.close();
    return root;
}

void printMenu() {
    std::cout << "\n=== МЕНЮ ===\n"
        << "1. Завантажити та розібрати C++ файл\n"
        << "2. Вивести всі ідентифікатори (алфавітний порядок)\n"
        << "3. Знайти ідентифікатор\n"
        << "4. Видалити ідентифікатор\n"
        << "5. Вийти\n"
        << "Вибір: ";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    Node* root = nullptr;
    int   choice;

    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string filename;
            std::cout << "Введіть ім'я файлу: ";
            std::getline(std::cin, filename);

            destroyTree(root);
            root = parseFile(filename);

            if (root)
                std::cout << "Файл успішно розібрано.\n";
            break;
        }
        case 2: {
            if (root == nullptr) {
                std::cout << "Дерево порожнє. Спочатку завантажте файл.\n";
            }
            else {
                std::cout << "\nІдентифікатор : кількість входжень\n"
                    << "-----------------------------------\n";
                inOrder(root);
            }
            break;
        }
        case 3: {
            std::string id;
            std::cout << "Введіть ідентифікатор для пошуку: ";
            std::getline(std::cin, id);

            Node* found = searchNode(root, id);
            if (found)
                std::cout << "Знайдено: \"" << found->identifier
                << "\", входжень: " << found->count << "\n";
            else
                std::cout << "Ідентифікатор \"" << id << "\" не знайдено.\n";
            break;
        }
        case 4: {
            std::string id;
            std::cout << "Введіть ідентифікатор для видалення: ";
            std::getline(std::cin, id);

            root = deleteNode(root, id);
            std::cout << "Видалення виконано.\n";
            break;
        }
        case 5:
            std::cout << "До побачення!\n";
            break;
        default:
            std::cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 5);

    destroyTree(root);
    return 0;
}