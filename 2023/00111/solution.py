"""
--- Day 8: Haunted Wasteland ---

See map.png for visualization of the map.

@imveikka
"""

from sys import argv
import numpy as np

lines = [f.strip() for f in open(argv[1], 'r')]
tree = {line[:3]: (line[7:10], line[12:15]) for line in lines[2:]}
table = {'L': 0, 'R': 1}

# Silver

current = 'AAA'
for i, direction in enumerate(lines[0] * 100):
    current = tree[current][table[direction]]
    if current == 'ZZZ':
        print('silver', i+1)
        break

# Gold

currents = [node for node in tree if node[-1] == 'A']
steps = []
for current in currents:
    for i, direction in enumerate(lines[0] * 100):
        current = tree[current][table[direction]]
        if current[-1] == 'Z':
            steps.append(i+1)
            break
gold = np.lcm.reduce(steps)
print('gold', gold)

