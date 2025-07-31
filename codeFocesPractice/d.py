import math
n, m = map(int, input().split(" "))


group = math.ceil(n/m)

a = list(map(int, input().split(" ")))

ans = sum(a[:group])

for i in range(group, n, group):
    ans = max(ans, sum(a[i:i+group]))

print(ans)