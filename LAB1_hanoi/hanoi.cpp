#include <iostream>
using namespace std;

void printMove(int disk, int source, int destination) {
    cout << "Переместить диск " << 
      disk << " с " << source << " на " << 
      destination << " стержень" << endl;
}

void hanoi(
    int n, 
    int source, 
    int auxiliary, 
    int destination) {
    if (n == 1) {
        printMove(n, source, destination);
        return;
    }
    // Перемещаем n-1 дисков с исходного стержня на вспомогательный
    hanoi(n - 1, source, destination, auxiliary);
    // Перемещаем самый большой диск (n) на целевой стержень
    printMove(n, source, destination);
    // Перемещаем n-1 дисков с вспомогательного на целевой
    hanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int N, k;
    
    // Запрашиваем количество дисков
    cout << "Введите количество дисков N: ";
    cin >> N;
    
    // Проверяем корректность ввода N
    if (N <= 0) {
        cout << "Ошибка: количество дисков должно быть положительным." << endl;
        return 1;
    }
    
    // Запрашиваем номер целевого стержня
    cout << "Введите номер целевого стержня k (2 или 3): ";
    cin >> k;
    
    // Проверяем корректность ввода k
    if (k != 2 && k != 3) {
        cout << "Ошибка: целевой стержень должен быть 2 или 3." << endl;
        return 1;
    }
    
    // Исходный стержень всегда 1, вспомогательный — оставшийся (1+2+3=6, 6-k-1)
    int source = 1;
    int auxiliary = 6 - k - source; // Например, если k=2, то auxiliary=3; если k=3, то auxiliary=2
    
    // Вызываем рекурсивную функцию
    hanoi(N, source, auxiliary, k);
    
    return 0;
}
