from copy import deepcopy

rooms = [["D", "D", "D", "C"], ["A", "B", "C", "C"], ["B", "A", "B", "B"], ["A", "C", "A", "D"]]
hallway = [None] * 11
room_index = [2, 4, 6, 8]

def solve(rooms, hallway, p = False):
    res_min = None
    for pos, amphipod in enumerate(hallway):
        if amphipod:
            if sum(hallway[i] != None for i in range(min(pos, room_index[ord(amphipod) - 65]), max(pos, room_index[ord(amphipod) - 65]) + 1)) == 1 and all(i == amphipod for i in rooms[ord(amphipod) - 65]):
                rooms[ord(amphipod) - 65].append(amphipod)
                hallway[pos] = None
                score = pow(10, ord(amphipod) - 65) * (abs(pos - room_index[ord(amphipod) - 65]) + 5 - len(rooms[ord(amphipod) - 65]))
                res = solve(rooms, hallway)
                if res != None:
                    return res + score
                else:
                    return

    for index, room in enumerate(rooms):
        if room and ord(room[-1]) - 65 != index:
            if not any(hallway[i] != None for i in range(min(room_index[index], room_index[ord(room[-1]) - 65]), max(room_index[index], room_index[ord(room[-1]) - 65]))):
                if all(i == room[-1] for i in rooms[ord(room[-1]) - 65]):
                    amphipod = rooms[index].pop()
                    rooms[ord(amphipod) - 65].append(amphipod)
                    score = pow(10, ord(amphipod) - 65) * (abs(room_index[index] - room_index[ord(amphipod) - 65]) + 9 - len(rooms[index]) - len(rooms[ord(amphipod) - 65]))
                    res = solve(rooms, hallway)
                    if res != None:
                        return res + score
                    else:
                        return

    for index, room in enumerate(rooms):
        if room and any(i != chr(65 + index) for i in room):
            for pos in range(len(hallway)):
                if pos not in room_index and not any(hallway[i] != None for i in range(min(pos, room_index[index]), max(pos, room_index[index]) + 1)):
                    if p:
                        print(room, pos)
                    rooms_copy = deepcopy(rooms)
                    amphipod = rooms_copy[index].pop()
                    hallway_copy = hallway.copy()
                    hallway_copy[pos] = amphipod
                    score = pow(10, ord(amphipod) - 65) * (abs(pos - room_index[index]) + 5 - len(rooms[index]))
                    res = solve(rooms_copy, hallway_copy)
                    if p:
                        print(res)
                    if res != None and (not res_min or res + score < res_min):
                        res_min = res + score

    if res_min:
        return res_min
    if all(i == None for i in hallway):
        return 0

print(solve(rooms, hallway, True))
