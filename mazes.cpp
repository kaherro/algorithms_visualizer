#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

class MazeVisualizer {
private:
    int width = 10, height = 10;
    vector<vector<char>> maze;

    void Vizualize() {
        string buffer = "";
        for (int i = 0; i < 1 + height * 2; i++) {
            for (int j = 0; j < 1 + width * 2; j++) {
                buffer += maze[i][j];
                buffer += maze[i][j];
            }
            buffer += '\n';
        }
        cout << "\033[H" << buffer;
    }

    void dfs(int x, int y, vector<vector<bool>> &visited) {
        Vizualize();
        maze[x][y] = ' ';
        visited[x][y] = true;
        vector<pair<int, int>> directions = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        random_shuffle(directions.begin(), directions.end());
        for (auto dir : directions) {
            int vx = x + dir.first;
            int vy = y + dir.second;
            if (vx >= 0 && vx < 1 + height * 2 && vy >= 0 && vy < 1 + width * 2 && !visited[vx][vy]) {
                maze[x + dir.first / 2][y + dir.second / 2] = ' ';
                dfs(vx, vy, visited);
            }
        }
    }

public:
    MazeVisualizer() : maze(1 + height * 2, vector<char>(1 + width * 2, '\xDB')) {}

    void generate_maze(int height, int width) {
        this->height = height;
        this->width = width;
        maze = vector<vector<char>>(1 + height * 2, vector<char>(1 + width * 2, '\xDB'));
        vector<vector<bool>> visited(1 + height * 2, vector<bool>(1 + width * 2, false));
        dfs(1, 1, visited);
    }
};
