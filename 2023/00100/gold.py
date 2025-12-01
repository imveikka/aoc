"""
--- Part Two ---

Never give up.

I debugged this thing about half of the time.

@imveikka
"""

from sys import argv
import numpy as np
from itertools import pairwise
from tqdm import tqdm
from io import StringIO
from re import sub

with open(argv[1], 'r') as f:
    lines = f.read().split('\n\n')

seeds = [int(seed) for seed in lines[0].split()[1:]]
seeds = [range(a, a+b) for a, b in np.reshape(seeds, (len(seeds) // 2, 2))]

make_range = lambda param: \
    [range(param[1], param[1] + param[2]),
     range(param[0], param[0] + param[2])]
make_ranges = lambda param: [make_range(p) for p in param]
loadtxt = lambda param: \
    np.loadtxt(param, delimiter=' ', dtype=int)
get_maps = lambda param: param.split('\n', 1)[1]

maps_sub = map(get_maps, lines[1: ])
maps_io = map(StringIO, maps_sub)
maps_np = map(loadtxt, maps_io)
maps = [make_ranges(param) for param in maps_np]

for pairs in maps:
    start = np.inf
    for foo, _ in pairs:
        start = min(start, foo.start)
    pairs.append((range(start), range(start)))

range_and = lambda r1, r2: \
    range(max(r1.start, r2.start), min(r1.stop, r2.stop))

range_rem = lambda r1, r2: \
    (range(r1.start, r2.start), range(r2.stop, r1.stop)) \
    if r1.start <= r2.stop and r1.stop >= r2.start \
    else (r1, range(0))

used = set()
gold = np.inf

def traverse(seed, level):

    if level == len(maps):
        global gold
        gold = min(gold, min(seed))
        return 

    leftovers = {seed}

    for source, dest in maps[level]:
        foo = range_and(seed, source)
        if len(foo) > 0:
            bar = range(foo.start + (dest.start - source.start),
                        foo.stop + (dest.start - source.start))
            if (bar, level + 1) not in used:
                traverse(bar, level + 1)
                used.add((bar, level + 1))
        leftovers = {side for \
            prev in leftovers for \
            side in range_rem(prev, source) if \
            len(side) > 0}

    for untouched in leftovers:
        if (untouched, level + 1) not in used:
            traverse(untouched, level + 1)
            used.add((untouched, level + 1))

[traverse(seed, 0) for seed in seeds]
print(gold)

