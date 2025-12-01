"""
--- Day 1: Trebuchet?! ---

It's the most wonderful time of the year!

Never look down on regex.
"""

from re import sub

if __name__ == "__main__":
    with open('./bigboy', 'r') as buf:
        lines = buf.read().splitlines()
    no_chars = map(lambda line: sub('[a-z]', '', line), lines)
    numbers = map(lambda line: str(line[0] * 2 if len(line) == 1 else line[0] + line[-1]), no_chars)
    result = sum(map(lambda line: int(line), numbers))
    print(result)

