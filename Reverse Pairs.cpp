int seg[1000006];
void update(int ind, int st, int en, int index) {
    if(st == en) {
        seg[ind]++;
        return;
    }
    int mid = (st + en) >> 1;
    if(index <= mid) {
        update(2 * ind + 1, st, mid, index);
    }
    else {
        update(2 * ind + 2, mid + 1, en, index);
    }
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
} 
int query(int ind, int st, int en, int l, int r) {
    if(en < l || st > r || st > en) {
        return 0;
    }
    if(l <= st && en <= r) {
        return seg[ind];
    }
    int mid = (st + en) >> 1;
    return query(2 * ind + 1, st, mid, l, r) + query(2 * ind + 2, mid + 1, en, l, r);
}
int reversePairs(vector<int>& nums) {
    int n = nums.size();
    set<long long> st(nums.begin(), nums.end());
    int cnt = 0;
    unordered_map<int, int> mp;
    for(int i : st) {
        mp[i] = cnt++;
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        long long rq = nums[i] * 2ll + 1;
        if(st.find(rq) != st.end()) {
            int l = mp[rq], r = n - 1;
            ans += query(0, 0, n - 1, l, r);
        }
        else {
            auto it = st.lower_bound(rq);
            if(it != st.end()) {
                int l = mp[*it], r = n - 1;
                ans += query(0, 0, n - 1, l, r);
            }
        }
        update(0, 0, n - 1, mp[nums[i]]);
    }
    return ans;
}
