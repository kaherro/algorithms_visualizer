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
    
    void merge(int left, int right, int mid) {
        int n = mid - left + 1;
        int m = right - mid;
        vector<int> L(n), R(m);
        for (int i = 0; i < n; i++) {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < m; j++) {
            R[j] = arr[mid + 1 + j];
        }
        int i = 0, j = 0, k = left; 
        while(i < n && j < m) {
            if(L[i] <= R[j]) {
                arr[k] = L[i];
                visualize({-1, -1, k});
                i++;
            } else {
                arr[k] = R[j];
                visualize({-1, -1, k});
                j++;
            }
            k++; 
        }
        while(i < n) {
            arr[k] = L[i];
            visualize({-1, -1, k});
            i++, k++;
        }
        while(j < m) {
            arr[k] = R[j];
            visualize({-1, -1, k});
            j++, k++;
        }
    }
    void merge_sort(int left, int right) {
        if(left < right) {
            int mid = left + (right - left) / 2;
            merge_sort(left, mid);
            merge_sort(mid + 1, right);
            merge(left, right, mid);
            // visualize({left, right, mid});
        }
    }
    void merge_sort() {
        merge_sort(0, size - 1);
    }

    void quick_sort(int low, int high) {
        if (low < high) {
            int pivot = arr[high];
            int i = low - 1;
            for (int j = low; j < high; j++) {
                if (arr[j] < pivot) {
                    i++;
                    swap(arr[i], arr[j]);
                    visualize({i, j, -1});
                }
            }
            swap(arr[i + 1], arr[high]);
            visualize({i + 1, high, -1});
            int pi = i + 1;
            quick_sort(low, pi - 1);
            quick_sort(pi + 1, high);
        }
    }
    void quick_sort() {
        quick_sort(0, size - 1);
    }

    void heapify(int n, int i) {
        int largest = i; 
        int left = 2 * i + 1; 
        int right = 2 * i + 2; 

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            visualize({i, largest, -1});
            heapify(n, largest);
        }
    }
    void heap_sort() {
        cout << "\033[2J"; 
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(size, i);
        }
        for (int i = size - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            visualize({0, i, -1});
            heapify(i, 0);
        }
    }
};

int main() {
    cout << "\033[?25l"; 
    system("pause");
}