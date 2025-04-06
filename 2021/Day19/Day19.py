f = open("Day19.txt", "r").read().split("\n\n")

class sensor:
    def __init__(self, string, pos = None):
        self.beacons = [tuple(map(int, beacon.split(","))) for beacon in string.split("\n")[1:]]
        self.pos = pos

    def match(self, other):
        for beacon in self.beacons:
            for other_beacon in other.beacons:
                self.pos = (other_beacon[0] - beacon[0], other_beacon[1] - beacon[1], other_beacon[2] - beacon[2])

                other_beacons = {beacon for beacon in other.beacons if beacon[0] >= self.pos[0] - 1000 and
                                                                       beacon[0] <= self.pos[0] + 1000 and
                                                                       beacon[1] >= self.pos[1] - 1000 and
                                                                       beacon[1] <= self.pos[1] + 1000 and
                                                                       beacon[2] >= self.pos[2] - 1000 and
                                                                       beacon[2] <= self.pos[2] + 1000}
                beacons = [beacon for beacon in self.beacons if beacon[0] + self.pos[0] >= other.pos[0] - 1000 and
                                                                beacon[0] + self.pos[0] <= other.pos[0] + 1000 and
                                                                beacon[1] + self.pos[1] >= other.pos[1] - 1000 and
                                                                beacon[1] + self.pos[1] <= other.pos[1] + 1000 and
                                                                beacon[2] + self.pos[2] >= other.pos[2] - 1000 and
                                                                beacon[2] + self.pos[2] <= other.pos[2] + 1000]


                if len(beacons) == len(other_beacons) and len(beacons) >= 12:
                    print(beacon, other_beacon, self.pos)
                    print(beacons)
                    print(other_beacons)
                    print()
                    n = 0
                    for b in beacons:
                        b = (b[0] + self.pos[0], b[1] + self.pos[1], b[2] + self.pos[2])
                        print(b)
                        if b in other_beacons:
                            n += 1
                        else:
                            break
                    print(n)
                    if n == len(beacons):
                        print("test")


print(sensor(f[1]).match(sensor(f[0], (0, 0, 0))))

# for i in f[1:]:

