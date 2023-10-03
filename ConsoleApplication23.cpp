#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Структура для представления элемента очереди
typedef struct {
    char* data;
    int priority;
} QueueElement;

// Структура для представления приоритетной очереди
typedef struct {
    QueueElement* elements;
    int maxSize;
    int currentSize;
} PriorityQueue;

// Функция для создания приоритетной очереди
PriorityQueue* createPriorityQueue(int maxSize) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->elements = (QueueElement*)malloc(maxSize * sizeof(QueueElement));
    queue->maxSize = maxSize;
    queue->currentSize = 0;
    return queue;
}

// Функция для проверки, является ли очередь пустой
int isEmpty(PriorityQueue* queue) {
    return queue->currentSize == 0;
}

// Функция для проверки, является ли очередь полной
int isFull(PriorityQueue* queue) {
    return queue->currentSize == queue->maxSize;
}

// Функция для добавления элемента в приоритетную очередь
void enqueue(PriorityQueue* queue, char* data, int priority) {
    if (isFull(queue)) {
        printf("Очередь полна. Невозможно добавить элемент.\n");
        return;
    }

    QueueElement newElement;
    newElement.data = (char*)malloc((strlen(data) + 1) * sizeof(char));
    strcpy(newElement.data, data);
    newElement.priority = priority;

    int i;
    for (i = queue->currentSize - 1; i >= 0; i--) {
        if (queue->elements[i].priority > newElement.priority) {
            queue->elements[i + 1] = queue->elements[i];
        }
        else {
            break;
        }
    }

    queue->elements[i + 1] = newElement;
    queue->currentSize++;
}

// Функция для удаления элемента из приоритетной очереди
void dequeue(PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста. Невозможно удалить элемент.\n");
        return;
    }

    printf("Удален элемент с данными: %s\n", queue->elements[0].data);

    free(queue->elements[0].data);

    int i;
    for (i = 0; i < queue->currentSize - 1; i++) {
        queue->elements[i] = queue->elements[i + 1];
    }

    queue->currentSize--;
}

// Функция для вывода элементов приоритетной очереди
void printPriorityQueue(PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста.\n");
        return;
    }

    printf("Элементы приоритетной очереди:\n");
    for (int i = 0; i < queue->currentSize; i++) {
        printf("Данные: %s, Приоритет: %d\n", queue->elements[i].data, queue->elements[i].priority);
    }
}

// Функция для освобождения памяти, занятой приоритетной очередью
void freePriorityQueue(PriorityQueue* queue) {
    for (int i = 0; i < queue->currentSize; i++) {
        free(queue->elements[i].data);
    }
    free(queue->elements);
    free(queue);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int maxSize;
    printf("Введите максимальный размер приоритетной очереди: ");
    scanf("%d", &maxSize);

    PriorityQueue* queue = createPriorityQueue(maxSize);

    int choice;
    char data[100];
    int priority;

    while (1) {
        printf("\n1. Добавить элемент в очередь\n");
        printf("2. Удалить элемент из очереди\n");
        printf("3. Вывести элементы очереди\n");
        printf("4. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите данные элемента: ");
            scanf("%s", data);
            printf("Введите приоритет элемента: ");
            scanf("%d", &priority);
            enqueue(queue, data, priority);
            break;
        case 2:
            dequeue(queue);
            break;
        case 3:
            printPriorityQueue(queue);
            break;
        case 4:
            freePriorityQueue(queue);
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}

/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node
{
    char inf[256];  // полезная информация
    struct node* next; // ссылка на следующий элемент
};

struct node* head = NULL, * last = NULL; // указатели на первый и последний элементы списка

// Функции добавления элемента, просмотра списка
void enqueue(void);
void dequeue(void);
void review(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");   // вводим данные
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p;// возвращаем указатель на созданный элемент
}

/* Добавление элемента в очередь (в конец) 
void enqueue(void)
{
    struct node* p = NULL;
    p = get_struct();
    if (head == NULL && p != NULL)// если очереди нет, то устанавливаем голову и хвост очереди
    {
        head = p;
        last = p;
    }
    else if (head != NULL && p != NULL) // очередь уже есть, то вставляем в конец
    {
        last->next = p;
        last = p;
    }
    return;
}

/* Удаление элемента из очереди (из начала) 
void dequeue(void)
{
    if (head == NULL) // если очередь пуста
    {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = head;
    head = head->next; // устанавливаем голову на следующий элемент
    free(temp); // освобождаем память, выделенную для удаленного элемента

    if (head == NULL) // если после удаления очередь стала пустой
    {
        last = NULL; // обнуляем хвост очереди
    }

    return;
}

/* Просмотр содержимого очереди 
void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Очередь пуста\n");
    }
    while (struc)
    {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
    return;
}

int main()
{

    setlocale(LC_ALL, "Rus");
    int choice;

    while (1)
    {
        printf("\nОчередь:\n");
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Просмотреть очередь\n");
        printf("4. Выход\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            review();
            break;
        case 4:
            exit(0);
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node
{
    char inf[256];  // полезная информация
    struct node* next; // ссылка на следующий элемент
};

struct node* head = NULL; // указатель на вершину стека
int dlinna = 0;

// Функции добавления элемента, удаления элемента и просмотра стека
void push(void), pop(void), review(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент стека
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");   // вводим данные
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p;// возвращаем указатель на созданный элемент
}

/* Добавление элемента в стек (в начало) 
void push(void)
{
    struct node* p = NULL;
    p = get_struct();
    if (p != NULL)
    {
        p->next = head;
        head = p;
        dlinna++;
    }
    return;
}

/* Удаление элемента из стека (с начала) 
void pop(void)
{
    struct node* p = NULL;
    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }
    p = head;
    head = head->next;
    free(p);
    dlinna--;
    return;
}

/* Просмотр содержимого стека 
void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Стек пуст\n");
    }
    while (struc)
    {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
    return;
}

int main()
{

    setlocale(LC_ALL, "Rus");
    int choice;
    while (1)
    {
        printf("\n1. Добавить элемент в стек\n");
        printf("2. Удалить элемент из стека\n");
        printf("3. Просмотреть содержимое стека\n");
        printf("4. Выход\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            review();
            break;
        case 4:
            exit(0);
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}


*/