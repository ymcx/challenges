import sys
import re


def get_coordinates():
    coordinates = [
        tuple(int(coordinate) for coordinate in re.findall(r"-?\d+", line))
        for line in sys.stdin
    ]

    sensors = [pair[:2] for pair in coordinates]
    beacons = [pair[2:] for pair in coordinates]
    coverages = [get_manhattan(s, b) for s, b in zip(sensors, beacons)]

    return sensors, coverages


def get_manhattan(a, b):
    return abs(b[0] - a[0]) + abs(b[1] - a[1])


def is_covered(point):
    for sensor, coverage in zip(sensors, coverages):
        distance = get_manhattan(sensor, point)
        if distance <= coverage:
            return True

    return False


def get_result(y, x_min, x_max):
    return sum(is_covered((x, y)) for x in range(x_min, x_max)) - 1


sensors, coverages = get_coordinates()
result = get_result(2000000, -500000, 5000000)
print(result)
