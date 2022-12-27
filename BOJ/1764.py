def solution():
    n, m = map(int, input().split())

    see = set()
    listen = set()
    for i in range(n):
        see.add(input())
    for i in range(m):
        listen.add(input())
    ans = sorted(list(see & listen))
    print(len(ans))
    for name in ans:
    	print(name)
solution()