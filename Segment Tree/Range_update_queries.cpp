#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SGTree
{
    vector<int> seg, lazy;

public:
    SGTree() {}
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }
public: 
    void build(int ind , int low , int high , vector<int> v){
        if(low == high){
            seg[ind] = v[low];
            return;
        }

        int mid = (high+low)>>1;
        build(2*ind+1 , low , mid , v);
        build(2*ind+2 , mid+1 , high , v);
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];  
    }
public:
    void update(int ind , int low , int high , int l , int r , int val){
        //update the all previous remaining updates in lazy array
        // and propogate downwords
        if(lazy[ind] != 0){
            seg[ind] += (high-low+1)*lazy[ind];
            //Propogate the lazy update downwords
            // for the remaining nodes to get update
            if(low != high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            //after all work of the current index node is done set it to 0
            lazy[ind] = 0;
        }
        //no overlap, we don't do anythig and we return 
        if(high < l || r < low) return;

        // complete overlap
        if(low >= l && high <= r){
            seg[ind] += (high-low+1)*val;
            if(low != high){
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            }
            return;
        }

        // partial overlap;
        int mid = (high+low)>>1;
        update(2*ind+1 , low , mid , l , r , val);
        update(2*ind+2 , mid+1 , high , l , r , val);
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
    }
public:
    int query(int ind , int low , int high , int l , int r){
        //update the all previous remaining updates in lazy array
        // and propogate downwords
        if(lazy[ind] != 0){
            seg[ind] += (high-low+1)*lazy[ind];
            //Propogate the lazy update downwords
            // for the remaining nodes to get update
            if(low != high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            //after all work of the current index node is done set it to 0
            lazy[ind] = 0;
        }

        // no overlap return 0;
        if(high < l ||r < low) return 0;

        // Complete overlap
        if(low >= l && high <= r) return seg[ind];

        // partial overlap
        int mid = (high+low)>>1;
        int left = query(2*ind+1 , low , mid , l , r);
        int right = query(2*ind+2 , mid+1 , high , l , r);
        return left+right;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n; 
    vector<int> v(n);
    for(int &i : v) cin >> i;
    SGTree st(n);
    st.build(0 , 0 , n-1 , v);
    
    int q; cin >> q;
    while(q--){
        int t; cin >> t;
        if(t == 1){
            int l , r; cin >> l >> r;
            cout << st.query(0 , 0 , n-1 , l , r);
            cout << endl;
        }
        else{
            int l , r ,val;
            cin >> l >> r >> val;
            st.update(0 ,0 , n-1 , l, r , val);
        }
    }
    return 0;
}