#include <bits/stdc++.h>
using namespace std;
#define ll long long

/* create SG class (Segment tree class) use this class to make objects and apply segmentree on different
 segments ;
 you need to modify the build function , update function and query functions according to the 
 quetion needs.

 problem rating on this topic 1900 - 2900
  */
class SG {
    vector<ll> seg, lazy;

    void apply(int ind, int low, int high, ll value) {
        seg[ind] += (high - low + 1) * value;
        if (low != high) {
            lazy[2 * ind + 1] += value;
            lazy[2 * ind + 2] += value;
        }
    }

    void propagate(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            apply(ind, low, high, lazy[ind]);
            lazy[ind] = 0;
        }
    }

public:
    SG(int n) {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1, 0);
    }

    void build(int ind, int low, int high, vector<ll> &v) {
        if (low == high) {
            seg[ind] = v[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, v);
        build(2 * ind + 2, mid + 1, high, v);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void update(int ind, int low, int high, int l, int r, int val) {
        propagate(ind, low, high);
        if (high < l || low > r) return;

        if (low >= l && high <= r) {
            apply(ind, low, high, val);
            return;
        }
        int mid = (low + high) / 2;
        update(2 * ind + 1, low, mid, l, r, val);
        update(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    ll query(int ind, int low, int high, int l, int r) {
        propagate(ind, low, high);
        if (high < l || low > r) return 0;

        if (low >= l && high <= r) return seg[ind];

        int mid = (low + high) / 2;
        return query(2 * ind + 1, low, mid, l, r) + query(2 * ind + 2, mid + 1, high, l, r);
    }

    void print() {
        for (ll i : seg) cout << i << " ";
        cout << endl;
    }
};