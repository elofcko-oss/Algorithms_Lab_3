
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NAME_SIZE 256

typedef struct Node {
    char name[NAME_SIZE];
    int priority;
    struct Node* next;
} Node;

// Создание нового элемента
Node* createNode(const char* name, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    strncpy(newNode->name, name, NAME_SIZE - 1);
    newNode->name[NAME_SIZE - 1] = '\0';

    newNode->priority = priority;
    newNode->next = NULL;

    return newNode;
}

// Очистка ввода
void clearInput(void) {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// Ввод названия
void readName(char* name, size_t size) {
    size_t len;

    if (fgets(name, (int)size, stdin) == NULL) {
        name[0] = '\0';
        return;
    }

    len = strlen(name);

    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';
    } else {
        clearInput();
    }
}

// Ввод числа с проверкой
int readInt(const char* message, int* value) {
    printf("%s", message);

    if (scanf("%d", value) != 1) {
        printf("Ошибка: необходимо ввести число.\n");
        clearInput();
        return 0;
    }

    clearInput();
    return 1;
}

// Вывод списка
void printList(Node* head) {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    while (head != NULL) {
        printf("Название: %s", head->name);
        printf(" | Приоритет: %d\n", head->priority);

        head = head->next;
    }
}

// Освобождение памяти
void clearList(Node** head) {
    Node* current = *head;

    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
}

// Поиск по подстроке
void searchBySubstring(Node* head, const char* substring) {
    int found = 0;

    if (substring[0] == '\0') {
        printf("Подстрока не должна быть пустой.\n");
        return;
    }

    while (head != NULL) {
        if (strstr(head->name, substring) != NULL) {
            printf("Название: %s | Приоритет: %d\n",
                   head->name, head->priority);
            found = 1;
        }

        head = head->next;
    }

    if (!found) {
        printf("Совпадений не найдено.\n");
    }
}

// Добавление в приоритетную очередь
// Чем больше число, тем выше приоритет
void priorityInsert(Node** head, const char* name, int priority) {
    Node* newNode = createNode(name, priority);

    if (newNode == NULL) {
        return;
    }

    if (*head == NULL || (*head)->priority < priority) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;

    while (current->next != NULL &&
           current->next->priority >= priority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Удаление первого элемента приоритетной очереди
void priorityRemove(Node** head) {
    if (*head == NULL) {
        printf("Приоритетная очередь пуста.\n");
        return;
    }

    Node* temp = *head;

    printf("Удалён элемент: %s\n", temp->name);

    *head = (*head)->next;
    free(temp);
}

// Удаление из приоритетной очереди по названию
void priorityDelete(Node** head, const char* name) {
    Node* current = *head;
    Node* previous = NULL;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            Node* temp = current;

            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }

            current = current->next;
            free(temp);
            found = 1;
        } else {
            previous = current;
            current = current->next;
        }
    }

    if (found) {
        printf("Элементы удалены.\n");
    } else {
        printf("Элемент не найден.\n");
    }
}

// Добавление в обычную очередь
void queueEnqueue(Node** head, Node** tail,
                  const char* name, int priority) {
    Node* newNode = createNode(name, priority);

    if (newNode == NULL) {
        return;
    }

    if (*tail == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }

    printf("Элемент добавлен в очередь.\n");
}

// Удаление из обычной очереди
void queueDequeue(Node** head, Node** tail) {
    if (*head == NULL) {
        printf("Очередь пуста.\n");
        return;
    }

    Node* temp = *head;

    printf("Удалён элемент: %s\n", temp->name);

    *head = (*head)->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
}

// Удаление из очереди по названию
void queueDeleteByName(Node** head, Node** tail,
                       const char* name) {
    Node* current = *head;
    Node* previous = NULL;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            Node* temp = current;

            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }

            current = current->next;

            if (temp == *tail) {
                *tail = previous;
            }

            free(temp);
            found = 1;
        } else {
            previous = current;
            current = current->next;
        }
    }

    if (*head == NULL) {
        *tail = NULL;
    }

    if (found) {
        printf("Элементы с таким названием удалены.\n");
    } else {
        printf("Элементы с таким названием не найдены.\n");
    }
}

// Удаление из очереди по приоритету
void queueDeleteByPriority(Node** head, Node** tail,
                           int priority) {
    Node* current = *head;
    Node* previous = NULL;
    int found = 0;

    while (current != NULL) {
        if (current->priority == priority) {
            Node* temp = current;

            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }

            current = current->next;

            if (temp == *tail) {
                *tail = previous;
            }

            free(temp);
            found = 1;
        } else {
            previous = current;
            current = current->next;
        }
    }

    if (*head == NULL) {
        *tail = NULL;
    }

    if (found) {
        printf("Элементы с таким приоритетом удалены.\n");
    } else {
        printf("Элементы с таким приоритетом не найдены.\n");
    }
}

// Инвертирование обычной очереди
void queueReverse(Node** head, Node** tail) {
    Node* previous = NULL;
    Node* current = *head;
    Node* next = NULL;

    if (*head == NULL || (*head)->next == NULL) {
        printf("Для инвертирования недостаточно элементов.\n");
        return;
    }

    *tail = *head;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    *head = previous;

    printf("Очередь успешно инвертирована.\n");
}

// Добавление в стек
void stackPush(Node** top, const char* name) {
    Node* newNode = createNode(name, 0);

    if (newNode == NULL) {
        return;
    }

    newNode->next = *top;
    *top = newNode;

    printf("Элемент добавлен в стек.\n");
}

// Удаление из стека
void stackPop(Node** top) {
    if (*top == NULL) {
        printf("Стек пуст.\n");
        return;
    }

    Node* temp = *top;

    printf("Удалён элемент: %s\n", temp->name);

    *top = (*top)->next;
    free(temp);
}

// Главное меню
int main(void) {
    setlocale(LC_ALL, "");

    Node* priorityHead = NULL;

    Node* queueHead = NULL;
    Node* queueTail = NULL;

    Node* stackTop = NULL;

    int choice;
    int priority;
    int answer;
    char name[NAME_SIZE];
    char substring[NAME_SIZE];

    do {
        printf("\n========== ГЛАВНОЕ МЕНЮ ==========\n");

        printf("\n--- ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ---\n");
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент с наивысшим приоритетом\n");
        printf("3. Показать приоритетную очередь\n");
        printf("4. Поиск по подстроке\n");
        printf("5. Удалить элемент по названию\n");

        printf("\n--- ОБЫЧНАЯ ОЧЕРЕДЬ ---\n");
        printf("6. Добавить элемент\n");
        printf("7. Удалить первый элемент\n");
        printf("8. Показать очередь\n");
        printf("9. Удалить элементы по названию\n");
        printf("10. Удалить элементы по приоритету\n");
        printf("11. Поиск по подстроке\n");
        printf("12. Инвертировать очередь\n");

        printf("\n--- СТЕК ---\n");
        printf("13. Добавить элемент\n");
        printf("14. Удалить верхний элемент\n");
        printf("15. Показать стек\n");
        printf("16. Поиск по подстроке\n");

        printf("\n0. Выход\n");
        printf("==================================\n");

        if (!readInt("Выберите действие: ", &choice)) {
            continue;
        }

        switch (choice) {

        // ПРИОРИТЕТНАЯ ОЧЕРЕДЬ

        case 1:
            printf("Введите название элемента: ");
            readName(name, sizeof(name));

            if (name[0] == '\0') {
                printf("Название не может быть пустым.\n");
                break;
            }

            if (!readInt("Введите приоритет: ", &priority)) {
                break;
            }

            priorityInsert(&priorityHead, name, priority);
            break;

        case 2:
            priorityRemove(&priorityHead);
            break;

        case 3:
            printf("\nПриоритетная очередь:\n");
            printList(priorityHead);
            break;

        case 4:
            printf("Введите подстроку для поиска: ");
            readName(substring, sizeof(substring));

            searchBySubstring(priorityHead, substring);
            break;

        case 5:
            printf("Введите название для удаления: ");
            readName(name, sizeof(name));

            priorityDelete(&priorityHead, name);
            break;

        // ОБЫЧНАЯ ОЧЕРЕДЬ

        case 6:
            printf("Введите название элемента: ");
            readName(name, sizeof(name));

            if (name[0] == '\0') {
                printf("Название не может быть пустым.\n");
                break;
            }

            if (!readInt("Введите приоритет: ", &priority)) {
                break;
            }

            queueEnqueue(&queueHead, &queueTail,
                         name, priority);
            break;

        case 7:
            queueDequeue(&queueHead, &queueTail);
            break;

        case 8:
            printf("\nОбычная очередь:\n");
            printList(queueHead);
            break;

        case 9:
            printf("Введите название для удаления: ");
            readName(name, sizeof(name));

            queueDeleteByName(&queueHead, &queueTail, name);
            break;

        case 10:
            if (!readInt("Введите приоритет для удаления: ",
                         &priority)) {
                break;
            }

            queueDeleteByPriority(&queueHead, &queueTail,
                                  priority);
            break;

        case 11:
            printf("Введите подстроку для поиска: ");
            readName(substring, sizeof(substring));

            searchBySubstring(queueHead, substring);
            break;

        case 12:
            if (queueHead == NULL) {
                printf("Очередь пуста. Нечего инвертировать.\n");
                break;
            }

            printf("\nТекущая очередь:\n");
            printList(queueHead);

            if (!readInt(
                "\nВы действительно хотите инвертировать очередь? (1 - Да, 0 - Нет): ",
                &answer)) {
                break;
            }

            if (answer == 1) {
                queueReverse(&queueHead, &queueTail);

                printf("\nОчередь после инвертирования:\n");
                printList(queueHead);
            } else {
                printf("Инвертирование отменено.\n");
            }
            break;

        // СТЕК

        case 13:
            printf("Введите название элемента: ");
            readName(name, sizeof(name));

            if (name[0] == '\0') {
                printf("Название не может быть пустым.\n");
                break;
            }

            stackPush(&stackTop, name);
            break;

        case 14:
            stackPop(&stackTop);
            break;

        case 15:
            printf("\nСтек:\n");
            printList(stackTop);
            break;

        case 16:
            printf("Введите подстроку для поиска: ");
            readName(substring, sizeof(substring));

            searchBySubstring(stackTop, substring);
            break;

        case 0:
            printf("Завершение программы.\n");
            break;

        default:
            printf("Неверный пункт меню. Попробуйте снова.\n");
            break;
        }

    } while (choice != 0);

    // Освобождение всей выделенной памяти
    clearList(&priorityHead);
    clearList(&queueHead);
    clearList(&stackTop);

    return 0;
}
