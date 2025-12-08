from itertools import count, product

def read_input(path):
    with open(path, "r") as f:
        lines = f.read().splitlines()
    return [list(map(int, line.split(","))) for line in lines]

def l2_distance(vec):
    return sum(elem**2 for elem in vec)**.5

def vec_diff(v1, v2):
    return [e1 - e2 for e1, e2 in zip(v1, v2)]

def silver(path, k):
    locs = read_input(path)
    n = len(locs)
    adj_list = [(i, j, l2_distance(vec_diff(locs[i], locs[j]))) for i, j in product(range(n), range(n)) if i < j]
    adj_list = sorted(adj_list, key=lambda x: x[2])
    roots = list(range(n))
    for _, (i, j, d) in zip(range(k), adj_list):
        while roots[i] != i: i = roots[i]
        while roots[j] != j: j = roots[j]
        if i != j:
            if i < j: roots[j] = i
            else: roots[i] = j
    counts = {}
    for i in range(n):
        while roots[i] != i: i = roots[i]
        if i not in counts: counts[i] = 1
        else: counts[i] += 1
    a, b, c = sorted(counts.values())[:-4:-1]
    return a * b * c

def gold(path):
    locs = read_input(path)
    n = len(locs)
    adj_list = [(i, j, l2_distance(vec_diff(locs[i], locs[j]))) for i, j in product(range(n), range(n)) if i < j]
    adj_list = sorted(adj_list, key=lambda x: x[2])
    roots = list(range(n))
    c, C = 0, n-1
    for i, j, _ in adj_list:
        out = locs[i][0] * locs[j][0]
        while roots[i] != i: i = roots[i]
        while roots[j] != j: j = roots[j]
        if i != j:
            if i < j: roots[j] = i
            else: roots[i] = j
            c += 1
            if c == C: break
    return out

if __name__ == "__main__":
    print(silver("./input.txt", 1000))
    print(gold("./input.txt"))
