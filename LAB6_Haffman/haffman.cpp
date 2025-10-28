#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <locale>
#include <codecvt>
using namespace std;

// Узел дерева Хаффмана
struct Node {
    string ch;  // храним символ как строку для UTF-8
    int freq;
    Node *left, *right;
    Node(string c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Для сравнения узлов в очереди
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Генерация кодов
void generateCodes(Node* root, string code, map<string, string>& codes) {
    if (!root) return;
    
    // Если это лист (символ)
    if (!root->left && !root->right) {
        codes[root->ch] = code;
        return;
    }
    
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Функция для корректного разделения UTF-8 строки на символы
vector<string> splitUTF8(const string& str) {
    vector<string> symbols;
    for (size_t i = 0; i < str.length();) {
        unsigned char c = str[i];
        size_t symbol_len;
        
        if ((c & 0x80) == 0) { // 1-byte symbol (ASCII)
            symbol_len = 1;
        } else if ((c & 0xE0) == 0xC0) { // 2-byte symbol
            symbol_len = 2;
        } else if ((c & 0xF0) == 0xE0) { // 3-byte symbol (русские буквы)
            symbol_len = 3;
        } else if ((c & 0xF8) == 0xF0) { // 4-byte symbol
            symbol_len = 4;
        } else {
            symbol_len = 1; // fallback
        }
        
        symbols.push_back(str.substr(i, symbol_len));
        i += symbol_len;
    }
    return symbols;
}

int main() {
    // Настройка локали для поддержки русского языка
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    string text;
    cout << "Введите текст: ";
    getline(cin, text);
    
    if (text.empty()) {
        text = "иванов иван иванович";
        cout << "Используется тестовый текст: " << text << endl;
    }
    
    // 1. Разбиваем текст на UTF-8 символы и подсчитываем частоты
    vector<string> symbols = splitUTF8(text);
    map<string, int> freq;
    for (const string& symbol : symbols) {
        freq[symbol]++;
    }
    
    // 2. Вывод таблицы встречаемости
    cout << "\nА) ТАБЛИЦА ВСТРЕЧАЕМОСТИ СИМВОЛОВ:\n";
    int total = symbols.size();
    for (auto& p : freq) {
        string symbol = p.first;
        if (symbol == " ") symbol = "[пробел]";
        else if (symbol == "\n") symbol = "[новая строка]";
        else if (symbol == "\t") symbol = "[табуляция]";
        
        cout << symbol << " - " << p.second << " раз (" 
             << (p.second * 100.0 / total) << "%)\n";
    }
    
    // 3. Построение дерева Хаффмана
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : freq) {
        pq.push(new Node(p.first, p.second));
    }
    
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        
        Node* parent = new Node("", left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    
    Node* root = pq.top();
    
    // 4. Генерация кодов
    map<string, string> codes;
    generateCodes(root, "", codes);
    
    // 5. Вывод таблицы кодов
    cout << "\nБ) ТАБЛИЦА КОДОВ:\n";
    for (auto& p : codes) {
        string symbol = p.first;
        if (symbol == " ") symbol = "[пробел]";
        else if (symbol == "\n") symbol = "[новая строка]";
        else if (symbol == "\t") symbol = "[табуляция]";
        
        cout << symbol << " -> " << p.second << "\n";
    }
    
    // 6. Кодирование текста
    cout << "\nВ) ЗАКОДИРОВАННАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ:\n";
    string encoded = "";
    for (const string& symbol : symbols) {
        encoded += codes[symbol];
    }
    cout << encoded << "\n";
    
    // 7. Статистика
    cout << "\nСТАТИСТИКА:\n";
    cout << "Исходный размер: " << text.length() << " байт (" << total * 8 << " бит)\n";
    cout << "Сжатый размер: " << encoded.length() << " бит\n";
    if (encoded.length() > 0) {
        cout << "Коэффициент сжатия: " << (total * 8.0 / encoded.length()) << ":1\n";
    }
    
    return 0;
}