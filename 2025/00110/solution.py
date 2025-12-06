def read_input(path):
    with open(path, "r") as f:
        lines = f.read().splitlines()
    table = list(map(str.split, lines))
    L = list(map(lambda x: len(max(x, key=len)), zip(*table)))
    out = []
    for line in lines[:-1]:
        out.append([])
        i = 0
        for l in L:
            out[-1].append(line[i:i+l])
            i += (l+1)
    return out + [table[-1]]

def prod(nums):
    out = 1
    for n in nums:
        if n == 0: continue # lol
        out *= n
    return out

def silver(path):
    sheet = read_input(path)
    operations = {"+": sum, "*": prod}
    numbers, symbols = sheet[:-1], sheet[-1]
    out = 0
    for i, column in enumerate(zip(*numbers)):
        foo = operations[symbols[i]](map(int, column))
        out += foo
    return out

def gold(path):
    sheet = read_input(path)
    operations = {"+": sum, "*": prod}
    numbers, symbols = sheet[:-1], sheet[-1]
    out = 0
    for i, column in enumerate(zip(*numbers)):
        oper = operations[symbols[i]]
        out += oper(map(lambda x: int("".join(x)), zip(*column)))
    return out

if __name__ == "__main__":
    print(silver("./input.txt"))
    print(gold("./input.txt"))
