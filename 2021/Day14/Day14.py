string, rules = open("Day14.txt", "r").read().split("\n\n")
rules = {rule[:2]: rule[-1] for rule in rules.split("\n")}

res = {string[-1]: 1}
x = dict()
for i in range(len(string) - 1):
    if string[i:i + 2] in x:
        x[string[i:i + 2]] += 1
    else:
        x[string[i:i + 2]] = 1

for _ in range(40):
    new_x = dict()
    for key, value in x.items():
        for new_key in [key[0] + rules[key], rules[key] + key[1]]:
            if new_key in new_x:
                new_x[new_key] += value
            else:
                new_x[new_key] = value
    x = new_x

for key, value in x.items():
    if key[0] in res:
        res[key[0]] += value
    else:
        res[key[0]] = value

print(max(res.values()) - min(res.values()))
