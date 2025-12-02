def repeats(n):
    s = str(n)
    l = len(s)
    return s[:l//2] == s[l//2:]


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


if __name__ == "__main__":
    print(silver(path="./input.txt"))
