import random

def print_grid(grid):
    for row in grid:
        for cell in row:
            if cell == -1:
                print("M", end=" ")
            else:
                print(cell, end=" ")
        print()

grid = [[0 for _ in range(10)] for _ in range(10)]
mines = set()

while len(mines) < 10:
    mines.add((random.randint(0, 9), random.randint(0, 9)))

for mine in mines:
    x, y = mine
    grid[x][y] = -1

for x, row in enumerate(grid):
    for y, cell in enumerate(row):
        if cell == -1:
            continue

        count = 0
        for r in range(-1, 2):
            for c in range(-1, 2):
                if x + r < 0 or x + r >= len(grid):
                    continue
                if y + c < 0 or y + c >= len(row):
                    continue
                if r == 0 and c == 0:
                    continue

                if grid[x + r][y + c] == -1:
                    count += 1
                
        grid[x][y] = count

game_grid = [["#" for _ in range(10)] for _ in range(10)]
game_over = False

while not game_over:
    print_grid(game_grid)
    flag = input("Do you want to flag a cell? (y/n): ").lower()
    if flag == "y":
        x = int(input("Enter row (0-9): "))
        y = int(input("Enter column (0-9): "))
        if game_grid[x][y] == "#":
            game_grid[x][y] = "F"
        elif game_grid[x][y] == "F":
            game_grid[x][y] = "#"
    else:
        x = int(input("Enter row (0-9): "))
        y = int(input("Enter column (0-9): "))

        if grid[x][y] == -1:
            print("Game Over! You hit a mine.")
            game_over = True
            print_grid(grid)
        else:
            game_grid[x][y] = grid[x][y]
            if all(game_grid[i][j] != "#" for i in range(10) for j in range(10) if grid[i][j] != -1):
                print("Congratulations! You've cleared the minefield.")
                game_over = True

print_grid(grid)