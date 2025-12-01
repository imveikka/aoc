"""
--- Part Two ---

I don't wanna hear that this is too slow or something
along those lines. I can optimize this, I'm just too lazy.

@imveikka

Update: Well, the bigboy takes too long.
I'll optimize this in syssymmällä.
"""

import numpy as np
from scipy.spatial import distance_matrix

with open('./input', 'r') as buf:
    schematic = np.array([list(line) for line in buf.read().splitlines()])

digits = np.char.isdigit(schematic)
symbols = schematic == '*'

digits_coords = np.vstack(np.where(digits)).T
symbols_coords = np.vstack(np.where(symbols)).T

schematic[~digits] = '.'

digit_coord_pairs, sep = [], 0
for row in schematic:
    line = ''.join(row)
    for digit in filter(str.isdigit, line.split('.')):
        coords = digits_coords[sep: sep+len(digit)]
        sep += len(digit)
        digit_coord_pairs.append((int(digit), coords))

result = 0
for sym_coord in symbols_coords:
    part_numbers, ratio = 0, 1
    for dig, dig_coord in digit_coord_pairs:
        if np.any(distance_matrix([sym_coord], dig_coord) < 1.5):
            part_numbers += 1
            ratio *= dig
        if part_numbers > 2:
            break
    if part_numbers == 2:
        result += ratio

print(result)

