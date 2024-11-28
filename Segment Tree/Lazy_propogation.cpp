#include <bits/stdc++.h>
using namespace std;
#define ll long long

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

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int cal(int n, int f) {
    while (f--) {
        if (n < 10) break;  // Optimization to stop early if n becomes a single digit
        n = sumOfDigits(n);
    }
    return n;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        int n, q;
        cin >> n >> q;
        vector<ll> v(n);
        for (ll &i : v) cin >> i;
        vector<ll> fre(n, 0LL);

        SG sg(n);
        sg.build(0, 0, n - 1, fre);

        while (q--) {
            int t;
            cin >> t;
            if (t == 1) {
                int a, b;
                cin >> a >> b;
                sg.update(0, 0, n - 1, a - 1, b - 1, 1);
            } else {
                int a;
                cin >> a;
                int f = sg.query(0, 0, n - 1, a - 1, a - 1);
                cout << cal(v[a - 1], f) << endl;
            }
        }
    }
    return 0;
}
