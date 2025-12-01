"""
--- Day 4: Scratchcards ---

Silver and gold puzzle at the same file?

@imveikka
"""


import numpy as np

buf = np.loadtxt('./input', delimiter='|', dtype=str)

copies = {i: 1 for i in range(buf.shape[0])}
silver = 0

for i, game in enumerate(buf):
    card = np.fromstring(game[0].split(': ')[1], dtype=int, sep=' ')
    hand = np.fromstring(game[1], dtype=int, sep=' ')
    n = np.intersect1d(card, hand).shape[0]
    if n > 0:
        silver += 2**(n-1)
        for j in range(i + 1, i + 1 + n):            
            copies[j] += copies[i]

gold = sum(copies.values())

print(f'{silver = }')
print(f'{gold = }')

    
