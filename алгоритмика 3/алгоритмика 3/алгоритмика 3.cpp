#include <iostream>
#include <string>
#include <limits>
#include <locale>

using namespace std;

struct StackNode {
    string name;
    StackNode* next;

    explicit StackNode(const string& n)
        : name(n), next(nullptr) {}
};

void stackPush(StackNode*& top, const string& name) {
    StackNode* node = new StackNode(name);
    node->next = top;
    top = node;
}

void stackPop(StackNode*& top) {
    if (top == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }
    StackNode* temp = top;
    cout << "Извлечён элемент: " << temp->name << '\n';
    top = top->next;
    delete temp;
}

void printStack(StackNode* current) {
    if (current == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }
    int number = 1;
    while (current != nullptr) {
        cout << number++ << ". " << current->name << " (верх стека)\n";
        current = current->next;
    }
}

void clearStack(StackNode*& top) {
    while (top != nullptr) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}


struct QueueNode {
    string name;
    QueueNode* next;

    explicit QueueNode(const string& n)
        : name(n), next(nullptr) {}
};

void queueEnqueue(QueueNode*& head, QueueNode*& tail, const string& name) {
    QueueNode* node = new QueueNode(name);
    if (tail == nullptr) {          // очередь была пустой
        head = node;
    } else {
        tail->next = node;
    }
    tail = node;
}

void queueDequeue(QueueNode*& head, QueueNode*& tail) {
    if (head == nullptr) {
        cout << "Очередь пуста.\n";
        return;
    }
    QueueNode* temp = head;
    cout << "Извлечён элемент: " << temp->name << '\n';
    head = head->next;
    if (head == nullptr) {           // очередь стала пустой
        tail = nullptr;
    }
    delete temp;
}

void printQueue(QueueNode* current) {
    if (current == nullptr) {
        cout << "Очередь пуста.\n";
        return;
    }
    int number = 1;
    while (current != nullptr) {
        cout << number++ << ". " << current->name << " (FIFO)\n";
        current = current->next;
    }
}

void clearQueue(QueueNode*& head) {
    while (head != nullptr) {
        QueueNode* temp = head;
        head = head->next;
        delete temp;
    }
}



struct PriorityNode {
    string name;
    int priority;
    PriorityNode* next;

    explicit PriorityNode(const string& n, int p = 0)
        : name(n), priority(p), next(nullptr) {}
};

// Вставка по приоритету (сортировка по убыванию: больший приоритет — ближе к голове)
void priorityInsert(PriorityNode*& head, const string& name, int priority) {
    PriorityNode* node = new PriorityNode(name, priority);

    if (head == nullptr || priority > head->priority) {
        node->next = head;
        head = node;
        return;
    }

    PriorityNode* current = head;
    while (current->next != nullptr && current->next->priority >= priority) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

void priorityRemove(PriorityNode*& head) {
    if (head == nullptr) {
        cout << "Приоритетная очередь пуста.\n";
        return;
    }
    PriorityNode* temp = head;
    cout << "Извлечён элемент: " << temp->name
         << ", приоритет: " << temp->priority << '\n';
    head = head->next;
    delete temp;
}

PriorityNode* priorityFind(PriorityNode* head, const string& name) {
    PriorityNode* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool priorityDelete(PriorityNode*& head, const string& name) {
    PriorityNode* current = head;
    PriorityNode* previous = nullptr;

    while (current != nullptr) {
        if (current->name == name) {
            if (previous == nullptr) {
                head = current->next;
            } else {
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

void printPriorityQueue(PriorityNode* current, bool showPriority = false) {
    if (current == nullptr) {
        cout << "Приоритетная очередь пуста.\n";
        return;
    }
    int number = 1;
    while (current != nullptr) {
        cout << number++ << ". " << current->name;
        if (showPriority) {
            cout << " (приоритет: " << current->priority << ")";
        }
        cout << '\n';
        current = current->next;
    }
}

void clearPriorityQueue(PriorityNode*& head) {
    while (head != nullptr) {
        PriorityNode* temp = head;
        head = head->next;
        delete temp;
    }
}


string readName() {
    string name;
    getline(cin, name);
   
    if (!name.empty() && name.back() == '\r') {
        name.pop_back();
    }
    if (name.empty()) {
        cout << "Название не должно быть пустым.\n";
        return "";
    }
    return name;
}

int main() {
    setlocale(LC_ALL, "Russian");

    PriorityNode* pHead = nullptr;                  // Приоритетная очередь
    QueueNode* qHead = nullptr, *qTail = nullptr;  // Обычная очередь
    StackNode* sTop = nullptr;                      // Стек

    int choice;

    do {
        cout << "\n===== ЛАБОРАТОРНАЯ РАБОТА №3 (РАЗНЫЕ СТРУКТУРЫ) =====\n";
        cout << "1. Добавить в приоритетную очередь\n";
        cout << "2. Извлечь из приоритетной очереди\n";
        cout << "3. Показать приоритетную очередь\n";
        cout << "4. Найти элемент по имени (приоритетная)\n";
        cout << "5. Удалить элемент по имени (приоритетная)\n";
        cout << "6. Добавить в обычную очередь\n";
        cout << "7. Извлечь из обычной очереди\n";
        cout << "8. Показать обычную очередь\n";
        cout << "9. Добавить в стек\n";
        cout << "10. Извлечь из стека\n";
        cout << "11. Показать стек\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите число.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string name;
        int priority;

        switch (choice) {
            case 1:
                cout << "Введите название элемента: ";
                name = readName();
                if (name.empty()) break;
                cout << "Введите приоритет (больше = выше): ";
                if (!(cin >> priority)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Некорректный приоритет.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                priorityInsert(pHead, name, priority);
                cout << "Элемент добавлен.\n";
                break;

            case 2:
                priorityRemove(pHead);
                break;

            case 3:
                cout << "\nПриоритетная очередь:\n";
                printPriorityQueue(pHead, true);
                break;

            case 4:
                cout << "Введите имя для поиска: ";
                name = readName();
                if (name.empty()) break;
                PriorityNode* found = priorityFind(pHead, name);
                if (found != nullptr) {
                    cout << "Элемент найден: " << found->name
                         << ", приоритет: " << found->priority << '\n';
                } else {
                    cout << "Элемент не найден.\n";
                }
                break;

            case 5:
                cout << "Введите имя для удаления: ";
                name = readName();
                if (name.empty()) break;
                if (priorityDelete(pHead, name)) {
                    cout << "Элемент удалён.\n";
                } else {
                    cout << "Элемент не найден.\n";
                }
                break;

            case 6:
                cout << "Введите название элемента: ";
                name = readName();
                if (!name.empty()) {
                    queueEnqueue(qHead, qTail, name);
                    cout << "Элемент добавлен в очередь.\n";
                }
                break;

            case 7:
                queueDequeue(qHead, qTail);
                break;

            case 8:
                cout << "\nОбычная очередь (FIFO):\n";
                printQueue(qHead);
                break;

            case 9:
                cout << "Введите название элемента: ";
                name = readName();
                if (!name.empty()) {
                    stackPush(sTop, name);
                    cout << "Элемент добавлен в стек.\n";
                }
                break;

            case 10:
                stackPop(sTop);
                break;

            case 11:
                cout << "\nСтек (сверху вниз, LIFO):\n";
                printStack(sTop);
                break;

            case 0:
                cout << "Завершение программы.\n";
                break;

            default:
                cout << "Такого пункта меню нет. Выберите от 0 до 11.\n";
        }

    } while (choice != 0);

    // Освобождение памяти по каждой структуре отдельно
    clearPriorityQueue(pHead);
    clearQueue(qHead);
    clearStack(sTop);

    return 0;
}
