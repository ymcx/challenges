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
            x_min = min(x_min, x)
            x_max = max(x_max, x)
            y_min = min(y_min, y)
            y_max = max(y_max, y)

    return x_min, x_max, y_min, y_max


def get_board():
    width = x_max - x_min + 1
    height = y_max - y_min + 1
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


def is_valid_position(x, y):
    return 0 <= x < width and 0 <= y < height


def spawn_sand(x, y):
    y += 1

    if not is_valid_position(x, y):
        return False

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

result = 0
while spawn_sand(500 - x_min, 0 - y_min):
    result += 1

print(result)
