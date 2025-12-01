"""
--- Day 2: Cube Conundrum ---

Sorry guys I'm late
(that's my secret)

@imveikka
"""

import numpy as np

buffer = np.loadtxt('./bigboy', delimiter=':', dtype=str)

def is_it_possible(sets, colors=np.array([12, 13, 14])):
    table = {'red': 0, 'green': 0, 'blue': 0}
    sets = sets.split(';')
    for cubes in sets:
        reveals = cubes.split(',')
        for reveal in reveals:
            number, color = reveal[1:].split()
            table[color] = max(int(number), table[color])
    return np.all(np.array(list(table.values())) <= colors)

games = np.arange(len(buffer)) # + 1 # add if not bigboy

foo = list(map(is_it_possible, buffer[:, 1]))

print(np.sum(games[foo]))

