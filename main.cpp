#include <windows.h>
#include <iostream>
#include "sortings.cpp"
#include "mazes.cpp"
#include <conio.h> 

void clear_input_buffer() {
    while (_kbhit()) {
        _getch(); 
    }
}

using namespace std;

class Menu {
private: 
    int enter_permutation() {
        system("cls");
        cout << "Enter size of permutation to be sort:\n";
        int n = -1;
        clear_input_buffer(); 
        cin >> n;
        while (cin.fail() || n <= 0 || n > 200) {
            system("cls");
            cout << "Invalid size. Please enter size (1-200).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> n;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return n;
    }
    pair<int, int> enter_maze() {
        system("cls");
        cout << "Enter size of maze (height width):\n";
        int height = -1, width = -1;
        cin >> height >> width;
        clear_input_buffer();
        while (cin.fail() || height <= 0 || width <= 0 || height > 50 || width > 50) {
            system("cls");
            cout << "Invalid size. Please enter height (1-50) and width (1-50).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> height >> width;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return {height, width};
    }
    
    void sort_selection_menu() {
        string menuItems[8] = { "Bubble sort", "Selection sort", "Merge sort", "Quick sort", 
                                "Heap sort", "Bogo sort", "Miracle sort", "Exit" };
        int selected = 0;
        bool menuActive = true;
        
        while (menuActive) {
            system("cls");
            cout << "=== SORTINGS MENU ===\n\n";
            for (int i = 0; i < 8; i++) {
                if (i == selected) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // cyan
                    cout << "> " << menuItems[i] << " <" << endl;
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // white
                    cout << "  " << menuItems[i] << endl;
                }
            }
            
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "\nUse UP/DOWN arrows to navigate, ENTER to select.\n";

            while (menuActive) {
                if (GetAsyncKeyState(VK_UP) & 1) {
                    selected--;
                    if (selected < 0) selected = 7;
                    break;
                }
                else if (GetAsyncKeyState(VK_DOWN) & 1){
                    selected++;
                    if (selected > 7) selected = 0;
                    break;
                }
                else if (GetAsyncKeyState(VK_RETURN) & 1){
                    switch (selected){
                        case 0: {
                            system("cls");
                            SortVisualizer sorter;
                            int n = enter_permutation();
                            system("cls");
                            sorter.random_array(n);
                            sorter.bubble_sort(); 
                            system("pause");
                            return; 
                        }
                        case 1: {
                            system("cls");
                            SortVisualizer sorter;
                            int n = enter_permutation();
                            system("cls");
                            sorter.random_array(n);
                            sorter.selection_sort(); 
                            system("pause");
                            return; 
                        }
                        case 2: {
                            system("cls");
                            SortVisualizer sorter;
                            int n = enter_permutation();
                            system("cls");
                            sorter.random_array(n);
                            sorter.merge_sort(); 
                            system("pause");
                            return; 
                        }
                        case 3: {
                            system("cls");
                            SortVisualizer sorter;
                            int n = enter_permutation();
                            system("cls");
                            sorter.random_array(n);
                            sorter.quick_sort(); 
                            system("pause");
                            return; 
                        }
                        case 4: {
                            system("cls");
                            SortVisualizer sorter;
                            int n = enter_permutation();
                            system("cls");
                            sorter.random_array(n);
                            sorter.heap_sort(); 
                            system("pause");
                            return; 
                        }
                        case 5: {
                            system("cls");
                            SortVisualizer sorter;
                            int n = enter_permutation();
                            system("cls");
                            sorter.random_array(n);
                            sorter.bogo_sort(); 
                            system("pause");
                            return; 
                        }
                        case 6: {
                            system("cls");
                            SortVisualizer sorter;
                            int n = enter_permutation();
                            system("cls");
                            sorter.random_array(n);
                            sorter.miracle_sort(); 
                            system("pause");
                            return; 
                        }
                        case 7: {
                            system("cls");
                            cout << "Exiting...\n";
                            Sleep(1000);
                            main_menu_display();
                            menuActive = false;
                            return;
                        }
                    }
                }
            }
            Sleep(100);
        }
    }

    void maze_selection_menu() {
        string menuItems[4] = { "DFS", "Kruskal", "Wilson", "Exit" };
        int selected = 0;
        bool menuActive = true;

        while (menuActive) {
            system("cls");
            cout << "=== MAZE MENU ===\n\n";
            for (int i = 0; i < 4; i++) {
                if (i == selected) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // cyan
                    cout << "> " << menuItems[i] << " <" << endl;
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // white
                    cout << "  " << menuItems[i] << endl;
                }
            }
            
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "\nUse UP/DOWN arrows to navigate, ENTER to select.\n";

            while (menuActive) {
                if (GetAsyncKeyState(VK_UP) & 1) {
                    selected--;
                    if (selected < 0) selected = 3;
                    break;
                }
                else if (GetAsyncKeyState(VK_DOWN) & 1){
                    selected++;
                    if (selected > 3) selected = 0;
                    break;
                }
                else if (GetAsyncKeyState(VK_RETURN) & 1){
                    switch (selected){
                        case 0: {
                            int height, width;
                            tie(height, width) = enter_maze();
                            system("cls");
                            MazeVisualizer mazeVis;
                            mazeVis.dfs(height, width);
                            system("pause");
                            return; 
                        }
                        case 1: {
                            int height, width;
                            tie(height, width) = enter_maze();
                            system("cls");
                            MazeVisualizer mazeVis;
                            mazeVis.kruskal(height, width);
                            system("pause");
                            return; 
                        }
                        case 2: {
                            int height, width;
                            tie(height, width) = enter_maze();
                            system("cls");
                            MazeVisualizer mazeVis;
                            mazeVis.wilson(height, width);
                            system("pause");
                            return; 
                        }
                        case 3: {
                            system("cls");
                            cout << "Exiting...\n";
                            Sleep(1000);
                            main_menu_display();
                            menuActive = false;
                            return;
                        }
                    }
                }
            }
            Sleep(100);
        }
    }

public:
    void main_menu_display() {
        string menuItems[3] = { "MazeVisualizer", "SortingsVisualizer", "Exit" };
        int selected = 0;
        bool menuActive = true;

        while (menuActive) {
            system("cls");
            cout << "=== MAIN MENU ===\n\n";
            for (int i = 0; i < 3; i++) {
                if (i == selected) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // cyan
                    cout << "> " << menuItems[i] << " <" << endl;
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // white
                    cout << "  " << menuItems[i] << endl;
                }
            }
            
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "\nUse UP/DOWN arrows to navigate, ENTER to select.\n";

            while (menuActive) {
                if (GetAsyncKeyState(VK_UP) & 1) {
                    selected--;
                    if (selected < 0) selected = 2;
                    break;
                }
                else if (GetAsyncKeyState(VK_DOWN) & 1){
                    selected++;
                    if (selected > 2) selected = 0;
                    break;
                }
                else if (GetAsyncKeyState(VK_RETURN) & 1){
                    switch (selected){
                        case 0: { 
                            system("cls");
                            cout << "Entering maze menu...\n";
                            Sleep(1000);
                            maze_selection_menu();
                            break;
                        }
                        case 1: { 
                            system("cls");
                            cout << "\033[?25l"; 
                            cout << "Entering sortings menu...\n";
                            Sleep(1000);
                            sort_selection_menu();
                            break;
                        }
                        case 2: {
                            system("cls");
                            cout << "Exiting...\n";
                            Sleep(1000);
                            menuActive = false;
                            return; 
                        }
                    }
                }
            }
            
            Sleep(100);
        }
    }
};

int main() 
{
    Menu menu;
    menu.main_menu_display();
}