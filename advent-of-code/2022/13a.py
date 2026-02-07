import sys


def is_ordered(left_list, right_list):
    while left_list and right_list:
        left = left_list.pop(0)
        right = right_list.pop(0)

        if left == right:
            continue
        elif isinstance(left, int) and isinstance(right, int):
            return left < right
        elif isinstance(right, int):
            right = [right]
        elif isinstance(left, int):
            left = [left]

        result = is_ordered(left, right)
        if result != -1:
            return result

    if left_list == right_list:
        return -1

    return left_list < right_list


lines = sys.stdin.readlines()
pairs = [(eval(lines[i]), eval(lines[i + 1])) for i in range(0, len(lines), 3)]
result = sum(is_ordered(left, right) * i for i, (left, right) in enumerate(pairs, 1))

print(result)
