file = open("Day2.txt", "r").read().split("\n")

x = y = aim = 0
for line in file:
    d, X = line.split()

    if d == "forward":
        x += int(X)
        y += aim * int(X)
    elif d == "up":
        aim -= int(X)
    elif d == "down":
        aim += int(X)

print(x * y)
