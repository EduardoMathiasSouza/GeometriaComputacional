#include <bits/stdc++.h>

#include "range-tree-2d-id/2d.hpp"
#include "segtree-windowing-id/segtree.hpp"

#define all(x) x.begin(), x.end()
using namespace std;
typedef pair<int, int> ii;

int32_t main() {
  int n,  // numero de segmentos
      w;  // numero de janelas
  cin >> n >> w;
  vector<pair<pair<ii, ii>, int>> segmentos(n);
  for (int i = 0; i < n; i++) {
    auto &[a, b] = segmentos[i].first;
    cin >> a.first >> b.first;
    cin >> a.second >> b.second;

    if (a.first > b.first) {
      swap(a, b);
    }

    segmentos[i].second = i + 1;  // id
  }
  // Preparacao para a rangetree
  vector<tuple<int, int, int>> pontos;
  for (auto &[ab, id] : segmentos) {
    pair<int, int> a, b;
    tie(a, b) = ab;
    pontos.emplace_back(a.first, a.second, id);
    pontos.emplace_back(b.first, b.second, id);
  }
  RangeTree2d rangeTree2d(pontos);

  // Preparacao para a segtree para segmentos horizontais
  vector<pair<pair<ii, ii>, int>> segmentos_inv(all(segmentos));
  for (auto &[ab, id] : segmentos_inv) {
    auto &[a, b] = ab;
    swap(a.first, a.second);
    swap(b.first, b.second);
    if (a.first > b.first) {
      swap(a, b);
    }
  }

  Segtree segtree_vertical(segmentos), segtree_horizontal(segmentos_inv);

  while (w--) {
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    // Resposta com a rangeTree(pontos que tem alguma ponta na janela)
    vi answer = rangeTree2d.query(x1, x2, y1, y2);

    // Resposta com a segtree(pontos que cruzam a janela)
    vector<int> leftedge = segtree_vertical.query(x1, y1, y2);
    vector<int> rightedge = segtree_vertical.query(x2, y1, y2);
    vector<int> bottomedge = segtree_horizontal.query(y1, x1, x2);
    vector<int> topedge = segtree_horizontal.query(y2, x1, x2);
    for (auto &x : {leftedge, rightedge, bottomedge, topedge}){
        answer.insert(answer.begin(), all(x));
    }

    // Imprimir resposta(sem repeticao)
    bool first = true;
    sort(all(answer));
    answer.resize(distance(answer.begin(), unique(all(answer))));
    for (auto &id : answer) {
      if (!first) cout << " ";
      cout << id;
      first = false;
    }
    cout << "\n";
  }
}
