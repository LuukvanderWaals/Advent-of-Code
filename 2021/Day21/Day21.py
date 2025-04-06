player = [5, 10]

class die:
    def __init__(self):
        self.value = 1
        self.thrown = 0

    def throw(self, n):
        res = 0
        for _ in range(n):
            res += self.value
            self.value = self.value % 100 + 1
        self.thrown += n
        return res

score = [0, 0]
d = die()
turn = 0
while True:
    player[turn] = (player[turn] + d.throw(3) - 1) % 10 + 1
    score[turn] += player[turn]
    if score[turn] >= 1000:
        break
    turn = (turn + 1) % 2

print(min(score) * d.thrown)

throws = [x + y + z for x in range(1, 4) for y in range(1, 4) for z in range(1, 4)]
throws = {throw: throws.count(throw) for throw in throws}.items()

def solve(player, score, turn):
    wins = [0, 0]
    for throw, n in throws:
        if score[turn] + (player[turn] + throw - 1) % 10 + 1 >= 21:
            wins[turn] += n
        else:
            new_player = player.copy()
            new_player[turn] = (player[turn] + throw - 1) % 10 + 1
            new_score = score.copy()
            new_score[turn] += new_player[turn]
            wins0, wins1 = solve(new_player, new_score, (turn + 1) % 2)
            wins[0] += wins0 * n
            wins[1] += wins1 * n
    return wins

print(max(solve([5, 10], [0, 0], 0)))
