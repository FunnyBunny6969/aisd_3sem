#include <iostream>
#include <cstring>
using namespace std;

const long long INF = 1e18;
const int V = 9;

// Глобальная матрица смежности
long long graph[V][V] = {
    {0, 7, 10, INF, INF, INF, INF, INF, INF},    // a
    {7, 0, INF, INF, INF, 9, 27, INF, INF},      // b
    {10, INF, 0, INF, 31, 8, INF, INF, INF},     // c
    {INF, INF, INF, 0, 32, INF, INF, 17, 21},    // d
    {INF, INF, 31, 32, 0, INF, INF, INF, INF},   // e
    {INF, 9, 8, INF, INF, 0, INF, 11, INF},      // f
    {INF, 27, INF, INF, INF, INF, 0, INF, 15},   // g
    {INF, INF, INF, 17, INF, 11, INF, 0, 15},    // h
    {INF, INF, INF, 21, INF, INF, 15, 15, 0}     // i
};

int main() {
    char start_char;
    cout << "Введите начальную вершину (a-i): ";
    cin >> start_char;
    int start = start_char - 'a';

    if (start < 0 || start >= V) {
        cout << "Неверная вершина!" << endl;
        return 1;
    }

    // Дейкстра
    long long dist[V];
    bool visited[V];
    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[start] = 0;

    // Основной цикл
    for (int i = 0; i < V; ++i) {
        // Ищем минимальное расстояние среди непосещённых
        long long min_dist = INF;
        int u = -1;
        for (int j = 0; j < V; ++j) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // Все достижимые обработаны
        visited[u] = true;

        // Релаксация
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Вывод
    cout << "Кратчайшие пути от вершины " << start_char << ":" << endl;
    for (int i = 0; i < V; ++i) {
        char v_char = 'a' + i;
        if (dist[i] == INF) {
            cout << "До " << v_char << ": недостижимо" << endl;
        } else {
            cout << "До " << v_char << ": " << dist[i] << endl;
        }
    }

    return 0;
}
