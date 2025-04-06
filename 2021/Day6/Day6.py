file = list(map(int, open("Day 6.txt", "r").read().split(",")))

fishes = [file.count(i) for i in range(9)]
print(fishes)

for _ in range(256):
    new_fishes = [0 for i in range(9)]
    for i, n in enumerate(fishes):
        if i == 0:
            new_fishes[6] += n
            new_fishes[8] += n
        else:
            new_fishes[i - 1] += n
    fishes = new_fishes

print(sum(fishes))
