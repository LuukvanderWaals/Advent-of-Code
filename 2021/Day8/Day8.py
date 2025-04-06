# print(sum(1 for i in list(map(lambda x: x.split(" ")[11:], open("Day8.txt", "r").read().split("\n"))) for j in i if len(j) not in [5, 6]))

letters = ["a", "b", "c", "d", "e", "f", "g"]
digits = "abcefg cf acdeg acdfg bcdf abdfg abdefg acf abcdefg abcdfg"

hashmap = {letter: digits.count(letter) for letter in letters}

d = {sum(hashmap[line] for line in digit): i for i, digit in enumerate(digits.split())}

res = 0
for inp, output in map(lambda x: (x.split("|")[0].replace(" ", ""), x.split(" ")[11:]), open("Day8.txt", "r").read().split("\n")):
    hashmap = {i: 0 for i in letters}

    v = {i: 0 for i in letters}
    for i in inp:
        v[i] += 1

    display = 0
    for digit in output:
        n = 0
        for line in digit:
            n += v[line]
        display = display * 10 + d[n]

    # print(display)
    res += display

print()
print(res)
