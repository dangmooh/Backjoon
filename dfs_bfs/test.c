#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


/* linked list */

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *head = NULL;

Node * create_node(int v)
{
    Node *n = malloc(sizeof(Node));
    if(!n) exit(1);
    n->value = v;
    n->next = NULL;
    return n;
}

void push_front(Node **head, int v)
{
    Node *n = create_node(v);
    n->next = *head;
    *head = n;
}

int pop_front(Node **head)
{
    if(!*head) return -1;
    Node *n = *head;
    int v = n->value;
    *head = n->next;
    free(n);
    return v;
}

void free_list(Node **head)
{
    Node *cur = *head;
    while(cur)
    {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
}



/* stack */

#define MAX 1000
int stack[MAX], top = 0;

bool push(int v) 
{
    bool ret;

    ret = false;
    if(top != MAX - 1)
    {
        stack[top++] = v; 
        ret = true;
    } 

    return ret;
}


int pop()
{
    return top > 0 ? stack[--top] : -1;
}

bool is_empty()
{
    return top == 0;
}

/* queue */

int queue[MAX];
int qh=0; qt=0;

void enqueue(int v)
{
    queue[qt] = v;
    qt = (qt+1) % MAX;
}

void dequeue()
{
    if (qh == qt) return -1;
    int v = queue[qh];
    qh = (qh + 1) % MAX;
    return v;
}

bool q_empty()
{
    return qh == qt;
}

/* priority queue */

typedef struct {
    int *heap;
    int size, capacity;
} Heap;

void heap_init(Heap *h, int cap)
{
    h->size = 0;
    h->capacity = cap;
    h->heap = malloc(cap * sizeof(int));
}

void heap_push(Heap *h, int x)
{
    int i = h->size++;
    while(i>0)
    {
        int p = (i-1)/2;
        if (h->heap[p]>=x) break;
        h->heap[i] = h->heap[p];
        i = p;
    }
    h->heap[i] = x;
}

int heap_pop(Heap *h)
{
    if (h->size == 0) return -1;
    int ret = h->heap[0];
    int last = h->heap[--h->size];
    int i=0;
    while(i*2+1 <h->size)
    {
        int c = 2*i+1;
        if (c+1 < h->size && h->heap[c+1] > h->heap[c]) c++;
        if (h->heap[c] <= last) break;
        h->heap[i] = h->heap[c];
        i = c;
    }
    h->heap[i] = last;
    return ret;
}

void heap_free(Heap *h)
{
    free(h->heap);
}

/* dynamic array */


typedef struct {
    int *data;
    int size, capacity;
} Vector;

void vec_init(Vector *v)
{
    v->size = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * sizeof(int));
}

void vec_push(Vector *v, int x)
{
    if (v->size == v->capacity)
    {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * sizeof(int));
        if(!v->data) exit(1);
    }
    v->data[v->size++] = x;
}

int vec_get(Vector *v, int i) 
{
    return v->data[i];
}

void vec_free(Vector *v)
{
    free(v->data);
}




