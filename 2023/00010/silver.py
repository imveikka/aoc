"""
--- Day 3: Gear Ratios ---

Come on guys this is only a third day!

@imveikka
"""

import numpy as np
from scipy.spatial import distance_matrix

with open('./bigboy', 'r') as buf:
    schematic = np.array([list(line) for line in buf.read().splitlines()])

digits = np.char.isdigit(schematic)
dots = schematic == '.'
symbols = ~(digits + dots)

digits_coords = np.vstack(np.where(digits)).T
symbols_coords = np.vstack(np.where(symbols)).T

schematic[symbols] = '.'

sep, result = 0, 0
for row in schematic:
    line = ''.join(row)
    for digit in filter(str.isdigit, line.split('.')):
        coords = digits_coords[sep: sep+len(digit)]
        sep += len(digit)
        dists = distance_matrix(coords, symbols_coords)
        if np.any(dists < 1.5):
            result += int(digit) 
    
print(result)


