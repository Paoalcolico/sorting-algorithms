#pragma once

#include <algorithm>
#include <vector>

inline void UP(int& a, int& b) {
    int temp = a;
    a += b + 1;
    b = temp;
}

inline void DOWN(int& a, int& b) {
    int temp = b;
    b = a - b - 1;
    a = temp;
}

template <typename T>
std::vector<T> smooth_sorting(std::vector<T> A) {
    const int N = A.size();
    int q = 1, r = 0, p = 1, b = 1, c = 1;

    auto Sift = [&](int& r1, int b1, int c1) {
        int r0 = r1;
        T t = A[r0];
        while (b1 >= 3) {
            int r2 = r1 - b1 + c1;
            int r3 = r1 - 1;

            if (A[r3] >= A[r2]) {
                r2 = r3;
                DOWN(b1, c1);
            }

            if (A[r2] <= t) break;

            A[r1] = A[r2];
            r1 = r2;
            DOWN(b1, c1);
        }
        if (r1 != r0) A[r1] = t;
    };

    auto Trinkle = [&](int& r1, int p, int b, int c) {
        int r0 = r1, p1 = p, b1 = b, c1 = c;
        T t = A[r0];

        while (p1 > 0) {
            while ((p1 & 1) == 0) {
                p1 >>= 1;
                UP(b1, c1);
            }

            int r3 = r1 - b1;
            if (p1 == 1 || A[r3] <= t) break;

            --p1;
            if (b1 == 1) {
                A[r1] = A[r3];
                r1 = r3;
            } else {
                int r2 = r1 - b1 + c1;
                int r4 = r1 - 1;

                if (A[r4] >= A[r2]) {
                    r2 = r4;
                    DOWN(b1, c1);
                    p1 <<= 1;
                }

                if (A[r2] <= A[r3]) {
                    A[r1] = A[r3];
                    r1 = r3;
                } else {
                    A[r1] = A[r2];
                    r1 = r2;
                    DOWN(b1, c1);
                    break;
                }
            }
        }

        if (r1 != r0) A[r1] = t;
        Sift(r1, b1, c1);
    };

    auto SemiTrinkle = [&](int& r, int& r1, int c) {
        r1 = r - c;
        if (A[r1] > A[r]) {
            std::swap(A[r], A[r1]);
            Trinkle(r1, p, b, c);
        }
    };

    int r1, b1, c1;

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
        } else {
            --p;
            r -= b - c;
            if (p > 0) SemiTrinkle(r, r1, c);

            DOWN(b, c);
            p = (p << 1) + 1;
            r += c;
            SemiTrinkle(r, r1, c);

            DOWN(b, c);
            p = (p << 1) + 1;
        }
    }

    return A;
}
