import re
import sys


def get_coordinates():
    coordinates = [
        tuple(int(coordinate) for coordinate in re.findall(r"-?\d+", line))
        for line in sys.stdin
    ]

    sensors = [i[:2] for i in coordinates]
    beacons = [i[2:] for i in coordinates]
    sensor_beacon = [get_manhattan(i, j) for i, j in zip(sensors, beacons)]

    return sensors, sensor_beacon


def get_manhattan(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def advance(sensors, sensor_beacon, x, y):
    for sensor, r in zip(sensors, sensor_beacon):
        d = get_manhattan(sensor, (x, y))
        if d <= r:
            room = r - d
            x_new = sensor[0] + r - abs(sensor[1] - y) + 1
            return (x_new, room)

    return (None, None)


def solve(sensors, sensor_beacon, limit):
    y = 0
    while y <= limit:
        x = 0
        room_min = limit
        while x <= limit:
            (x_new, room) = advance(sensors, sensor_beacon, x, y)
            if not x_new:
                return 4000000 * x + y
            x = x_new
            room_min = min(room_min, room)
        y += room_min + 1


limit = 4000000
sensors, sensor_beacon = get_coordinates()
result = solve(sensors, sensor_beacon, limit)

print(result)
