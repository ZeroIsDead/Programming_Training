n = int(input())

memo = {}

def findPoints(seg, turn=True):
    if seg <= 2:
        return 1
    if turn and seg in memo:
        return memo[seg]

    if seg % 2 == 0:
        half = seg // 2
        res = findPoints(half, not turn) + (half if turn else 0)
    else:
        res = findPoints(seg - 1, not turn) + (1 if turn else 0)

    if turn:
        memo[seg] = res
    return res

for _ in range(n):
    a = int(input())
    if a <= 0:
        print(0)
    else:
        print(findPoints(a))