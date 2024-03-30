#include <iostream>
#include <vector>
#include <random>
#include <windows.h>
#include <ctime>

using namespace std;

vector<vector<int>> generateMatrix(int rows, int cols, int min, int max) {
    cout << "Returned Matrix: " << endl;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = min + rand() % (max - min + 1);
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }

    return matrix;
}

DWORD WINAPI findMaxSubArray(LPVOID param) {
    // reinterpret_cast — это оператор приведения типов в C++, 
    // который позволяет выполнять приведение типов между различными типами данных, включая указатели на разные типы данных.
    vector<vector<int>>* matrix = reinterpret_cast<vector<vector<int>>*>(param);
    vector<int> maxSubArr = (*matrix)[0];
    int subArrEvenSum = 0;

    for (int i = 0; i < matrix->size(); i++) {
        int evenSum = 0;
        for (int j = 0; j < (*matrix)[i].size(); j++) {
            if ((*matrix)[i][j] % 2 == 0) evenSum += (*matrix)[i][j];
        }

        if (subArrEvenSum < evenSum) maxSubArr = (*matrix)[i];

        subArrEvenSum = evenSum;
    }

    cout << "Result:" << endl;
    for (int i = 0; i < maxSubArr.size(); i++) {
        cout << maxSubArr[i] << " ";
    }
    cout << endl;

    return 0;
}


int main() {
    const int rows = 5;
    const int cols = 2;
    const int min = 1;
    const int max = 20;

    vector<vector<int>> matrix = generateMatrix(rows, cols, min, max);

    HANDLE hThread = CreateThread(NULL, 0, findMaxSubArray, &matrix, 0, NULL);

    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);

    return 0;

}