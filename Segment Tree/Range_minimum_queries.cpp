#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SGTree
{
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, vector<int> v)
    {
        if (low == high)
        {
            seg[ind] = v[low];
            return;
        }
        int mid = (high + low) >> 1;
        build(2 * ind + 1, low, mid, v);
        build(2 * ind + 2, mid + 1, high, v);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
// this query is for finding minimum in the range , we can modify our queries or can make out own 
    int query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        //[l , r] < [low , high] || [low , high] < [l , r]
        if (r < low || high < l)
            return INT_MAX;

        // complete overlap
        //[l , [low , high] , r]
        if (low >= l && high <= r)
            return seg[ind];
        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return min(left, right);
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }

        int mid = (low + high) >> 1;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};
void
sol()
{
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (int &i : v)
        cin >> i;
    // int seg[n * 4];
    // build(0, 0, n - 1, v, seg);
    // update(0, 0, n - 1, 4, 0, seg);
    SGTree sg(n);
    sg.build(0 , 0 , n-1 , v);
    sg.update(0 , 0 , n-1 , 4 , 0);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << sg.query(0, 0, n - 1, l, r);
        cout << endl;
    }
}

int main()
{
    sol();
    return 0;
}