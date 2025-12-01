"""
--- Part Two ---

Valtti moment.

@veikka
"""

import numpy as np
from sys import argv

table = {
    'A': 13,
    'K': 12,
    'Q': 11,
    'T': 10,
    '9': 9,
    '8': 8,
    '7': 7,
    '6': 6,
    '5': 5,
    '4': 4,
    '3': 3,
    '2': 2,
    'J': 1
    }

pairs = np.loadtxt(argv[1], dtype=str)

def calculate(pair):
    hand, _ = pair
    cards = [table[x] for x in hand]
    vals, counts = np.unique(cards, return_counts=True)

    valtti = vals == 1
    n_valttis = counts[valtti]
    vals, counts = vals[~valtti], counts[~valtti]

    if vals.any():
        counts[np.argmax(counts)] += np.sum(n_valttis)
    else:
        counts = [5]

    return sorted(counts, reverse=True), cards

order = sorted(pairs, key=lambda pair: calculate(pair))

gold = 0
for i, pair in enumerate(order):
    gold += (i+1) * int(pair[1])

print(gold)
