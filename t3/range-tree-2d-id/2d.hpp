#include <bits/stdc++.h>

#include "1d.hpp"
#define int long long
#define all(x) x.begin(), x.end()
using namespace std;

typedef tuple<int, int, int> iii;

struct item {  // TODO: mudar nome
  RangeTree1d assoc;
  int xmid = oo;
  bool ehfolha = false;
  int tam = 0;  // TODO: remover
};

struct RangeTree2d {
  vector<item> tree2d;

  RangeTree2d(vector<iii> pontos);

  void build2dRangeTree(vector<iii> pontos, int pos = 0);

  bool ehfolha(int v);

  int findSplit(int l, int r);

  vector<int> query(int x1, int x2, int y1, int y2);

  // Funcao de debug
  void dump(int pos, int h = 0);
};
