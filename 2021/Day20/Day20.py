string, image = open("Day20.txt", "r").read().split("\n\n")

image = set((x, y) for y, row in enumerate(image.split()) for x, pixel in enumerate(row) if pixel == "#")

token = "."
for i in range(50):
    new_image = set()
    pixels = set((x + dx, y + dy) for x, y in image for dx in range(-1, 2) for dy in range(-1, 2))
    for x, y in pixels:
        i = 0
        for dy in range(-1, 2):
            for dx in range(-1, 2):
                i <<= 1
                if (token == ".") == ((x + dx, y + dy) in image):
                    i += 1
        if string[i] == token:
            new_image.add((x, y))
    token = "#" if token == "." else "."

    image = new_image

print(len(image))


# for y in range(-3, 4):
#     for x in range(-3, 4):
#         if (x, y) in image:
#             print(".", end="")
#         else:
#             print("#", end="")
#     print()

