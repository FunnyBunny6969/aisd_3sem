#include <stdio.h>

#define MAX 10 

int matrix[MAX][MAX] = {
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
};

struct Queue {
    int items[MAX];
    int front;
    int rear;
};

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->rear < q->front;
}

void push(Queue* q, int value) {
    q->items[++q->rear] = value;
}

int popFront(Queue* q) {
    return q->items[q->front++];
}

int popBack(Queue* q) {
    return q->items[q->rear--];
}

void printAdjacencyList(int vertices) {
    printf("Список смежности:\n");
    for (int u = 0; u < vertices; u++) {
        printf("%d: ", u);
        int hasNeighbors = 0; 
        for (int v = 0; v < vertices; v++) {
            if (matrix[u][v] == 1) {
                printf("%d ", v);
                hasNeighbors = 1;
            }
        }
        if (!hasNeighbors) {
            printf("пусто");
        }
        printf("\n");
    }
}

void printEdgeList(int vertices) {
    printf("Список рёбер:\n");
    for (int u = 0; u < vertices; u++) {
        for (int v = u + 1; v < vertices; v++) { 
            if (matrix[u][v] == 1) {
                printf("(%d, %d)\n", u, v);
            }
        }
    }
}

void bfs(int v, int vertices) {
    int visited[MAX] = {0};
    Queue q;
    initQueue(&q);

    push(&q, v);
    while (!isEmpty(&q)) {
        int u = popFront(&q);
        visited[u] = 1;
        printf("%d ", u);
        for (int w = 0; w < vertices; w++) {
            if (matrix[u][w] == 1 && !visited[w]) {
                push(&q, w);
                visited[w] = 1;
            }
        }
    }
}

void dfs(int v, int vertices) {
    int visited[MAX] = {0};
    Queue q;
    initQueue(&q);

    push(&q, v);
    visited[v] = 1;
    while (!isEmpty(&q)) {
        int u = popBack(&q);
        printf("%d ", u);
        for (int w = 0; w < vertices; w++) {
            if (matrix[u][w] == 1 && !visited[w]) {
                push(&q, w);
                visited[w] = 1;
            }
        }
    }
}

int main() {
    int vertices = 10;

    printAdjacencyList(vertices);
    printf("\n");

    printEdgeList(vertices);
    printf("\n");

    printf("Обход BFS, начиная с вершины 0:\n");
    bfs(0, vertices);
    printf("\n\n");

    printf("Обход DFS, начиная с вершины 0:\n");
    dfs(0, vertices);
    printf("\n");

    return 0;
}
