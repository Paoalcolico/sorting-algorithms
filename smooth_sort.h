#pragma once

#include <algorithm>
#include <vector>

template <typename T>
std::vector<T> smooth_sorting(std::vector<T> A) {
    int N = A.size();
    int q = 1, r = 0, p = 1, b = 1, c = 1;
    int r1, b1, c1;

    auto IsAscending = [](const T& a, const T& b) {
        return a <= b;
    };

    auto UP = [](int& IA, int& IB) {
        int temp = IA;
        IA += IB + 1;
        IB = temp;
    };

    auto DOWN = [](int& IA, int& IB) {
        int temp = IB;
        IB = IA - IB - 1;
        IA = temp;
    };

    auto Sift = [&](int& r1, int b1, int c1) {
        int r0 = r1;
        T t = A[r0];
        while (b1 >= 3) {
            int r2 = r1 - b1 + c1;
            if (!IsAscending(A[r1 - 1], A[r2])) {
                r2 = r1 - 1;
                DOWN(b1, c1);
            }
            if (IsAscending(A[r2], t)) {
                b1 = 1;
            } else {
                A[r1] = A[r2];
                r1 = r2;
                DOWN(b1, c1);
            }
        }
        if (r1 != r0) A[r1] = t;
    };

    auto Trinkle = [&](int& r1, int p, int b, int c) {
        int p1 = p, r0 = r1;
        int b1 = b, c1 = c;
        T t = A[r0];
        while (p1 > 0) {
            while ((p1 & 1) == 0) {
                p1 >>= 1;
                UP(b1, c1);
            }
            int r3 = r1 - b1;
            if ((p1 == 1) || IsAscending(A[r3], t)) {
                p1 = 0;
            } else {
                --p1;
                if (b1 == 1) {
                    A[r1] = A[r3];
                    r1 = r3;
                } else if (b1 >= 3) {
                    int r2 = r1 - b1 + c1;
                    if (!IsAscending(A[r1 - 1], A[r2])) {
                        r2 = r1 - 1;
                        DOWN(b1, c1);
                        p1 <<= 1;
                    }
                    if (IsAscending(A[r2], A[r3])) {
                        A[r1] = A[r3];
                        r1 = r3;
                    } else {
                        A[r1] = A[r2];
                        r1 = r2;
                        DOWN(b1, c1);
                        p1 = 0;
                    }
                }
            }
        }
        if (r1 != r0) A[r1] = t;
        Sift(r1, b1, c1);
    };

    auto SemiTrinkle = [&](int& r, int& r1, int c) {
        r1 = r - c;
        if (!IsAscending(A[r1], A[r])) {
            std::swap(A[r], A[r1]);
            Trinkle(r1, p, b, c);
        }
    };

    while (q < N) {
        r1 = r;
        if ((p & 7) == 3) {
            b1 = b;
            c1 = c;
            Sift(r1, b1, c1);
            p = (p + 1) >> 2;
            UP(b, c);
            UP(b, c);
        } else if ((p & 3) == 1) {
            if (q + c < N) {
                b1 = b;
                c1 = c;
                Sift(r1, b1, c1);
            } else {
                Trinkle(r1, p, b, c);
            }
            DOWN(b, c);
            p <<= 1;
            while (b > 1) {
                DOWN(b, c);
                p <<= 1;
            }
            ++p;
        }
        ++q;
        ++r;
    }

    r1 = r;
    Trinkle(r1, p, b, c);

    while (q > 1) {
        --q;
        if (b == 1) {
            --r;
            --p;
            while ((p & 1) == 0) {
                p >>= 1;
                UP(b, c);
            }
        } else if (b >= 3) {
            --p;
            r = r - b + c;
            if (p > 0) SemiTrinkle(r, r1, c);

            DOWN(b, c);
            p = (p << 1) + 1;
            r = r + c;
            SemiTrinkle(r, r1, c);
            DOWN(b, c);
            p = (p << 1) + 1;
        }
    }

    return A;
}
