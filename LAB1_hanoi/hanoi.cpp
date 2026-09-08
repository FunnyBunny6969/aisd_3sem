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
    cout << "Введите номер целевого стержня k: ";
    cin >> k;

    int source = 1;

    if (k == source) {
        cout << "WELL DONE" << endl;
        return 1;
    }

    else if (k <= 3) {
        int auxiliary = 6 - k - source;
        hanoi(N, source, auxiliary, k);
    }

    else {
        hanoi(N, source, 2, k);
    }
    
    return 0;
}
