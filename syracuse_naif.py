def f(n):
    if n % 2 == 1:
        return 3*n + 1
    else:
        return n >> 1

def m_naive(n):
    res = 0
    while n != 1:
        n = f(n)
        res += 1
    return res
