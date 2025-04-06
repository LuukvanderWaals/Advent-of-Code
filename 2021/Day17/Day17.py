x1, x2, y1, y2 = map(int, open("Day17.txt", "r").read().split(" "))

count = 0
for i in range(1, x2 + 1):
    for j in range(y1, -y1 + 1):
        xv = i
        yv = j
        x = y = 0
        while x <= x2 and y >= y1:
            if x >= x1 and y <= y2:
                print(i, j)
                count += 1
                break

            x += xv
            y += yv
            if xv > 0:
                xv -= 1
            yv -= 1

print(count)
