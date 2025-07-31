n = int(input())

for _ in range(n):
    s = input()

    a = []

    for i in s:
        if (a and a[-1] == "A" and i == "B"):
            a.pop()
            continue
        a.append(i)

    if (a.count("B") == 2 and "BB" in "".join(a)):
        print(len(a)-2)
        continue
    
    print(len(a))
