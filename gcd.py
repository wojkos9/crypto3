from itertools import zip_longest
from fractions import Fraction as F


class P(list):
    def __init__(self, *args, t=F):
        a = args[0] if hasattr(args[0], '__iter__') else args
        super().__init__([t(x) for x in a])

    def lstrip(s):
        return type(s)(s[next((i for i in range(len(s)) if s[i]), -1):])

    def rpad(s, n):
        return type(s)(s[:] + [0] * max((n - len(s)), 0))

    def __mul__(s, b):
        p, q = len(s), len(b)
        r = [0] * (p+q-1)
        for i in range(p):
            for j in range(q):
                r[i+j] += s[i] * b[j]
        return type(s)(r)

    def __add__(s, b):
        r = type(s)([x+y for (x, y) in zip_longest(s[::-1], b[::-1], fillvalue=0)][::-1])
        return r.lstrip()

    def __sub__(s, b):
        r = type(s)([x-y for (x, y) in zip_longest(s[::-1], b[::-1], fillvalue=0)][::-1])
        return r.lstrip()

    def __str__(s):
        if s == [0]:
            return "0"

        def r(f: F):
            return f.numerator if f.denominator == 1 else f'{f.numerator}/{f.denominator}'
        return " + ".join(
            f'{r(c) if c != 1 or e == 0 else ""}{"x" if e else ""}{f"^{e}" if e > 1 else ""}'
            for c, e in zip(s, reversed(range(len(s)))) if c)

class B(int):
    def __new__(cls, x):
        return super(B, cls).__new__(cls, x & 1)

B.__add__ = B.__sub__ = int.__xor__
B.__mul__ = B.__truediv__ = int.__and__
B.__bool__ = lambda s: bool(s & 1)

class P2(P):
    def __init__(self, *args):
        super().__init__(*args, t=B)

def pdiv(a, b):
    T = type(a)
    m, n = len(a), len(b)
    if n == 1:
        return T([c/b[0] for c in a]), T(0)
    c = []
    while m - n >= 0:
        k = a[0] / b[0]
        c.append(k)
        a = a - (b * T(k)).rpad(m)
        m, n = len(a), len(b)
    return c, a


def gcd(a, b):
    while True:
        _, r = pdiv(a, b)
        if not r[0]:
            return b
        print(r)
        a, b = b, r


a = P(1, 0, 1, 0, -3, -3, 8, 2, -5)
b = P(3, 0, 5, 0, -4, -9, 21)
r = gcd(a, b)
print(r)
