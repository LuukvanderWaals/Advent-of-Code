dumbos = list(map(lambda x: [[int(i), 0] for i in x], open("Day11.txt", "r").read().split("\n")))
n = len(dumbos[0])
flashes = 0


def dumbo(x, y, step):
    global flashes
    if dumbos[y][x][1] != step:
        if dumbos[y][x][0] == 9:
            flashes += 1
            dumbos[y][x] = [0, step]
            for dx in [-1, 0, 1]:
                for dy in [-1, 0, 1]:
                    if (dx != 0 or dy != 0) and min(x + dx, y + dy) >= 0 and max(x + dx, y + dy) < n:
                        dumbo(x + dx, y + dy, step)
        else:
            dumbos[y][x][0] += 1

step = 0
while True:
    step += 1
    for y in range(len(dumbos)):
        for x in range(len(dumbos[y])):
            dumbo(x, y, step)

    if step == 100:
        print(flashes)


    if max(max(i)[0] for i in dumbos) == 0:
        print(step)
        break
