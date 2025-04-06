sea = list(map(lambda x: list(x), open("Day25.txt", "r").read().split()))

change = True
step = 0
while change:
    step += 1
    change = False
    for y in range(len(sea)):
        check = False
        l = []
        for x in range(len(sea[y])):
            if check:
                check = False
                continue
            if sea[y][x] == ">" and sea[y][(x + 1) % len(sea[y])] == ".":
                l.append(x)
                check = True
                change = True
        for x in l:
            sea[y][(x + 1) % len(sea[y])] = ">"
            sea[y][x] = "."


    for x in range(len(sea[y])):
        check = False
        l = []
        for y in range(len(sea)):
            if check:
                check = False
                continue
            if sea[y][x] == "v" and sea[(y + 1) % len(sea)][x] == ".":
                l.append(y)
                check = True
                change = True

        for y in l:
            sea[(y + 1) % len(sea)][x] = "v"
            sea[y][x] = "."

    print(step)
    print("\n".join("".join(i) for i in sea))
    print()
