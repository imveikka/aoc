def silver(path="./big.txt", start=50, n=100):
    out = 0
    sign = {"R": 1, "L": -1}
    with open(path, "r") as f:
        for line in f:
            shift = sign[line[0]] * int(line[1:-1]) % n
            start += shift + n
            out += (start % n == 0)
    return out


def gold(path="./big.txt", start=50, n=100):
    out = 0
    sign = {"R": 1, "L": -1}
    with open(path, "r") as f:
        for line in f:
            shift = int(line[1:-1])
            out += shift // n
            shift = sign[line[0]] * (shift % n)
            extra = start != 0
            start += shift 
            out += (extra and (start <= 0 or start >= n))
            start = (n + start) % n
    return out


if __name__ == "__main__":
    print(silver())
    print(gold())
