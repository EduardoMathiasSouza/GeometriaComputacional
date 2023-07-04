#include <bits/stdc++.h>
#include "range-tree-2d-id/2d.hpp"

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

  while (w--) {
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    // Resposta com a rangeTree(pontos que tem alguma ponta na janela)
    vi answer = rangeTree2d.query(x1, x2, y1, y2);

    // Resposta com a segtree(pontos que cruzam a janela)

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
