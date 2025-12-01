"""
--- Day 6: Wait For It ---

Didn't have to wait much for this one.

@imveikka
"""

import numpy as np
from sys import argv

with open(argv[1], 'r') as f:
    buf = f.read().splitlines()

digits_silver = map(lambda x: x.split(':')[1].strip(), buf)
digits_gold = map(lambda x: x.split(':')[1].replace(' ', ''), buf)

for label, mapping in zip(('silver', 'gold'), (digits_silver, digits_gold)):
    time, distance = [np.fromstring(row, sep=' ') for row in mapping]
    res = 1
    for max_time, record in zip(time, distance):
        press_times = np.arange(1, max_time)
        scores = press_times * (max_time - press_times)
        res *= np.sum(scores > record)
    print(label, res)

