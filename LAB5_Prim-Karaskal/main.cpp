#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int V = 8;
int graph[V][V];

// Структура для ребра
struct Edge {
    int src, dest, weight;
};

// Структура для системы непересекающихся множеств
struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }
    
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

void initializeGraph() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
}

void addEdge(int u, int v, int weight) {
    u = u - 1;
    v = v - 1;
    graph[u][v] = weight;
    graph[v][u] = weight; 
}

// ========== АЛГОРИТМ ПРИМА ==========
int minKey(vector<int>& key, vector<bool>& mstSet) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(vector<int>& parent) {
    cout << "Минимальное остовное дерево (Прим):" << endl;
    cout << "Ребро \tВес" << endl;
    
    int totalWeight = 0;
    for (int i = 1; i < V; i++) {
        cout << parent[i] + 1 << " - " << i + 1 << " \t" << graph[i][parent[i]] << endl;
        totalWeight += graph[i][parent[i]];
    }
    cout << "Общий вес остовного дерева: " << totalWeight << endl << endl;
}

void primMST() {
    vector<int> parent(V);
    vector<int> key(V);
    vector<bool> mstSet(V);

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent);
}

// ========== АЛГОРИТМ КРАСКАЛА ==========
void kruskalMST() {
    // Собираем все ребра графа
    vector<Edge> edges;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }
    
    // Сортируем ребра по весу
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });
    
    // Создаем систему непересекающихся множеств
    DisjointSet ds(V);
    vector<Edge> result;
    int totalWeight = 0;
    
    // Проходим по отсортированным ребрам
    for (Edge edge : edges) {
        int rootSrc = ds.find(edge.src);
        int rootDest = ds.find(edge.dest);
        
        // Если ребро не создает цикл - добавляем его
        if (rootSrc != rootDest) {
            result.push_back(edge);
            totalWeight += edge.weight;
            ds.unite(rootSrc, rootDest);
        }
        
        // Останавливаемся когда набрали V-1 ребро
        if (result.size() == V - 1) {
            break;
        }
    }
    
    // Выводим результат
    cout << "Минимальное остовное дерево (Краскал):" << endl;
    cout << "Ребро \tВес" << endl;
    for (Edge edge : result) {
        cout << edge.src + 1 << " - " << edge.dest + 1 << " \t" << edge.weight << endl;
    }
    cout << "Общий вес остовного дерева: " << totalWeight << endl << endl;
}

void printGraph() {
    cout << "Матрица смежности:" << endl;
    cout << "   ";
    for (int i = 0; i < V; i++) {
        cout << i + 1 << "\t";
    }
    cout << endl;
    
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": ";
        for (int j = 0; j < V; j++) {
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    initializeGraph();

    // Добавляем ребра
    addEdge(1,2,2);
    addEdge(1,4,8);
    addEdge(1,5,2);
    addEdge(2,3,3);
    addEdge(2,5,5);
    addEdge(2,4,10);
    addEdge(3,8,7);
    addEdge(3,5,12);
    addEdge(4,5,14);
    addEdge(4,6,3);
    addEdge(4,7,1);
    addEdge(5,6,11);
    addEdge(5,7,4);
    addEdge(5,8,8);
    addEdge(6,7,6);
    addEdge(7,8,9);

    cout << "=== СРАВНЕНИЕ АЛГОРИТМОВ ПРИМА И КРАСКАЛА ===" << endl;
    cout << "Количество вершин: " << V << endl << endl;

    // Выводим матрицу смежности
    printGraph();

    // Запускаем оба алгоритма
    primMST();
    kruskalMST();

    return 0;
}