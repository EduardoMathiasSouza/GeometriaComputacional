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

    swap(a.first, a.second);
    swap(b.first, b.second);


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

    vector<pair<ii, ii>> answer = segtree.query(qx, y1, y2);
    for (auto &[x, y] : answer) {
      swap(x.first, x.second);
      swap(y.first, y.second);
    
      if (x > y) {
        swap(x, y);
      } 
    }
    sort(all(answer));
    bool first = true;
    for (auto &[x, y] : answer) {
      if (!first) cout << " ";
      cout << "(" << x.first << "," << x.second << ") -- (" << y.first << ","
           << y.second << ")";
      first = false;
    }
    cout << "\n";
  }
}
