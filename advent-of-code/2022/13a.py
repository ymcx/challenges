import sys


def merge_line(line):
    while True:
        new = []
        i = 0

        while i < len(line):
            if line[i][-1].isalnum() and line[i + 1][0].isalnum():
                x = 2
            else:
                x = 1

            item = ",".join(line[i : i + x])
            new.append(item)

            i += x

        if line == new:
            return line

        line = new


def read_lines():
    lines = [line[:-1] for line in sys.stdin if line != "\n"]
    lines = [line.split(",") for line in lines]
    lines = [merge_line(line) for line in lines]
    lines = iter(lines)
    lines = list(zip(lines, lines))

    return lines


def is_right_order(left, right):
    for left, right in zip(left, right):
        left_brackets = left.count("[")
        right_brackets = right.count("[")

        left = left.replace("[", "").replace("]", "")
        right = right.replace("[", "").replace("]", "")

        if len(left) == 0 and len(right) == 0:
            if left_brackets == right_brackets:
                continue
            return left_brackets < right_brackets

        if len(left) == 0:
            return True

        if len(right) == 0:
            return False

        left = [int(i) for i in left.split(",")]
        right = [int(i) for i in right.split(",")]

        for x, y in zip(left, right):
            if x == y:
                continue
            return x < y

        if len(left) == len(right):
            continue

        return len(left) < len(right)


def get_result(lines):
    return sum(
        i * is_right_order(left, right) for i, (left, right) in enumerate(lines, 1)
    )


lines = read_lines()
result = get_result(lines)

print(result)
