"""
--- Day 11: Cosmic Expansion ---

Let the comeback begin.

@imveikka
"""

import numpy as np
from sys import argv
from itertools import product

galaxy = np.array([[c for c in f.strip()] for f in open(argv[1], 'r')])

# Silver

rows = np.where((galaxy == '.').all(axis=1))[0]
cols = np.where((galaxy == '.').all(axis=0))[0]

silver_coords = np.array(np.where(galaxy == '#')).T
for i in range(len(silver_coords)):
    y, x = silver_coords[i]
    y += np.sum(rows < y)
    x += np.sum(cols < x)
    silver_coords[i] = [y, x]


silver = 0
for i, (x1, y1) in enumerate(silver_coords):
    for (x2, y2) in silver_coords[i+1:]:
        silver += abs(x1-x2) + abs(y1-y2)

print(f'{silver = }')

# Gold

gold_coords = np.array(np.where(galaxy == '#')).T
for i in range(len(gold_coords)):
    y, x = gold_coords[i]
    y += 999999 * np.sum(rows < y)
    x += 999999 * np.sum(cols < x)
    gold_coords[i] = [y, x]
    
gold = 0
for i, (x1, y1) in enumerate(gold_coords):
    for (x2, y2) in gold_coords[i+1:]:
        gold += abs(x1-x2) + abs(y1-y2)

print(f'{gold = }')
