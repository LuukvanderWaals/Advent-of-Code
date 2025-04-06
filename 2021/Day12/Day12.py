grotten = {}

for i in open("Day12.txt", "r").read().split():
    grot1, grot2 = i.split("-")

    if grot1 in grotten:
        grotten[grot1].append(grot2)
    else:
        grotten[grot1] = [grot2]

    if grot2 in grotten:
        grotten[grot2].append(grot1)
    else:
        grotten[grot2] = [grot1]


def vind_pad(grot, pad):
    n = 0
    for i in grotten[grot]:
        if i == "end":
            n += 1
        elif i.isupper() or i not in pad or (i != "start" and not any(x.islower() for x in pad if pad.count(x) > 1)):
            n += vind_pad(i, pad + [i])
    return n

print(vind_pad("start", ["start"]))
