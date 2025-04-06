numbers, boards = open("Day 4.txt", "r").read().split("\n\n", 1)

numbers = map(int, numbers.split(","))
boards = boards.split("\n\n")

for i, board in enumerate(boards):
    board = list(map(lambda x: list(map(int, x.split())), board.split("\n")))
    boards[i] = board + [[row[col] for row in board] for col in range(len(board))]


def bingo():
    global boards
    for n in numbers:
        for i, board in enumerate(boards):
            for row in board:
                if n in row:
                    row.remove(n)
                    if row == []:
                        winner = map(lambda x: sum(x), board[:5]), n
                        boards[i] = []
        boards = [board for board in boards if board]
    return winner

board, n = bingo()
print(sum(board) * n)
