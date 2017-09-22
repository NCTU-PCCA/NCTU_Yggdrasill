bigM = int(1e9+7)
fac = [1]*10001
for i in range(1, 10001):
	fac[i] = fac[i-1]*i
ifac = [pow(fac[i], bigM-2, bigM) for i in range(10001)]
def f(a, b, M):
	if b == 0 or b == a:
		return 1
	elif a < b:
		return 0
	elif a < M:
		return fac[a]*ifac[b]*ifac[a-b]%bigM
	else:
		return f(a//M, b//M, M) * f(a%M, b%M, M) % bigM
t = int(input())
for cases in range(t):
	a, b, M = [int(x) for x in input().split()]
	print(f(a, b, M))