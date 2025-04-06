print(sum(not any(list(map(lambda x: sorted(list(x)), password.split(" "))).count(word) > 1 for word in list(map(lambda x: sorted(list(x)), password.split(" ")))) for password in open("test.txt", "r").read().split("\n")))


