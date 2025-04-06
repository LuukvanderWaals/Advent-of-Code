points, folds = open("Day13.txt", "r").read().split("\n\n")
points = [[int(point.split(",")[0]), int(point.split(",")[1])] for point in points.split()]

size = [0, 0]
for fold in folds.split("\n"):
    direction = fold[11] == "y"
    value = int(fold[13:])
    for point in points:
        point[direction] = value - abs(point[direction] - value)
    size[direction] = value

    n = 0
    for y in range(size[1]):
        for x in range(size[0]):
            if [x, y] in points:
                n += 1
                print("#", end="")
            else:
                print(".", end="")
        print()

    print(n)
