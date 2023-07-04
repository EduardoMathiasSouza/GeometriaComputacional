#ifndef __RANGE_TREE__
#define __RANGE_TREE__

#include <bits/stdc++.h>
using namespace std;



#define int long long
typedef vector<int> vi;
typedef long long ll;
const ll oo = 1987654321987654321;

typedef tuple<int, int, int> iii;
typedef pair<int, int> ii;
struct node1d{
    int e = -1, d = -1;
    iii val;
    bool ehfolha = false;
};

struct RangeTree1d{
    vector<node1d> tree;

    RangeTree1d() = default;
    RangeTree1d(vector<iii> pontos);

    int _create();

    int build(vector<iii> &pontos, int pos, int lx, int rx);

    void dump(int pos, int lx, int rx, int h = 0);

    bool ehfolha(int v);

    int findSplit(int root, int l, int r);

    void reportSubtree(int pos, vector<int> &answer);

    vector<int> query(int l, int r);
};

#endif 
