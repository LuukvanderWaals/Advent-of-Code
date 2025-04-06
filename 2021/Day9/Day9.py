file = list(map(lambda x: list(map(lambda y: True if y == "9" else False, x)), open("Day9.txt").read().split("\n")))

def area(x, y):
    if y < 0 or y >= len(file) or x < 0 or x >= len(file[y]) or file[y][x]:
        return 0
    file[y][x] = True
    n = 1
    for i, j in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
        n += area(x + i, y + j)
    return n

areas = []
for i in range(len(file)):
    while False in file[i]:
        areas.append(area(file[i].index(False), i))
        if len(areas) > 3:
            areas.remove(min(areas))

print(areas)
print(areas[0] * areas[1] * areas[2])
