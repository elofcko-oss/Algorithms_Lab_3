
#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Node {
    string name;
    int priority;
    Node* next;

    Node(const string& n, int p = 0)
        : name(n), priority(p), next(nullptr) {
    }
};

// Вывод списка
void printList(Node* head, bool showPriority = false) {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }

    int number = 1;

    while (head != nullptr) {
        cout << number++ << ". " << head->name;

        if (showPriority) {
            cout << " (приоритет: " << head->priority << ")";
        }

        cout << '\n';
        head = head->next;
    }
}

// Освобождение памяти
void clearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Добавление в приоритетную очередь
// Чем больше число, тем выше приоритет
void priorityInsert(Node*& head, const string& name, int priority) {
    Node* node = new Node(name, priority);

    if (head == nullptr || priority > head->priority) {
        node->next = head;
        head = node;
        return;
    }

    Node* current = head;

    while (current->next != nullptr &&
        current->next->priority >= priority) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

// Извлечение элемента с наивысшим приоритетом
void priorityRemove(Node*& head) {
    if (head == nullptr) {
        cout << "Приоритетная очередь пуста.\n";
        return;
    }

    Node* temp = head;

    cout << "Извлечён элемент: " << temp->name
        << ", приоритет: " << temp->priority << '\n';

    head = head->next;
    delete temp;
}

// Поиск элемента по имени
Node* priorityFind(Node* head, const string& name) {
    while (head != nullptr) {
        if (head->name == name) {
            return head;
        }

        head = head->next;
    }

    return nullptr;
}

// Удаление элемента по имени
bool priorityDelete(Node*& head, const string& name) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->name == name) {
            if (previous == nullptr) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

// Добавление в обычную очередь
void queueEnqueue(Node*& head, Node*& tail, const string& name) {
    Node* node = new Node(name);

    if (tail == nullptr) {
        head = node;
    }
    else {
        tail->next = node;
    }

    tail = node;
}

// Извлечение из обычной очереди
void queueDequeue(Node*& head, Node*& tail) {
    if (head == nullptr) {
        cout << "Очередь пуста.\n";
        return;
    }

    Node* temp = head;

    cout << "Извлечён элемент: " << temp->name << '\n';

    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete temp;
}

// Добавление в стек
void stackPush(Node*& top, const string& name) {
    Node* node = new Node(name);

    node->next = top;
    top = node;
}

// Извлечение из стека
void stackPop(Node*& top) {
    if (top == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }

    Node* temp = top;

    cout << "Извлечён элемент: " << temp->name << '\n';

    top = top->next;
    delete temp;
}

// Ввод непустого названия
string readName() {
    string name;

    getline(cin, name);

    if (name.empty()) {
        cout << "Название не должно быть пустым.\n";
        return "";
    }

    return name;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Node* priorityHead = nullptr;

    Node* queueHead = nullptr;
    Node* queueTail = nullptr;

    Node* stackTop = nullptr;

    int choice;

    do {
        cout << "\n===== ЛАБОРАТОРНАЯ РАБОТА №3 =====\n";
        cout << "1. Добавить в приоритетную очередь\n";
        cout << "2. Извлечь из приоритетной очереди\n";
        cout << "3. Показать приоритетную очередь\n";
        cout << "4. Найти элемент по имени\n";
        cout << "5. Удалить элемент по имени\n";
        cout << "6. Добавить в обычную очередь\n";
        cout << "7. Извлечь из обычной очереди\n";
        cout << "8. Показать обычную очередь\n";
        cout << "9. Добавить в стек\n";
        cout << "10. Извлечь из стека\n";
        cout << "11. Показать стек\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) {
            cout << "Ошибка ввода. Завершение программы.\n";
            break;
        }

        // Удаляем символ перевода строки после числа
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string name;
        int priority;

        switch (choice) {
        case 1:
            cout << "Введите название элемента: ";
            name = readName();

            if (name.empty()) {
                break;
            }

            cout << "Введите приоритет (больше = выше): ";

            if (!(cin >> priority)) {
                cout << "Некорректный приоритет.\n";
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            priorityInsert(priorityHead, name, priority);
            cout << "Элемент добавлен.\n";
            break;

        case 2:
            priorityRemove(priorityHead);
            break;

        case 3:
            cout << "\nПриоритетная очередь:\n";
            printList(priorityHead, true);
            break;

        case 4: {
            cout << "Введите имя для поиска: ";
            name = readName();

            if (name.empty()) {
                break;
            }

            Node* found = priorityFind(priorityHead, name);

            if (found != nullptr) {
                cout << "Элемент найден: " << found->name
                    << ", приоритет: " << found->priority << '\n';
            }
            else {
                cout << "Элемент не найден.\n";
            }

            break;
        }

        case 5:
            cout << "Введите имя для удаления: ";
            name = readName();

            if (name.empty()) {
                break;
            }

            if (priorityDelete(priorityHead, name)) {
                cout << "Элемент удалён.\n";
            }
            else {
                cout << "Элемент не найден.\n";
            }
            break;

        case 6:
            cout << "Введите название элемента: ";
            name = readName();

            if (!name.empty()) {
                queueEnqueue(queueHead, queueTail, name);
                cout << "Элемент добавлен в очередь.\n";
            }
            break;

        case 7:
            queueDequeue(queueHead, queueTail);
            break;

        case 8:
            cout << "\nОбычная очередь (FIFO):\n";
            printList(queueHead);
            break;

        case 9:
            cout << "Введите название элемента: ";
            name = readName();

            if (!name.empty()) {
                stackPush(stackTop, name);
                cout << "Элемент добавлен в стек.\n";
            }
            break;

        case 10:
            stackPop(stackTop);
            break;

        case 11:
            cout << "\nСтек (сверху вниз, LIFO):\n";
            printList(stackTop);
            break;

        case 0:
            cout << "Завершение программы.\n";
            break;

        default:
            cout << "Такого пункта меню нет.\n";
        }

    } while (choice != 0);

    // Освобождение всей выделенной памяти
    clearList(priorityHead);
    clearList(queueHead);
    clearList(stackTop);

    return 0;
}