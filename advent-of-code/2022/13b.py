import math
import sys
import functools
import copy


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


def is_ordered_helper(left, right):
    left = copy.deepcopy(left)
    right = copy.deepcopy(right)

    if is_ordered(left, right):
        return -1

    return 1


divider_packets = [[[6]], [[2]]]
lines = [eval(line) for line in sys.stdin if line != "\n"] + divider_packets
lines = sorted(lines, key=functools.cmp_to_key(is_ordered_helper))
result = math.prod(i for i, line in enumerate(lines, 1) if line in divider_packets)

print(result)
