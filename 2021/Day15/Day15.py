f = list(map(lambda x: [int(i) for i in x], open("Day15.txt", "r").read().split()))
size = len(f)
state = {(0, 0): 0}

for _ in range(4):
    for i in range(len(f)):
        f[i] += map(lambda x: x % 9 + 1, f[i][-size:])

for i in range(4):
    for j in range(size):
        f.append(list(map(lambda x: (x + i) % 9 + 1, f[j])))

count = 0
while state:
    count += 1
    if count % 2500 == 0:
        print(count / 2500)
    (x, y), l = min(state.items(), key = lambda x: x[1])
    if x == y == len(f) - 1:
        print(l)
        break
    state.pop((x, y))
    f[x][y] = None
    for dx, dy in [(-1, 0), (0, -1), (0, 1), (1, 0)]:
        if min(x + dx, y + dy) >= 0 and max(x + dx, y + dy) < len(f) and f[x + dx][y + dy] != None and ((x + dx, y + dy) not in state or l + f[x + dx][y + dy] < state[(x + dx, y + dy)]):
            state[(x + dx, y + dy)] = l + f[x + dx][y + dy]

print(count)
