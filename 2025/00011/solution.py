from itertools import combinations


def readlines(path):
    with open(path, "r") as f:
        return f.read().splitlines()


def max_joltage_naive(bank, r=2):
    S = max(combinations(bank, r=r), key=lambda x: int("".join(x)))
    return int("".join(S))


def max_joltage_fast(bank, r=2):
    n = len(bank)
    batteries = ['0'] * r
    loc = 0
    for i in range(r):
        val, shift = mymax(bank[loc:n-(r-i-1)])
        batteries[i] = val
        loc += shift + 1
    return int("".join(batteries))


def mymax(seq):
    idx, val = -1, '0'
    for i, x in enumerate(seq):
        if x > val:
            idx = i
            val = x
    return val, idx


def silver(path="./test.txt"):
    banks = map(list, readlines(path))
    return sum(max_joltage_fast(bank, 2) for bank in banks)


def gold(path="./test.txt"):
    banks = map(list, readlines(path))
    removed = [max_joltage_fast(bank, 12) for bank in banks]
    return sum(removed)


if __name__ == "__main__":
    print(silver(path="./input.txt"))
    print(gold(path="./input.txt"))
