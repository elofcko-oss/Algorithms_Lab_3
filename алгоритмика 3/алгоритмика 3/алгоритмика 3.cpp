#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Структура одного элемента списка
typedef struct Node {
    char name[256];       // Название элемента
    int priority;         // Приоритет элемента
    struct Node* next;    // Указатель на следующий элемент
} Node;


// Создание нового элемента
Node* createNode(const char* name, int priority) {
    Node* node = (Node*)malloc(sizeof(Node));

    if (node == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';

    node->priority = priority;
    node->next = NULL;

    return node;
}


// Вывод списка
void printList(Node* head, int showPriority) {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    int number = 1;

    while (head != NULL) {
        printf("%d. %s", number++, head->name);

        if (showPriority) {
            printf(" (приоритет: %d)", head->priority);
        }

        printf("\n");
        head = head->next;
    }
}


// Освобождение всей памяти списка
void clearList(Node** head) {
    while (*head != NULL) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}


// Добавление в приоритетную очередь
// Чем больше число, тем выше приоритет
void priorityInsert(Node** head, const char* name, int priority) {
    Node* node = createNode(name, priority);

    if (node == NULL) {
        return;
    }

    if (*head == NULL || priority > (*head)->priority) {
        node->next = *head;
        *head = node;
        return;
    }

    Node* current = *head;

    while (current->next != NULL &&
           current->next->priority >= priority) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}


// Извлечение элемента с наивысшим приоритетом
void priorityRemove(Node** head) {
    if (*head == NULL) {
        printf("Приоритетная очередь пуста.\n");
        return;
    }

    Node* temp = *head;

    printf("Извлечён элемент: %s, приоритет: %d\n",
           temp->name, temp->priority);

    *head = (*head)->next;
    free(temp);
}


// Поиск элемента по имени
Node* priorityFind(Node* head, const char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }

        head = head->next;
    }

    return NULL;
}


// Удаление элемента по имени
int priorityDelete(Node** head, const char* name) {
    Node* current = *head;
    Node* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (previous == NULL) {
                *head = current->next;
            }
            else {
                previous->next = current->next;
            }

            free(current);
            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}


// Добавление в обычную очередь
void queueEnqueue(Node** head, Node** tail, const char* name) {
    Node* node = createNode(name, 0);

    if (node == NULL) {
        return;
    }

    if (*tail == NULL) {
        *head = node;
    }
    else {
        (*tail)->next = node;
    }

    *tail = node;
}


// Извлечение из обычной очереди
void queueDequeue(Node** head, Node** tail) {
    if (*head == NULL) {
        printf("Очередь пуста.\n");
        return;
    }

    Node* temp = *head;

    printf("Извлечён элемент: %s\n", temp->name);

    *head = (*head)->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
}


// Добавление в стек
void stackPush(Node** top, const char* name) {
    Node* node = createNode(name, 0);

    if (node == NULL) {
        return;
    }

    node->next = *top;
    *top = node;
}


// Извлечение из стека
void stackPop(Node** top) {
    if (*top == NULL) {
        printf("Стек пуст.\n");
        return;
    }

    Node* temp = *top;

    printf("Извлечён элемент: %s\n", temp->name);

    *top = (*top)->next;
    free(temp);
}


// Ввод непустого названия
int readName(char* name, size_t size) {
    printf("Введите название элемента: ");

    if (fgets(name, size, stdin) == NULL) {
        return 0;
    }

    name[strcspn(name, "\n")] = '\0';

    if (name[0] == '\0') {
        printf("Название не должно быть пустым.\n");
        return 0;
    }

    return 1;
}


// Очистка остатка строки ввода
void clearInput(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


// Главная функция программы
int main(void) {
    setlocale(LC_ALL, "");

    Node* priorityHead = NULL;

    Node* queueHead = NULL;
    Node* queueTail = NULL;

    Node* stackTop = NULL;

    int choice;
    int priority;

    char name[256];

    do {
        printf("\n===== ЛАБОРАТОРНАЯ РАБОТА №3 =====\n");
        printf("1. Добавить в приоритетную очередь\n");
        printf("2. Извлечь из приоритетной очереди\n");
        printf("3. Показать приоритетную очередь\n");
        printf("4. Найти элемент по имени\n");
        printf("5. Удалить элемент по имени\n");
        printf("6. Добавить в обычную очередь\n");
        printf("7. Извлечь из обычной очереди\n");
        printf("8. Показать обычную очередь\n");
        printf("9. Добавить в стек\n");
        printf("10. Извлечь из стека\n");
        printf("11. Показать стек\n");
        printf("0. Выход\n");

        printf("Ваш выбор: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода.\n");
            clearInput();
            continue;
        }

        clearInput();

        switch (choice) {

        case 1:
            if (!readName(name, sizeof(name))) {
                break;
            }

            printf("Введите приоритет (больше = выше): ");

            if (scanf("%d", &priority) != 1) {
                printf("Некорректный приоритет.\n");
                clearInput();
                break;
            }

            clearInput();

            priorityInsert(&priorityHead, name, priority);
            printf("Элемент добавлен.\n");
            break;


        case 2:
            priorityRemove(&priorityHead);
            break;


        case 3:
            printf("\nПриоритетная очередь:\n");
            printList(priorityHead, 1);
            break;


        case 4: {
            if (!readName(name, sizeof(name))) {
                break;
            }

            Node* found = priorityFind(priorityHead, name);

            if (found != NULL) {
                printf("Элемент найден: %s, приоритет: %d\n",
                       found->name, found->priority);
            }
            else {
                printf("Элемент не найден.\n");
            }

            break;
        }


        case 5:
            if (!readName(name, sizeof(name))) {
                break;
            }

            if (priorityDelete(&priorityHead, name)) {
                printf("Элемент удалён.\n");
            }
            else {
                printf("Элемент не найден.\n");
            }

            break;


        case 6:
            if (readName(name, sizeof(name))) {
                queueEnqueue(&queueHead, &queueTail, name);
                printf("Элемент добавлен в очередь.\n");
            }

            break;


        case 7:
            queueDequeue(&queueHead, &queueTail);
            break;


        case 8:
            printf("\nОбычная очередь (FIFO):\n");
            printList(queueHead, 0);
            break;


        case 9:
            if (readName(name, sizeof(name))) {
                stackPush(&stackTop, name);
                printf("Элемент добавлен в стек.\n");
            }

            break;


        case 10:
            stackPop(&stackTop);
            break;


        case 11:
            printf("\nСтек (сверху вниз, LIFO):\n");
            printList(stackTop, 0);
            break;


        case 0:
            printf("Завершение программы.\n");
            break;


        default:
            printf("Такого пункта меню нет.\n");
        }

    } while (choice != 0);


    // Освобождение всей выделенной памяти
    clearList(&priorityHead);
    clearList(&queueHead);
    clearList(&stackTop);

    return 0;
}
