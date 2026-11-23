import re
import sys


def get_coordinates(y):
    coordinates = [
        tuple(int(coordinate) for coordinate in re.findall(r"-?\d+", line))
        for line in sys.stdin
    ]

    sensors = [i[:2] for i in coordinates]
    beacons = [i[2:] for i in coordinates]
    x_left = min(i[0] for i in sensors)
    x_right = max(i[0] for i in sensors)

    sensor_xleft = [get_manhattan(i, (x_left, y)) for i in sensors]
    sensor_xright = [get_manhattan(i, (x_right, y)) for i in sensors]
    sensor_beacon = [get_manhattan(i, j) for i, j in zip(sensors, beacons)]

    x_left -= max(i - j for i, j in zip(sensor_beacon, sensor_xleft))
    x_right += max(i - j for i, j in zip(sensor_beacon, sensor_xright))

    return sensors, sensor_beacon, x_left, x_right


def get_manhattan(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def advance(sensors, sensor_beacon, x, y):
    for sensor, r in zip(sensors, sensor_beacon):
        d = get_manhattan(sensor, (x, y))
        if d <= r:
            x_new = sensor[0] + r - abs(sensor[1] - y) + 1
            score = x_new - x
            return (x_new, score)

    x_new = x + 1
    score = 0
    return (x_new, score)


def solve(sensors, sensor_beacon, x_left, x_right, y):
    result = 0
    x = x_left
    while x <= x_right:
        (x, score) = advance(sensors, sensor_beacon, x, y)
        result += score

    return result - 1


y = 2000000
sensors, sensor_beacon, x_left, x_right = get_coordinates(y)
result = solve(sensors, sensor_beacon, x_left, x_right, y)

print(result)
