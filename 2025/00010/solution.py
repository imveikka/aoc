def repeats(n):
    s = str(n)
    l = len(s)
    return s[:l//2] == s[l//2:]


def repeats_at_least_two(n):
    s = str(n)
    l = len(s)
    W = filter(lambda x: l % x == 0, range(1, l))
    for w in W:
        if len({s[i:i+w] for i in range(0, l, w)}) == 1:
            return True
    return False


def silver(path="./test.txt"):
    with open(path, "r") as f:
        lines = f.read()[:-1]
    pairs = lines.split(',')
    out = 0
    for pair in pairs:
        a, b = map(int, pair.split("-"))
        repetitions = filter(repeats, range(a, b+1))
        out += sum(repetitions)
    return out


def gold(path="./test.txt"):
    with open(path, "r") as f:
        lines = f.read()[:-1]
    pairs = lines.split(',')
    out = 0
    for pair in pairs:
        a, b = map(int, pair.split("-"))
        repetitions = filter(repeats_at_least_two, range(a, b+1))
        out += sum(repetitions)
    return out


if __name__ == "__main__":
    print(silver(path="./input.txt"))
    print(gold(path="./input.txt"))
