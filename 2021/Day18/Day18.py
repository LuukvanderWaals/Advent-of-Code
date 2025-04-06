import math

f = open("Day18.txt", "r").read().split()

class tree:
    def __init__(self, string, parent = None, parent_left = None):
        self.parent = parent
        self.parent_left = parent_left
        if string[0] == "[":
            self.type = "node"
            stack = 0
            for i, char in enumerate(string[1:]):
                if char == "[":
                    stack += 1
                elif char == "]":
                    stack -= 1
                if stack == 0:
                    break
            i = string.find(",", i)
            self.left_child = tree(string[1:i], self, False)
            self.right_child = tree(string[i + 1:-1], self, True)
        else:
            self.type = "leaf"
            self.value = int(string)

    def explode(self):
        explosion = self.find_explosion()
        if not explosion:
            return False
        left = explosion.search_left()
        if left:
            left.value += explosion.left_child.value
        right = explosion.search_right()
        if right:
            right.value += explosion.right_child.value
        if explosion.parent_left:
            explosion.parent.right_child = tree("0", explosion.parent, True)
        else:
            explosion.parent.left_child = tree("0", explosion.parent, False)
        return True

    def find_explosion(self, depth = 0):
        if self.type == "node":
            if depth == 4:
                return self
            for child in [self.left_child, self.right_child]:
                explosion = child.find_explosion(depth + 1)
                if explosion:
                    return explosion

    def search_left(self):
        node = self
        while node.parent_left == False:
            node = node.parent
        if node.parent_left == True:
            node = node.parent.left_child
            while node.type == "node":
                node = node.right_child
            return node

    def search_right(self):
        node = self
        while node.parent_left == True:
            node = node.parent
        if node.parent_left == False:
            node = node.parent.right_child
            while node.type == "node":
                node = node.left_child
            return node

    def split(self):
        split = self.find_split()
        if not split:
            return False
        s = "[" + str(math.floor(split.value / 2)) + "," + str(math.ceil(split.value / 2)) + "]"
        if split.parent_left:
            split.parent.right_child = tree(s, split.parent, True)
        else:
            split.parent.left_child = tree(s, split.parent, False)
        return True


    def find_split(self):
        if self.type == "leaf":
            if self.value >= 10:
                return self
        else:
            for child in [self.left_child, self.right_child]:
                split = child.find_split()
                if split:
                    return split


    def magnitude(self):
        if self.type == "leaf":
            return self.value
        return 3 * self.left_child.magnitude() + 2 * self.right_child.magnitude()


    def __str__(self):
        if self.type == "node":
            return "[" + str(self.left_child) + "," + str(self.right_child) + "]"
        return str(self.value)

t = tree(f[0])

for i in range(1, len(f)):
    t = tree("[" + str(t) + "," + f[i] + "]")
    while True:
        if not (t.explode() or t.split()):
            break

print(t.magnitude())

max_magnitude = 0
for i in f:
    for j in f:
        t = tree("[" + i + "," + j + "]")
        while True:
            if not (t.explode() or t.split()):
                break
        max_magnitude = max(max_magnitude, t.magnitude())

print(max_magnitude)
