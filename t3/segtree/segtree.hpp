#ifndef __SEGTREE__
#define __SEGTREE__

#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(), x.end()
#include "util.hpp"

#define oo 1987654321987654321

using namespace std;

typedef pair<int, int> ii;

struct item {
  int l, r;
  bool closed_left = false;
  bool closed_right = false;
  item(int _l, int _r, bool _closed_left, bool _closed_right);
  bool closed();
  bool half();
};

struct node {
  item limites = item(oo, oo, false, false);
  vector<tuple<ii, ii, int>> segmentos;
  node operator+(node oth);
  bool subseteq(int l, int r);

  // Int(lc(v)) interseção [l:r] não for vazia
  bool intersect(int l, int r);  //[l, r]
};

struct Segtree {
  vector<node> seg;
  int tamseg = 1;

  Segtree(vector<pair<pair<ii, ii>, int>> &vet);

  void buildseg(vector<item> &elementares, int pos, int lx, int rx);

  void insert(ii l, ii r, int id, int pos, int lx, int rx);

  vector<int> query(int qx, int y1, int y2, int pos, int lx, int rx);

  vector<int> query(int qx, int y1, int y2);

  void sortseg(int pos, int lx, int rx);

  static bool vertical(tuple<ii, ii, int> a);

  bool good(int i, int qx, int y1, int y2, int pos);

  static bool cmp(tuple<ii, ii, int> a, tuple<ii, ii, int> b);
};

#endif
