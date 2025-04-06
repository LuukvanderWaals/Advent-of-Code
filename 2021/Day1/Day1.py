file = list(map(int, open("Day 1 input.txt", "r").read().split()))

count = 0
for i in range(len(file) - 3):
    if file[i] < file[i + 3]:
        count += 1

print(count)
