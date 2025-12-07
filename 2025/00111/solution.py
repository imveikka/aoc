def read_input(path):
    with open(path, "r") as f:
        lines = f.read().splitlines()
    return list(map(list, lines))

def silver(path):
    grid = read_input(path)
    curr = {grid[0].index("S"),}
    out = 0
    for level in grid[1:]:
        splits = {i for i in curr if level[i] == "^"}
        curr -= splits  
        curr |= {i+1 for i in splits} | {i-1 for i in splits}
        out += len(splits)
    return out

def gold(path):
    grid = read_input(path)
    pascal = {grid[0].index("S"): 1,}
    for level in grid[1:]:
        splits = {i for i in pascal if level[i] == "^"}
        for i in splits:
            if i+1 not in pascal: pascal[i+1] = pascal[i]
            else: pascal[i+1] += pascal[i]
            if i-1 not in pascal: pascal[i-1] = pascal[i]
            else: pascal[i-1] += pascal[i]
            del pascal[i]
    return sum(pascal.values())

if __name__ == "__main__":
    print(silver("./input.txt"))
    print(gold("./input.txt"))
