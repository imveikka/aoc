"""
--- Day 10: Pipe Maze ---

Thank you @knuutti.

@imveikka
"""


from sys import argv
import numpy as np
from re import sub

# Silver

directions = ((0, -1), (1, 0), (-1, 0), (0, 1))
expected = {    # < v ^ >
        '|' : [{}, {'L', 'J', '|'}, {'7', 'F', '|'}, {}],
        '-' : [{'F', 'L', '-'}, {}, {}, {'J', '7', '-'}],
        'J' : [{'F', 'L', '-'}, {}, {'7', 'F', '|'}, {}],
        'L' : [{}, {}, {'7', 'F', '|'}, {'J', '7', '-'}],
        '7' : [{'F', 'L', '-'}, {'L', 'J', '|'}, {}, {}],
        'F' : [{}, {'L', 'J', '|'}, {}, {'J', '7', '-'}],
        'S' : [{'F', 'L', '-'}, {'L', 'J', '|'},
               {'7', 'F', '|'}, {'J', '7', '-'}]
        }

tiles = np.array([[c for c in f.strip()] for f in open(argv[1], 'r')])
tiles = np.pad(tiles, 1, constant_values='.')

start = tuple(np.stack(np.where(tiles == 'S')).ravel())
visited = np.zeros(tiles.shape).astype(bool)

dists = np.zeros(tiles.shape).astype(int)
visited[start] = True

queue = [start]
while queue:
    y, x = queue.pop(0)
    expt = expected[tiles[y, x]]
    for pipes, (dy, dx) in zip(expt, directions):
        if tiles[y+dy, x+dx] in pipes and not visited[y+dy, x+dx]:
            queue.append((y+dy, x+dx))
            visited[y+dy, x+dx] = True
            dists[y+dy, x+dx] = dists[y, x] + 1
    
silver = dists.max().astype(int)
print(f'{silver = }')

# Gold

tiles[~visited] = '.'

foo, bar = start
if tiles[foo, bar-1] in '-FL' and tiles[foo, bar+1] in '-J7':
    tiles[start] = '-'
elif tiles[foo, bar-1] in '-FL' and tiles[foo-1, bar] in '|7F':
    tiles[start] = 'J'
elif tiles[foo, bar-1] in '-FL' and tiles[foo+1, bar] in '|JL':
    tiles[start] = '7'
elif tiles[foo+1, bar] in '|JL' and tiles[foo, bar+1] in '-J7':
    tiles[start] = 'F'
elif tiles[foo+1, bar] in '-FL' and tiles[foo-1, bar] in '|7F':
    tiles[start] = '|'
else:
    tiles[start] = 'L'

gold = 0
for row in tiles:
    row = ''.join(map(str, row))
    row = sub('F[-]*J', '|', row)
    row = sub('L[-]*7', '|', row)
    row = sub('F[-]*7', '-', row)
    row = sub('L[-]*J', '-', row)
    row = sub('[-]*', '', row)
    row = row.lstrip('.{}').rstrip('.')

    in_region = False
    for c in row:
        if c == '|':
            in_region = not in_region
        if c == '.' and in_region:
            gold += 1

print(f'{gold = }')
