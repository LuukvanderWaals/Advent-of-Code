file = open("Day10.txt", "r").read().split("\n")

score_c = {")": 3, "]": 57, "}": 1197, ">": 25137}
score_i  = {")": 1, "]": 2, "}": 3, ">": 4}
brackets = {"(": ")", "[": "]", "{": "}", "<": ">"}

corrupted = 0
incomplete = []
for line in file:
    stack = []
    c = False
    for bracket in line:
        if bracket not in brackets and stack.pop() != bracket:
            corrupted += score_c[bracket]
            c = True
            break
        elif bracket in brackets:
            stack.append(brackets[bracket])
    if c == False:
        score = 0
        while stack:
            score = score * 5 + score_i[stack.pop()]
        incomplete.append(score)

incomplete.sort()

print(corrupted)
print(incomplete[int(len(incomplete) / 2)])
