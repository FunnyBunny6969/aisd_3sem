#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

vector<Item> knapsack(int capacity, vector<Item>& items, int& maxValue) {
    int n = items.size();
    
    // Создаем таблицу для динамического программирования
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    // Заполняем таблицу dp
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i-1].weight <= w) {
                dp[i][w] = max(
                    dp[i-1][w], 
                    dp[i-1][w - items[i-1].weight] + items[i-1].value);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    maxValue = dp[n][capacity];
    
    // Восстанавливаем выбранные предметы
    vector<Item> selectedItems;
    int w = capacity;
    
    for (int i = n; i > 0 && maxValue > 0; i--) {
        if (maxValue != dp[i-1][w]) {
            selectedItems.push_back(items[i-1]);
            maxValue -= items[i-1].value;
            w -= items[i-1].weight;
        }
    }
    
    return selectedItems;
}

// Функция для ввода данных от пользователя
void inputItems(vector<Item>& items) {
    int count;
    cout << "Введите количество предметов: ";
    cin >> count;
    
    for (int i = 0; i < count; i++) {
        Item item;
        cout << "\nПредмет " << i + 1 << ":\n";
        cout << "  Название: ";
        cin.ignore();
        getline(cin, item.name);
        cout << "  Вес: ";
        cin >> item.weight;
        cout << "  Стоимость: ";
        cin >> item.value;
        
        items.push_back(item);
    }
}

// Функция для вывода результатов
void printResults(const vector<Item>& selectedItems, int maxValue, int capacity) {
    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    cout << "Максимальная стоимость: " << maxValue << endl;
    cout << "Вместимость рюкзака: " << capacity << endl;
    
    if (selectedItems.empty()) {
        cout << "В рюкзак не поместился ни один предмет." << endl;
        return;
    }
    
    cout << "\nПредметы в рюкзаке:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Название\tВес\tСтоимость" << endl;
    cout << "----------------------------------------" << endl;
    
    int totalWeight = 0;
    int totalValue = 0;
    
    for (const auto& item : selectedItems) {
        cout << item.name << "\t\t" << item.weight << "\t" << item.value << endl;
        totalWeight += item.weight;
        totalValue += item.value;
    }
    
    cout << "----------------------------------------" << endl;
    cout << "Итого:\t\t" << totalWeight << "\t" << totalValue << endl;
}

int main() {
    system("chcp 65001 > nul");
    cout << "=== РЮКЗАК: РЕШЕНИЕ ЗАДАЧИ О РЮКЗАКЕ ===" << endl;
    
    int capacity;
    cout << "Введите вместимость рюкзака (N): ";
    cin >> capacity;
    
    if (capacity <= 0) {
        cout << "Ошибка: вместимость должна быть положительным числом!" << endl;
        return 1;
    }
    
    // Ввод предметов
    vector<Item> items;
    inputItems(items);
    
    if (items.empty()) {
        cout << "Ошибка: не введено ни одного предмета!" << endl;
        return 1;
    }
    
    int maxValue;
    vector<Item> selectedItems = knapsack(capacity, items, maxValue);
    printResults(selectedItems, maxValue, capacity);
    
    return 0;
}