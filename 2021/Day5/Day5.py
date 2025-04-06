file = open("Day 5.txt", "r").read()

size = 1000
l = [[0] * size for _ in range(size)]

for line in file.split("\n"):
    x1, y1, x2, y2 = map(int, line.replace(" -> ", ",").split(","))
    while True:
        l[y1][x1] += 1

        if x1 == x2 and y1 == y2:
            break

        if x1 != x2:
            x1 += 1 if x2 > x1 else -1
        if y1 != y2:
            y1 += 1 if y2 > y1 else -1


print(sum(map(lambda x: x >= 2, [i for j in l for i in j])))
