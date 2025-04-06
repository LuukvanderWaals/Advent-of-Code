from math import floor

iterations = ([x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13] for x0 in range(9, 0, -1) for x1 in range(9, 0, -1) for x2 in range(9, 0, -1) for x3 in range(9, 0, -1) for x4 in range(9, 0, -1) for x5 in range(9, 0, -1) for x6 in range(9, 0, -1) for x7 in range(9, 0, -1) for x8 in range(9, 0, -1) for x9 in range(9, 0, -1) for x10 in range(9, 0, -1) for x11 in range(9, 0, -1) for x12 in range(9, 0, -1) for x13 in range(9, 0, -1))

for n in iterations:
    print(n)
    index = 0
    var  = {"w": 0, "x": 0, "y": 0, "z": 0}
    for i in open("Day24.txt", "r").read().split("\n"):
        i, v = i.split(" ", 1)
        v = v.split(" ")

        if i == "inp":
            var[v[0]] = n[index]
            index += 1
        elif i == "add":
            if v[1].replace("-", "").isnumeric():
                var[v[0]] += int(v[1])
            else:
                var[v[0]] += var[v[1]]
        elif i == "mul":
            if v[1].replace("-", "").isnumeric():
                var[v[0]] *= int(v[1])
            else:
                var[v[0]] *= var[v[1]]
        elif i == "div":
            if v[1].replace("-", "").isnumeric():
                var[v[0]] /= int(v[1])
            else:
                var[v[0]] /= var[v[1]]
            var[v[0]] = floor(var[v[0]])
        elif i == "mod":
            if v[1].replace("-", "").isnumeric():
                var[v[0]] %= int(v[1])
            else:
                var[v[0]] %= var[v[1]]
        elif i == "":
            if v[1].replace("-", "").isnumeric():
                var[v[0]] = var[v[0]] == int(v[1])
            else:
                var[v[0]] = var[v[0]] == var[v[1]]
    if var["z"] == 0:
        print(n)
        break
