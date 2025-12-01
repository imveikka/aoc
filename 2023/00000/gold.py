"""
--- Part Two ---

It's a feature, not a bug.
"""

from re import sub

if __name__ == "__main__":

    with open('./bigboy', 'r') as buf:
        lines = buf.read().splitlines()

    numbers = (('one', 'o1e'), ('two', 't2o'), ('three', 't3e'),
               ('four', '4'), ('five', '5e'), ('six', '6'),
               ('seven', '7n'), ('eight', 'e8t'), ('nine', 'n9e'))
    
    for a, b in numbers:
        lines = list(map(lambda line: line.replace(a, b), lines))

    no_chars = map(lambda line: sub('[a-z]', '', line), lines)
    numbers = map(lambda line: str(line[0] * 2 if len(line) == 1 else line[0] + line[-1]), no_chars)
    result = sum(map(lambda line: int(line), numbers))
    print(result)

