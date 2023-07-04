// Codigo de testes para RangeTree2d

#include <bits/stdc++.h>
#include "2d.hpp"

#define int long long
#define all(x) x.begin(), x.end()

int32_t main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  vector<iii> pontos(n);

  for (int i = 0; i < n; i++) {
    auto &[x, y, id] = pontos[i];
    cin >> x >> y;
    id = i + 1;
  }
  /*  cout << "pontos: ";
    for (auto &[x, y] : pontos){
       cout << "(" << x << "," << y << ") ";
    }
    cout << "\n";*/
  RangeTree2d rangeTree2d(pontos);

  int q;
  cin >> q;
  while (q--) {
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;

    if (x2 < x1) swap(x1, x2);
    if (y2 < y1) swap(y1, y2);

    vector<int> answer = rangeTree2d.query(x1, x2, y1, y2);
    bool first = true;
    sort(all(answer));
    for (auto &id : answer) {
      if (!first) cout << " ";
      cout << id;
      first = false;
    }
    cout << "\n";
  }
}
