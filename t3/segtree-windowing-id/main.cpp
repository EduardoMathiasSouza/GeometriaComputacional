#include <bits/stdc++.h>

#define int long long
#define all(x) x.begin(), x.end()

#include "segtree.hpp"

// TODO: simplificar mais o codigo
// TODO: colocar comentarios

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

template <class It>
void db(It b, It e) {
  for (auto it = b; it != e; it++) cout << *it << ' ';
  cout << endl;
}

int32_t main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;

  // Leitura dos segmentos
  vector<pair<pair<ii, ii>, int>> vet(n);
  int cnt = 1;
  for (auto &[ab, id] : vet) {
    auto &[a, b] = ab;
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
    if (a.first > b.first) {
      swap(a, b);
    }
    id = cnt++;
  }
  Segtree segtree(vet);

  // Consultas
  int q;
  cin >> q;
  while (q--) {
    int qx, y1, y2;
    cin >> qx >> y1 >> y2;

    vector<int> answer = segtree.query(qx, y1, y2);
    sort(all(answer));
    bool first = true;
    for (auto &id : answer) {
      if (!first) cout << " ";
      cout << id;
      first = false;
    }
    cout << "\n";
  }
}
