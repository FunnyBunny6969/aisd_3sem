#include <iostream>
#include <cstdlib>
#include <windows.h>

void findLIS(int arr[], int n) {
    if (n == 0) {
        std::cout << "0\n";
        return;
    }
    
    int* dp = new int[n];
    int* prev = new int[n];
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }
    
    // Находим максимальную длину и её позицию
    int maxLength = 0;
    int endIndex = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            endIndex = i;
        }
    }
    
    // Выводим длину максимальной подпоследовательности
    std::cout << maxLength << "\n";
    
    if (maxLength > 0) {
        // Восстанавливаем подпоследовательность
        int* lis = new int[maxLength];
        int current = endIndex;
        
        for (int i = maxLength - 1; i >= 0; i--) {
            lis[i] = arr[current];
            current = prev[current];
        }
        
        // Выводим подпоследовательность
        for (int i = 0; i < maxLength; i++) {
            std::cout << lis[i];
            if (i < maxLength - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
        
        delete[] lis;
    }
    
    delete[] dp;
    delete[] prev;
}

int main() {
    std::cout << "Enter the number of sequence elements: ";
    int n; std::cin >> n;
    
    if (n <= 0) {
        std::cout << "The number of elements must be a positive number.\n";
        return 1;
    }
    
    std::cout << "Enter sequence elements separated by spaces: ";
    int* sequence = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> sequence[i];
    }
    
    findLIS(sequence, n);
    
    delete[] sequence;
    return 0;
}