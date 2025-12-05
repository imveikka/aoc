def read_input(path):
    with open(path, "r") as f:
        top, bot = f.read().split("\n\n")
    ranges = []
    for r in top.splitlines():
        a, b = map(int, r.split("-"))
        ranges.append(range(a, b+1))
    ids = list(map(int, bot.splitlines()))
    return ranges, ids


def silver(path):
    ranges, ids = read_input(path)
    out = 0
    for id in ids:
        for r in ranges:
            if id in r:
                out += 1
                break
    return out


def gold(path):
    ranges, _ = read_input(path)
    to_be_merged = []
    for range_raw in sorted(ranges, key=lambda x: x.start):
        for merge_set in to_be_merged:
            for range_merged in merge_set:
                if range_raw.start in range_merged or range_raw.stop in range_merged:
                    merge_set.append(range_raw)
                    break
            else:
                continue
            break
        else:
            to_be_merged.append([range_raw])
    out = 0
    for merge_set in to_be_merged:
        new_range = range(
            min(merge_set, key=lambda x: x.start).start,
            max(merge_set, key=lambda x: x.stop).stop
        )
        out += len(new_range)
    return out


if __name__ == "__main__":
    print(silver("./input.txt"))
    print(gold("./input.txt"))
