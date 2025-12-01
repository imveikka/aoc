"""
--- Day 9: Mirage Maintenance ---

Hyvän mielen tehtäviä

@imveikka
"""

from sys import argv
import numpy as np

history = np.loadtxt(argv[1], delimiter=' ', dtype=int)

def diffs(row): 
    while row.any():
        yield row[0], row[-1]
        row = np.diff(row) 

silver = 0
gold = 0

for row in history:
    Dg, Ds = np.array(list(diffs(row))).T
    
    silver += np.add.accumulate(Ds)[-1]

    Ig = 0
    for num in Dg[::-1]:
        Ig = num - Ig
    gold += Ig

print(f'silver: {silver}')
print(f'gold: {gold}')
    
