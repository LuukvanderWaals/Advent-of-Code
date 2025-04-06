from operator import add, mul

f = open("Day16.txt", "r").read()
packets = bin(int(f, 16))[2:].zfill(len(f) * 4)

class packet():
    def __init__(self, string):
        self.version = int(string[:3], 2)
        self.type = int(string[3:6], 2)
        self.subpackets = []
        if self.type == 4:
            self.value = 0
            self.total_length = 11
            i = 6
            while True:
                self.value += int(string[i + 1:i + 5], 2)
                if string[i] == "0":
                    break
                self.value <<= 4
                self.total_length += 5
                i += 5
        else:
            self.value = 0
            if string[6] == "0":
                self.length = int(string[7:22], 2)
                self.total_length = 22 + self.length
                length = 0
                while length != self.length:
                    self.subpackets.append(packet(string[22 + length:self.total_length]))
                    length += self.subpackets[-1].total_length
                    if self.type == 0:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value += self.subpackets[-1].value
                    elif self.type == 1:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value *= self.subpackets[-1].value
                    elif self.type == 2:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value = min(self.value, self.subpackets[-1].value)
                    elif self.type == 3:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value = max(self.value, self.subpackets[-1].value)
                    elif self.type == 5 and len(self.subpackets) == 2:
                        self.value = int(self.subpackets[0].value > self.subpackets[1].value)
                    elif self.type == 6 and len(self.subpackets) == 2:
                        self.value = int(self.subpackets[0].value < self.subpackets[1].value)
                    elif self.type == 7 and len(self.subpackets) == 2:
                        self.value = int(self.subpackets[0].value == self.subpackets[1].value)
            else:
                self.length = int(string[7:18], 2)
                self.total_length = 18
                length = 0
                while len(self.subpackets) != self.length:
                    self.subpackets.append(packet(string[18 + length:]))
                    self.total_length += self.subpackets[-1].total_length
                    length += self.subpackets[-1].total_length
                    if self.type == 0:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value += self.subpackets[-1].value
                    elif self.type == 1:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value *= self.subpackets[-1].value
                    elif self.type == 2:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value = min(self.value, self.subpackets[-1].value)
                    elif self.type == 3:
                        if len(self.subpackets) == 1:
                            self.value = self.subpackets[-1].value
                        else:
                            self.value = max(self.value, self.subpackets[-1].value)
                    elif self.type == 5 and len(self.subpackets) == 2:
                        self.value = int(self.subpackets[0].value > self.subpackets[1].value)
                    elif self.type == 6 and len(self.subpackets) == 2:
                        self.value = int(self.subpackets[0].value < self.subpackets[1].value)
                    elif self.type == 7 and len(self.subpackets) == 2:
                        self.value = int(self.subpackets[0].value == self.subpackets[1].value)
                self.length = length

    def __str__(self, childeren = True, all = True):
        string = "version: %d\ntype: %d\ntotal_length: %d\nvalue: %d" % (self.version, self.type, self.total_length, self.value)

        if self.type != 4:
            string += "\nsubpackets: %d\nlength: %d" % (len(self.subpackets), self.length)
            if childeren == True:
                string += "".join("\n|\n|   " + s.__str__(all).replace("\n", "\n|   ") for s in self.subpackets)
            else:
                string += "\n|\n|   ..."

        return string

packets = [packet(packets)]

print(packets[0])

print(packets[0].value)


res = 0
while packets:
    packet = packets.pop()
    res += packet.version
    packets += packet.subpackets
print(res)
