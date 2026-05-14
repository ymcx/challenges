import sys


def get_lines():
    return [
        [
            [int(coordinate) for coordinate in coordinates.split(",")]
            for coordinates in line.split("->")
        ]
        for line in sys.stdin
    ]


def get_boundaries():
    lines.append([[500, 0]])  # sand
    x_min, x_max, y_min, y_max = sys.maxsize, 0, sys.maxsize, 0

    for line in lines:
        for x, y in line:
            x_min = min(x_min, x - 250)
            x_max = max(x_max, x)
            y_min = min(y_min, y)
            y_max = max(y_max, y)

    return x_min, x_max, y_min, y_max


def get_board():
    width = x_max - x_min + 501
    height = y_max - y_min + 3
    board = [[False] * width for _ in range(height)]

    return board, width, height


def fill_board():
    for line in lines:
        for i in range(1, len(line)):
            x, y = line[i]
            lx, ly = line[i - 1]

            for i in range(abs(y - ly) + 1):
                i += min(ly, y) - y_min

                for j in range(abs(x - lx) + 1):
                    j += min(lx, x) - x_min
                    board[i][j] = True

    i = height - 1
    for j in range(width):
        board[i][j] = True


def spawn_sand(x, y):
    y += 1

    if not board[y][x]:
        return spawn_sand(x, y)

    if not board[y][x - 1]:
        return spawn_sand(x - 1, y)

    if not board[y][x + 1]:
        return spawn_sand(x + 1, y)

    board[y - 1][x] = True
    return True


lines = get_lines()
x_min, x_max, y_min, y_max = get_boundaries()
board, width, height = get_board()
fill_board()

result = 1
x, y = 500 - x_min, 0 - y_min
while spawn_sand(x, y) and not board[y][x]:
    result += 1

print(result)
