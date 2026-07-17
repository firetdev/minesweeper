#include <iostream>
#include <vector>
#include <set>          
#include <random>
#include <ranges>
#include <cctype>       

void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == -2) {
                std::cout << "# ";
            } else if (cell == -1) {
                std::cout << "M ";
            } else {
                std::cout << cell << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    
    std::vector<std::vector<int>> grid(10, std::vector<int>(10, 0));
    std::set<std::pair<int, int>> minePositions; 

    while (minePositions.size() < 10) {
        int x = dist(gen);
        int y = dist(gen);
        minePositions.insert({x, y});
    }

    for (const auto& pos : minePositions) {
        grid[pos.first][pos.second] = -1;
    }

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (grid[x][y] == -1) {
                continue;
            }

            int mineCount = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && grid[nx][ny] == -1) {
                        ++mineCount;
                    }
                }
            }
            grid[x][y] = mineCount;
        }
    }

    std::vector<std::vector<int>> gameGrid(10, std::vector<int>(10, -2));  // -2 is unrevealed cells
    bool gameOver = false;

    while (!gameOver) {
        printGrid(gameGrid);

        char flag;
        std::cout << "Do you want to flag a cell? (y/n): ";
        std::cin >> flag;
        flag = std::tolower(flag);

        if (flag == 'y') {
            int x, y;
            std::cout << "Enter the coordinates to flag (x y): ";
            std::cin >> x >> y;

            if (x < 0 || x >= 10 || y < 0 || y >= 10) {
                std::cout << "Invalid coordinates! Keep them between 0 and 9.\n\n";
                continue;
            }

            if (gameGrid[x][y] == -2) {
                gameGrid[x][y] = -1;
            } else if (gameGrid[x][y] == -1) {
                gameGrid[x][y] = -2;
            }
        } else {
            int x, y;
            std::cout << "Enter the coordinates to reveal (x y): ";
            std::cin >> x >> y;

            // Bounds check
            if (x < 0 || x >= 10 || y < 0 || y >= 10) {
                std::cout << "Invalid coordinates! Keep them between 0 and 9.\n\n";
                continue;
            }

            if (grid[x][y] == -1) {
                std::cout << "\nGame Over! You hit a mine.\n";
                gameOver = true;
                printGrid(grid);
            } else {
                gameGrid[x][y] = grid[x][y];
                
                if ([&]() {
                    for (int i = 0; i < 10; ++i) {
                        for (int j = 0; j < 10; ++j) {
                            if (grid[i][j] != -1 && gameGrid[i][j] == -2) { 
                                return false; 
                            }
                        }
                    }
                    return true;
                }()) {
                    std::cout << "\nCongratulations! You've cleared the minefield.\n";
                    gameOver = true;
                    printGrid(grid);
                }
            }
        }
    }

    return 0;
}