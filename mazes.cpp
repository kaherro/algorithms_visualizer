#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

class MazeVisualizer {
private:
    int width = 10, height = 10;
    vector<vector<char>> maze;

    void Visualize() {
        string buffer = "";
        for (int i = 0; i < 1 + height * 2; i++) {
            for (int j = 0; j < 1 + width * 2; j++) {
                if(maze[i][j] == '.') {
                    buffer += "\033[93m\xDB\033[0m"; // yellow
                    buffer += "\033[93m\xDB\033[0m"; // yellow
                    continue;
                }
                buffer += maze[i][j];
                buffer += maze[i][j];
            }
            buffer += '\n';
        }
        cout << "\033[H" << buffer;
        Sleep(30);
    }

    void dfs(int x, int y, vector<vector<bool>> &visited) {
        maze[x][y] = ' ';
        Visualize();
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

    pair<int, int> dsu_find(pair<int, int> v, vector<vector<pair<int, int>>>& parent) {
        while (v != parent[v.first][v.second]) {
            v = parent[v.first][v.second];
        }
        return v;
    }

    bool dsu_unite(pair<int, int> a, pair<int, int> b, 
        vector<vector<pair<int, int>>>& parent, vector<vector<int>>& rank) {
        a = dsu_find(a, parent);
        b = dsu_find(b, parent);
        if (a != b) {
            if (rank[a.first][a.second] < rank[b.first][b.second]) {
                swap(a, b);
            }
            parent[b.first][b.second] = a;
            if (rank[a.first][a.second] == rank[b.first][b.second]) {
                rank[a.first][a.second]++;
            }
            return true; 
        }
        return false; 
    }

    void kruskal() {
        vector<pair<pair<int, int>, pair<int, int>>> walls;
        for (int i = 1; i < height * 2; i += 2) {
            for (int j = 1; j < width * 2; j += 2) {
                if (i + 2 < height * 2 + 1) {
                    walls.push_back({{i, j}, {i + 2, j}});
                }
                if (j + 2 < width * 2 + 1) {
                    walls.push_back({{i, j}, {i, j + 2}});
                }
            }
        }

        random_shuffle(walls.begin(), walls.end());
        vector<vector<pair<int, int>>> parent(1 + height * 2, vector<pair<int, int>>(1 + width * 2));
        vector<vector<int>> rank(1 + height * 2, vector<int>(1 + width * 2, 0));

        for (int i = 1; i < 1 + height * 2; i += 2) {
            for (int j = 1; j < 1 + width * 2; j += 2) {
                parent[i][j] = {i, j};
            }
        }

        for (auto& wall : walls) {
            auto u = wall.first;
            auto v = wall.second;
            int wallX = (u.first + v.first) / 2;
            int wallY = (u.second + v.second) / 2;
            if (dsu_find(u, parent) != dsu_find(v, parent)) {
                maze[u.first][u.second] = ' ';
                maze[wallX][wallY] = ' ';
                maze[v.first][v.second] = ' ';
                dsu_unite(u, v, parent, rank);
                Visualize();
            }
        }
        Visualize();
    }

    void wilson() {
        vector<vector<bool>> visited(1 + height * 2, vector<bool>(1 + width * 2, false));
        int startX = 1 + 2 * (rand() % height);
        int startY = 1 + 2 * (rand() % width);
        maze[startX][startY] = ' ';
        visited[startX][startY] = true;
        Visualize();

        vector<pair<int, int>> unvisited;
        for (int i = 1; i < 1 + height * 2; i += 2) {
            for (int j = 1; j < 1 + width * 2; j += 2) {
                if (!(i == startX && j == startY)) {
                    unvisited.push_back({i, j});
                }
            }
        }
        random_shuffle(unvisited.begin(), unvisited.end());
        
        while (!unvisited.empty()) {
            int i = rand() % unvisited.size();
            pair<int, int> current = unvisited[i];
            int x = current.first;
            int y = current.second;
            
            vector<pair<int, int>> path;
            unordered_map<int, unordered_map<int, bool>> visited_path;
            pair<int, int> prev = {x, y};
            while (!visited[x][y]) {
                path.push_back({x, y});
                visited_path[x][y] = true;
                maze[x][y] = '.';
                maze[(x + prev.first) / 2][(y + prev.second) / 2] = '.';
                vector<pair<int, int>> directions = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
                vector<pair<int, int>> valid_moves;
                for (auto& dir : directions) {
                    int vx = x + dir.first;
                    int vy = y + dir.second;
                    if (vx >= 1 && vx < 1 + height * 2 && 
                        vy >= 1 && vy < 1 + width * 2) {
                        valid_moves.push_back({vx, vy});
                    }
                }

                if (!valid_moves.empty()) {
                    pair<int, int> next = valid_moves[rand() % valid_moves.size()];
                    maze[(x + next.first) / 2][(y + next.second) / 2] = '.';
                    if (visited_path[next.first][next.second]) {
                        auto it = path.begin();
                        while (it != path.end()) {
                            if (it->first == next.first && it->second == next.second) {
                                break;
                            }
                            visited_path[it->first][it->second] = false;
                            maze[it->first][it->second] = '\xDB';
                            prev = {it->first, it->second};
                            ++it;
                            maze[(prev.first + it->first) / 2][(prev.second + it->second) / 2] = '\xDB';
                        }
                        path.erase(path.begin(), it);
                    }
                    prev = {x, y};
                    x = next.first;
                    y = next.second;
                }
                Visualize();
            }
            path.push_back({x, y});
            
            for (size_t i = 0; i < path.size() - 1; i++) {
                int x1 = path[i].first;
                int y1 = path[i].second;
                int x2 = path[i + 1].first;
                int y2 = path[i + 1].second;
                maze[x1][y1] = ' ';
                visited[x1][y1] = true;
                maze[(x1 + x2) / 2][(y1 + y2) / 2] = ' ';
                for (auto it = unvisited.begin(); it != unvisited.end(); ++it) {
                    if (it->first == x1 && it->second == y1) {
                        unvisited.erase(it);
                        break;
                    }
                }
                Visualize();
            }
            Visualize();
        }
    }

public:
    MazeVisualizer() : maze(1 + height * 2, vector<char>(1 + width * 2, '\xDB')) {}
    
    void dfs(int height, int width) {
        this->height = height;
        this->width = width;
        maze = vector<vector<char>>(1 + height * 2, vector<char>(1 + width * 2, '\xDB'));
        vector<vector<bool>> visited(1 + height * 2, vector<bool>(1 + width * 2, false));
        Visualize();
        dfs(1, 1, visited);
    }
    void kruskal(int height, int width) {
        this->height = height;
        this->width = width;
        maze = vector<vector<char>>(1 + height * 2, vector<char>(1 + width * 2, '\xDB'));
        Visualize();
        kruskal();
    }
    void wilson(int height, int width) {
        this->height = height;
        this->width = width;
        maze = vector<vector<char>>(1 + height * 2, vector<char>(1 + width * 2, '\xDB'));
        Visualize();
        wilson();
    }
};
