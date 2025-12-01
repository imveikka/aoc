"""
--- Day 7: Camel Cards ---

Did you bring the parts?

@imveikka
"""

import numpy as np
from sys import argv

table = {
    'A': 12,
    'K': 11,
    'Q': 10,
    'J': 9,
    'T': 8,
    '9': 7,
    '8': 6,
    '7': 5,
    '6': 4,
    '5': 3,
    '4': 2,
    '3': 1,
    '2': 0
    }

pairs = np.loadtxt(argv[1], dtype=str)

def calculate(pair):
    hand, _ = pair
    cards = [table[x] for x in hand]
    print
    _, counts = np.unique(cards, return_counts=True)
    return sorted(counts, reverse=True), cards

order = sorted(pairs, key=lambda pair: calculate(pair))

silver = 0
for i, pair in enumerate(order):
    silver += (i+1) * int(pair[1])

print(silver)
