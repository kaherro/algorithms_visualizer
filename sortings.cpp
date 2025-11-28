#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <random>
using ll = long long;
#define f(i, n) for (int i = 0; i < int(n); i++)
using namespace std;

const ll MOD = 1e9 + 7;
class SortVisualizer {
private:
    int size = 10, max_element = 10;
    vector<int> arr = {1, 9, 3, 8, 5, 4, 6, 7, 2, 10};

    void visualize(vector<int> highlight) {
        string buffer = ""; 
        vector<vector<char>> matrix (max_element, vector<char>(size * 2, ' ')); 
        for(int i = 0; i < size * 2; i += 2) {
            for(int j = 0; j < arr[i / 2]; j++) {
                matrix[max_element - j - 1][i] = '\xDB';
                matrix[max_element - j - 1][i + 1] = '\xDB';
            }
            for(int j = arr[i / 2]; j < max_element; j++) {
                matrix[max_element - j - 1][i] = ' ';
                matrix[max_element - j - 1][i + 1] = ' ';
            }
        }
        for(int i = 0; i < max_element; i++) {
            for(int j = 0; j < size * 2; j++) {
                if (matrix[i][j] == '\xDB') {
                    if(j / 2 == highlight[0]) {
                        buffer += "\033[91m\xB2\033[0m"; // red
                        // buffer += "\033[93m\xDB\033[0m"; // yellow
                    }
                    else if(j / 2 == highlight[1]) {
                        buffer += "\033[94m\xB2\033[0m"; // blue
                        // buffer += "\033[93m\xDB\033[0m"; // yellow
                    }
                    else if(j / 2 == highlight[2]) {
                        buffer += "\033[93m\xDB\033[0m"; // yellow
                    }
                    else if(arr[j / 2] == j / 2 + 1) {
                        buffer += "\033[92m\xDB\033[0m"; // green
                    }
                    else {
                        buffer += "\xDB\033[0m"; 
                    }
                }
                else {
                    buffer += matrix[i][j];
                }
            }
            buffer += '\n';
        }
        Beep(200 + highlight[0] * 5 + highlight[1] * 5 + (highlight[2] + 1) * 5, 200);
        cout << "\033[H" << buffer;
    }
public: 
    void random_array(int size) {
        this->size = size;
        this->max_element = size;
        this->arr.resize(size);
        for(int i = 0; i < size; i++) {
            this->arr[i] = i + 1;
        }
        random_device rd;
        mt19937 gen(328); // 327
        shuffle(this->arr.begin(), this->arr.end(), gen);
    }

    void bubble_sort() {
        cout << "\033[2J"; 
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
                visualize({j, j + 1, -1});
            }
        }
    }

    void selection_sort() {
        cout << "\033[2J"; 
        for (int i = 0; i < size - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
                visualize({i, min_idx, j});
            }
            swap(arr[i], arr[min_idx]);
            visualize({i, min_idx, -1});
        }
        visualize({size - 2, size - 1, -1});
    }
};

int main() {
    cout << "\033[?25l"; 
    system("pause");
}