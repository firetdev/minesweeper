import random

grid = []
mines = set()

for i in range(10):
    grid.append([0, 0, 0, 0, 0, 0, 0, 0, 0, 0])

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

for row in grid:
    for cell in row:
        if cell == -1:
            print("M", end=" ")
        else:
            print(cell, end=" ")
    print()