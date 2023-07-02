#ifndef __RANGE_TREE__
#define __RANGE_TREE__

#include <bits/stdc++.h>
using namespace std;



#define int long long
typedef vector<int> vi;
typedef long long ll;
const ll oo = 1987654321987654321;

typedef pair<int, int> ii;
struct node{
    int e = -1, d = -1;
    ii val;
    bool ehfolha = false;
};

struct rangeTree1d{
    vector<node> tree;

    int _create();

    void initseg();

    int build(vector<ii> &pontos, int pos, int lx, int rx);

    void dump(int pos, int lx, int rx, int h = 0);

    bool ehfolha(int v);

    int findSplit(int root, int l, int r);

    void reportSubtree(int pos, vector<ii> &answer);

    vector<ii> query(int root, int l, int r);
};

#endif 
