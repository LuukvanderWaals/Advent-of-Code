class File:
    def __init__(self, name, size):
        self.name = name
        self.size = size


class Dir:
    def __init__(self, name, parent = None):
        self.name = name
        self.content = {"..": parent} if parent else {}

    def ls(self):
        for i in self.content.values():
            if type(i) == Dir:
                print("dir", i.name)
            else:
                print(i.size, i.name)

    def cd(self, name):
        if name == "/":
            return home
        return self.content[name]

    def mkdir(self, name):
        self.content[name] = Dir(name, self)

    def touch(self, name, size):
        self.content[name] = File(name, size)


home = Dir("/")

def create_file_system(f):
    d = home
    i = 0
    while i < len(f):
        cmd = f[i][2:].split()
        if cmd[0] == "cd":
            d = d.cd(cmd[1])
            i += 1
        elif cmd[0] == "ls":
            i += 1
            while i < len(f) and f[i][0] != "$":
                type_size, name = f[i].split()
                if type_size == "dir":
                    d.mkdir(name)
                else:
                    d.touch(name, int(type_size))
                i += 1


def solve(d):
    size = 0
    sizes = []
    for name, i in d.content.items():
        if name == "..":
            continue
        if type(i) == Dir:
            sizes += solve(i)
            size += sizes[-1]
        else:
            size += i.size

    return sizes + [size]


def main():
    create_file_system(open("input.txt", "r").read().split("\n"))
    sizes = solve(home)
    sizes = [i for i in sizes if i >= sizes[-1] - 40_000_000]
    print(min(sizes))

if __name__ == "__main__":
    main()
