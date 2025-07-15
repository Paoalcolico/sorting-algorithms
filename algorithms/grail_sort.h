#pragma once

#include <algorithm>
#include <csignal>
#include <cstring>
#include <functional>

template <typename T>
void swap_n(T* a, T* b, int n) {
    std::swap_ranges(a, a + n, b);
}

template <typename T>
void rotate(T* a, int l1, int l2) {
    if (l1 == 0 || l2 == 0) return;
    if (l1 + l2 < 32) {
        std::rotate(a, a + l1, a + l1 + l2);
        return;
    }
    std::reverse(a, a + l1);
    std::reverse(a + l1, a + l1 + l2);
    std::reverse(a, a + l1 + l2);
}

template <typename T, typename Compare = std::less<T>>
int binary_search_left(const T* arr, int len, const T* key, Compare cmp = Compare()) {
    int a = -1, b = len;
    while (a < b - 1) {
        int c = a + ((b - a) >> 1);
        if (!cmp(arr[c], *key))
            b = c;
        else
            a = c;
    }
    return b;
}

template <typename T, typename Compare = std::less<T>>
int binary_search_right(const T* arr, int len, const T* key, Compare cmp = Compare()) {
    int a = -1, b = len;
    while (a < b - 1) {
        int c = a + ((b - a) >> 1);
        if (cmp(*key, arr[c]))
            b = c;
        else
            a = c;
    }
    return b;
}

template <typename T, typename Compare = std::less<T>>
int find_keys(T* arr, int len, int nkeys, Compare cmp = Compare()) {
    int h = 1, h0 = 0;
    int u = 1, r;
    while (u < len && h < nkeys) {
        r = binary_search_left(arr + h0, h, arr + u);
        if (r == h || !(!cmp(arr[u], arr[h0 + r]) && !cmp(arr[h0 + r], arr[u]))) {
            rotate(arr + h0, h, u - (h0 + h));
            h0 = u - h;
            rotate(arr + (h0 + r), h - r, 1);
            h++;
        }
        u++;
    }
    rotate(arr, h0, h);
    return h;
}

template <typename T, typename Compare = std::less<T>>
void merge_without_buffer(T* arr, int len1, int len2, Compare cmp = Compare()) {
    int h;
    if (len1 < len2) {
        while (len1) {
            h = binary_search_left(arr + len1, len2, arr);
            if (h != 0) {
                rotate(arr, len1, h);
                arr += h;
                len2 -= h;
            }
            if (len2 == 0) break;
            do {
                arr++;
                len1--;
            } while (len1 && !cmp(*(arr + len1), *arr));
        }
    } else {
        while (len2) {
            h = binary_search_right(arr, len1, arr + (len1 + len2 - 1));
            if (h != len1) {
                rotate(arr + h, len1 - h, len2);
                len1 = h;
            }
            if (len1 == 0) break;
            do {
                len2--;
            } while (len2 && !cmp(*(arr + len1 + len2 - 1), *(arr + len1 - 1)));
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void merge_left(T* arr, int L1, int L2, int M, Compare cmp = Compare()) {
    int p0 = 0, p1 = L1;
    L2 += L1;
    while (p1 < L2) {
        if (p0 == L1 || cmp(*(arr + p1), *(arr + p0))) {
            std::swap(arr[M++], arr[p1++]);
        } else {
            std::swap(arr[M++], arr[p0++]);
        }
    }
    if (M != p0) swap_n(arr + M, arr + p0, L1 - p0);
}

template <typename T, typename Compare = std::less<T>>
void merge_right(T* arr, int L1, int L2, int M, Compare cmp = Compare()) {
    int p0 = L1 + L2 + M - 1, p2 = L1 + L2 - 1, p1 = L1 - 1;

    while (p1 >= 0) {
        if (p2 < L1 || cmp(*(arr + p2), *(arr + p1))) {
            std::swap(arr[p0--], arr[p1--]);
        } else {
            std::swap(arr[p0--], arr[p2--]);
        }
    }
    if (p2 != p0)
        while (p2 >= L1) std::swap(arr[p0--], arr[p2--]);
}

template <typename T, typename Compare = std::less<T>>
void smart_merge_with_buffer(
    T* arr,
    int* alen1,
    int* atype,
    int len2,
    int lkeys,
    Compare cmp = Compare()
) {
    int p0 = -lkeys, p1 = 0, p2 = *alen1, q1 = p2, q2 = p2 + len2;
    int ftype = 1 - *atype;  // 1 if inverted
    while (p1 < q1 && p2 < q2) {
        if (cmp(*(arr + p1), *(arr + p2)) && ftype > 0)
            std::swap(arr[p0++], arr[p1++]);
        else
            std::swap(arr[p0++], arr[p2++]);
    }
    if (p1 < q1) {
        *alen1 = q1 - p1;
        while (p1 < q1) std::swap(arr[--q1], arr[--q2]);
    } else {
        *alen1 = q2 - p2;
        *atype = ftype;
    }
}

template <typename T, typename Compare = std::less<T>>
void smart_merge_without_buffer(
    T* arr,
    int* alen1,
    int* atype,
    int _len2,
    Compare cmp = Compare()
) {
    int len1, len2, ftype, h;

    if (!_len2) return;
    len1 = *alen1;
    len2 = _len2;
    ftype = 1 - *atype;
    if (len1 && (!cmp(*(arr + len1), *(arr + (len1 - 1))) || ftype <= 0)) {
        while (len1) {
            h = ftype ? binary_search_left(arr + len1, len2, arr)
                      : binary_search_right(arr + len1, len2, arr);
            if (h != 0) {
                rotate(arr, len1, h);
                arr += h;
                len2 -= h;
            }
            if (len2 == 0) {
                *alen1 = len1;
                return;
            }
            do {
                arr++;
                len1--;
            } while (len1 && (cmp(*(arr + len1), *arr) && ftype > 0));
        }
    }
    *alen1 = len2;
    *atype = ftype;
}

template <typename T, typename Compare = std::less<T>>
void merge_left_with_x_buf(T* arr, int L1, int L2, int M, Compare cmp = Compare()) {
    int p0 = 0, p1 = L1;
    L2 += L1;
    while (p1 < L2) {
        if (p0 == L1 || cmp(*(arr + p1), *(arr + p0)))
            arr[M++] = arr[p1++];
        else
            arr[M++] = arr[p0++];
    }
    if (M != p0)
        while (p0 < L1) arr[M++] = arr[p0++];
}

template <typename T, typename Compare = std::less<T>>
void smart_merge_with_x_buf(
    T* arr,
    int* alen1,
    int* atype,
    int len2,
    int lkeys,
    Compare cmp = Compare()
) {
    int p0 = -lkeys, p1 = 0, p2 = *alen1, q1 = p2, q2 = p2 + len2;
    int ftype = 1 - *atype;  // 1 if inverted
    while (p1 < q1 && p2 < q2) {
        if (cmp(*(arr + p2), *(arr + p1)) && ftype > 0)
            arr[p0++] = arr[p1++];
        else
            arr[p0++] = arr[p2++];
    }
    if (p1 < q1) {
        *alen1 = q1 - p1;
        while (p1 < q1) arr[--q2] = arr[--q1];
    } else {
        *alen1 = q2 - p2;
        *atype = ftype;
    }
}

template <typename T, typename Compare = std::less<T>>
void merge_buffers_left_with_x_buf(
    T* keys,
    T* midkey,
    T* arr,
    int nblock,
    int lblock,
    int nblock2,
    int llast,
    Compare cmp = Compare()
) {
    int l, prest, lrest, frest, pidx, cidx, fnext;

    if (nblock == 0) {
        l = nblock2 * lblock;
        merge_left_with_x_buf(arr, l, llast, -lblock);
        return;
    }

    lrest = lblock;
    frest = cmp(*keys, *midkey) ? 0 : 1;
    pidx = lblock;
    for (cidx = 1; cidx < nblock; cidx++, pidx += lblock) {
        prest = pidx - lrest;
        fnext = cmp(*(keys + cidx), *midkey) ? 0 : 1;
        if (fnext == frest) {
            memcpy(arr + prest - lblock, arr + prest, lrest * sizeof(T));
            prest = pidx;
            lrest = lblock;
        } else {
            smart_merge_with_x_buf(arr + prest, &lrest, &frest, lblock, lblock);
        }
    }
    prest = pidx - lrest;
    if (llast) {
        if (frest) {
            memcpy(arr + prest - lblock, arr + prest, lrest * sizeof(T));
            prest = pidx;
            lrest = lblock * nblock2;
            frest = 0;
        } else {
            lrest += lblock * nblock2;
        }
        merge_left_with_x_buf(arr + prest, lrest, llast, -lblock);
    } else {
        memcpy(arr + prest - lblock, arr + prest, lrest * sizeof(T));
    }
}

template <typename T, typename Compare = std::less<T>>
void build_blocks(T* arr, int L, int K, T* extbuf, int LExtBuf, Compare cmp = Compare()) {
    int m, u, h, p0, p1, rest, restk, p, kbuf;
    kbuf = K < LExtBuf ? K : LExtBuf;
    while (kbuf & (kbuf - 1)) kbuf &= kbuf - 1;  // max power or 2 - just in case

    if (kbuf) {
        memcpy(extbuf, arr - kbuf, kbuf * sizeof(T));
        for (m = 1; m < L; m += 2) {
            u = 0;
            if (cmp(*(arr + m), *(arr + (m - 1)))) u = 1;
            arr[m - 3] = arr[m - 1 + u];
            arr[m - 2] = arr[m - u];
        }
        if (L % 2) arr[L - 3] = arr[L - 1];
        arr -= 2;
        for (h = 2; h < kbuf; h *= 2) {
            p0 = 0;
            p1 = L - 2 * h;
            while (p0 <= p1) {
                merge_left_with_x_buf(arr + p0, h, h, -h);
                p0 += 2 * h;
            }
            rest = L - p0;
            if (rest > h) {
                merge_left_with_x_buf(arr + p0, h, rest - h, -h);
            } else {
                for (; p0 < L; p0++) arr[p0 - h] = arr[p0];
            }
            arr -= h;
        }
        memcpy(arr + L, extbuf, kbuf * sizeof(T));
    } else {
        for (m = 1; m < L; m += 2) {
            u = 0;
            if (cmp(*(arr + m), *(arr + (m - 1)))) u = 1;
            std::swap(arr[m - 3], arr[m - 1 + u]);
            std::swap(arr[m - 2], arr[m - u]);
        }
        if (L % 2) std::swap(arr[L - 1], arr[L - 3]);
        arr -= 2;
        h = 2;
    }
    for (; h < K; h *= 2) {
        p0 = 0;
        p1 = L - 2 * h;
        while (p0 <= p1) {
            merge_left(arr + p0, h, h, -h);
            p0 += 2 * h;
        }
        rest = L - p0;
        if (rest > h) {
            merge_left(arr + p0, h, rest - h, -h);
        } else
            rotate(arr + p0 - h, h, rest);
        arr -= h;
    }
    restk = L % (2 * K);
    p = L - restk;
    if (restk <= K)
        rotate(arr + p, restk, K);
    else
        merge_right(arr + p, K, restk - K, K);
    while (p > 0) {
        p -= 2 * K;
        merge_right(arr + p, K, K, K);
    }
}

template <typename T, typename Compare = std::less<T>>
void merge_buffers_left(
    T* keys,
    T* midkey,
    T* arr,
    int nblock,
    int lblock,
    bool havebuf,
    int nblock2,
    int llast,
    Compare cmp = Compare()
) {
    int l, prest, lrest, frest, pidx, cidx, fnext;

    if (nblock == 0) {
        l = nblock2 * lblock;
        if (havebuf)
            merge_left(arr, l, llast, -lblock);
        else
            merge_without_buffer(arr, l, llast);
        return;
    }

    lrest = lblock;
    frest = cmp(*keys, *midkey) ? 0 : 1;
    pidx = lblock;
    for (cidx = 1; cidx < nblock; cidx++, pidx += lblock) {
        prest = pidx - lrest;
        fnext = cmp(*(keys + cidx), *midkey) ? 0 : 1;
        if (fnext == frest) {
            if (havebuf) swap_n(arr + prest - lblock, arr + prest, lrest);
            prest = pidx;
            lrest = lblock;
        } else {
            if (havebuf) {
                smart_merge_with_buffer(arr + prest, &lrest, &frest, lblock, lblock);
            } else {
                smart_merge_without_buffer(arr + prest, &lrest, &frest, lblock);
            }
        }
    }
    prest = pidx - lrest;
    if (llast) {
        if (frest) {
            if (havebuf) swap_n(arr + prest - lblock, arr + prest, lrest);
            prest = pidx;
            lrest = lblock * nblock2;
            frest = 0;
        } else {
            lrest += lblock * nblock2;
        }
        if (havebuf)
            merge_left(arr + prest, lrest, llast, -lblock);
        else
            merge_without_buffer(arr + prest, lrest, llast);
    } else {
        if (havebuf) swap_n(arr + prest, arr + (prest - lblock), lrest);
    }
}

template <typename T, typename Compare = std::less<T>>
void insertion_sort(T* arr, int len, Compare cmp = Compare()) {
    for (int i = 1; i < len; i++) {
        T key = arr[i];
        int left = 0, right = i;
        while (left < right) {
            int mid = (left + right) / 2;
            if (cmp(key, arr[mid])) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        for (int k = i; k > left; k--) {
            arr[k] = arr[k - 1];
        }
        arr[left] = key;
    }
}

template <typename T, typename Compare = std::less<T>>
void lazy_stable_sort(T* arr, int L, Compare cmp = Compare()) {
    for (int m = 1; m < L; m += 2) {
        if (cmp(arr[m], arr[m - 1])) {
            std::swap(arr[m - 1], arr[m]);
        }
    }
    for (int h = 2; h < L; h *= 2) {
        for (int p0 = 0; p0 <= L - 2 * h; p0 += 2 * h) {
            merge_without_buffer(arr + p0, h, h, cmp);
        }

        int rest = L - (L / (2 * h)) * (2 * h);
        if (rest > h) {
            merge_without_buffer(arr + L - rest, h, rest - h, cmp);
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void combine_blocks(
    T* keys,
    T* arr,
    int len,
    int LL,
    int lblock,
    bool havebuf,
    T* xbuf,
    Compare cmp = Compare()
) {
    int M, b, NBlk, midkey, lrest, u, p, v, kc, nbl2, llast;
    T* arr1;

    M = len / (2 * LL);
    lrest = len % (2 * LL);
    if (lrest <= LL) {
        len -= lrest;
        lrest = 0;
    }
    if (xbuf) memcpy(xbuf, arr - lblock, lblock * sizeof(T));
    for (b = 0; b <= M; b++) {
        if (b == M && lrest == 0) break;
        arr1 = arr + b * 2 * LL;
        NBlk = (b == M ? lrest : 2 * LL) / lblock;
        insertion_sort(keys, NBlk + (b == M ? 1 : 0));
        midkey = LL / lblock;
        for (u = 1; u < NBlk; u++) {
            p = u - 1;
            for (v = u; v < NBlk; v++) {
                kc = cmp(*(arr1 + v * lblock), *(arr1 + p * lblock))
                         ? 1
                         : (cmp(*(arr1 + p * lblock), *(arr1 + v * lblock)) ? -1 : 0);
                if (kc > 0 || (kc == 0 && cmp(*(keys + v), *(keys + p)))) p = v;
            }
            if (p != u - 1) {
                swap_n(arr1 + (u - 1) * lblock, arr1 + p * lblock, lblock);
                std::swap(keys[u - 1], keys[p]);
                if (midkey == u - 1 || midkey == p) midkey ^= (u - 1) ^ p;
            }
        }
        nbl2 = llast = 0;
        if (b == M) llast = lrest % lblock;
        if (llast != 0) {
            while (nbl2 < NBlk && cmp(*(arr1 + NBlk * lblock), *(arr1 + (NBlk - nbl2 - 1) * lblock))
            )
                nbl2++;
        }
        if (xbuf)
            merge_buffers_left_with_x_buf(
                keys,
                keys + midkey,
                arr1,
                NBlk - nbl2,
                lblock,
                nbl2,
                llast
            );
        else
            merge_buffers_left(
                keys,
                keys + midkey,
                arr1,
                NBlk - nbl2,
                lblock,
                havebuf,
                nbl2,
                llast
            );
    }
    if (xbuf) {
        for (p = len; --p >= 0;) arr[p] = arr[p - lblock];
        memcpy(arr - lblock, xbuf, lblock * sizeof(T));
    } else if (havebuf)
        while (--len >= 0) std::swap(arr[len], arr[len - lblock]);
}

template <typename T, typename Compare = std::less<T>>
void common_sort(T* arr, int Len, T* extbuf, int LExtBuf) {
    int lblock, nkeys, findkeys, ptr, cbuf, lb, nk;
    bool havebuf, chavebuf;
    long long s;

    if (Len < 16) {
        insertion_sort(arr, Len);
        return;
    }

    lblock = 1;
    while (lblock * lblock < Len) lblock *= 2;
    nkeys = (Len - 1) / lblock + 1;
    findkeys = find_keys(arr, Len, nkeys + lblock);
    havebuf = true;
    if (findkeys < nkeys + lblock) {
        if (findkeys < 4) {
            lazy_stable_sort(arr, Len);
            return;
        }
        nkeys = lblock;
        while (nkeys > findkeys) nkeys /= 2;
        havebuf = false;
        lblock = 0;
    }
    ptr = lblock + nkeys;
    cbuf = havebuf ? lblock : nkeys;
    if (havebuf)
        build_blocks(arr + ptr, Len - ptr, cbuf, extbuf, LExtBuf);
    else
        build_blocks(arr + ptr, Len - ptr, cbuf, static_cast<T*>(nullptr), 0);

    while (Len - ptr > (cbuf *= 2)) {
        lb = lblock;
        chavebuf = havebuf;
        if (!havebuf) {
            if (nkeys > 4 && nkeys / 8 * nkeys >= cbuf) {
                lb = nkeys / 2;
                chavebuf = true;
            } else {
                nk = 1;
                s = (long long)cbuf * findkeys / 2;
                while (nk < nkeys && s != 0) {
                    nk *= 2;
                    s /= 8;
                }
                lb = (2 * cbuf) / nk;
            }
        } else {
#if 0
			if(LExtBuf!=0){
				while(lb>LExtBuf && lb*lb>2*cbuf) lb/=2;
			}
#endif
        }
        combine_blocks(
            arr,
            arr + ptr,
            Len - ptr,
            cbuf,
            lb,
            chavebuf,
            chavebuf && lb <= LExtBuf ? extbuf : NULL
        );
    }
    insertion_sort(arr, ptr);
    merge_without_buffer(arr, ptr, Len - ptr);
}
