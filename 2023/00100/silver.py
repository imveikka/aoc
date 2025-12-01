"""
--- Day 5: If You Give A Seed A Fertilizer ---

Took longer to understand what to do.

@imveikka
"""


from sys import argv
import numpy as np
from itertools import pairwise
from tqdm import tqdm

with open(argv[1], 'r') as f:
    lines = f.read().split('\n\n')

seeds = lines[0].split()[1:]

mappings = {}
for line in lines[1:]:
    data = line.splitlines()
    from_to, _ = data[0].split()
    mappings[from_to] = []
    for ranges in data[1:]:
        s_d, s_s, inc = np.fromstring(ranges, dtype=int, sep=' ')
        mappings[from_to] += [(range(s_s, s_s + inc),
                               range(s_d, s_d + inc))]

silver = np.inf
for seed in seeds:
    foo = int(seed)
    for pairs in mappings.values():
        for source, dest in pairs:
            if foo in source:
                foo = dest.start + (foo - source.start)
                break
    silver = min(silver, foo)

print(silver)

