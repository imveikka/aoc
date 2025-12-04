from itertools import product


def readinput(path):
    with open(path, "r") as f:
        return list(map(list, f.read().splitlines()))


def silver(path):
    grid = readinput(path)
    h, w = len(grid), len(grid[0])
    out = 0
    for i, j in product(range(h), range(w)):
        if grid[i][j] == ".": continue
        wh = range(max(i-1, 0), min(i+2, h))
        ww = range(max(j-1, 0), min(j+2, w))
        hits = -1
        for ii, jj in product(wh, ww):
            hits += grid[ii][jj] == "@"
        out += hits < 4
    return out


def gold(path):
    grid = readinput(path)
    h, w = len(grid), len(grid[0])
    out = 0
    while True:
        locs = set()
        for i, j in product(range(h), range(w)):
            if grid[i][j] == ".": continue
            wh = range(max(i-1, 0), min(i+2, h))
            ww = range(max(j-1, 0), min(j+2, w))
            hits = -1
            for ii, jj in product(wh, ww):
                hits += grid[ii][jj] == "@"
            if hits < 4:
                locs.add((i, j))
        out += len(locs)
        if len(locs) > 0:
            for ii, jj in locs:
                grid[ii][jj] = "."
        else:
            break
    return out


if __name__ == "__main__":
    print(silver("./input.txt"))
    print(gold("./input.txt"))

