#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITEMS_COUNT 10

typedef struct Item
{
    __uint16_t nomer;
    char description[250];
    double mass;
    double price;
} Item_t;

int randint(int min, int max)
{
    return min + rand() % (max - min + 1);
}
__uint16_t rand16bit()
{
    __uint16_t r = 0;
    for (int i = 0; i < 16; i++)
    {
        int a = randint(0, 1);
        r = (r << i) | a;
    }
    return r;
}

double randReal(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

char *randomDescription(char *description)
{
    description[0] = randint('A', 'Z');
    unsigned index = 1;
    int wordCount = randint(5, 10);
    for (int j = 0; j < wordCount; j++)
    {
        int n = randint(0, 9);
        for (int i = 0; i < n; i++)
        {
            description[index++] = randint('a', 'z');
        }
        description[index++] = ' ';
    }
    description[index] = '\0';
    return description;
}

typedef struct
{
    int data;
    struct node *next;
} node_t;

node_t *create_node(int data)
{
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    return node;
}

void push(node_t **list, Item_t *item)
{
    node_t *n = malloc(sizeof(node_t));
    n->data = item;
    n->next = *list;
    *list = n;
}

void print_list(node_t *list)
{
    node_t *current = list;
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    putchar('\n');
}

void listFree(node_t **list)
{
    node_t *current = *list, *prev;
    while (current)
    {
        prev = current;
        current = current->next;
        free(prev);
    }
    *list = NULL;
}

double totalItemsWeight(note_t *items)
{
    double sum = 0;
    node_t *current = items;
    while (current)
    {
        sum += current->mass;
        current = current->next;
    }
    return sum;
}

node_t *minPriceItem(node_t *items)
{
    double min = 1500.0;
    void ptr = NULL;
    node_t *current = items;
    while (current)
    {
        if (current.price < min)
        {
            min = current.price;
            ptr = *current.price;
        }
        current = current->next;
    }
    return ptr;
}

int main()
{
    srand(time(NULL));
    node_t *llist = NULL;
    for (int i = 0; i < ITEMS_COUNT; i++)
    {
        Item_t *item;
        item->nomer = rand16bit();
        item->description = randomDescription(item.description);
        item->mass = randReal(0.1, 100.0);
        item->price = randReal(1.0, 1500.0);
        push(&llist, item);
    }
    print_list(llist);
    printf("%lf ",totalItemsWeight(llist));
    printf("%lu ",minPriceItem(llist));

    free(llist);
    return 0;
}