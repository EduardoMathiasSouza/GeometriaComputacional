// Bruteforce para o problema: dados segmentos 1d descobrir quais são
// intersectados por uma reta qx

#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(), x.end()

using namespace std;
typedef pair<int, int> ii;

int32_t main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;
  // Leitura dos segmentos
  vector<ii> vet(n);
  for (auto &[x, y] : vet) {
    cin >> x >> y;
  }

  // Consultas
  int q;
  cin >> q;
  while (q--) {
    int qx;
    cin >> qx;

    vector<ii> answer;
    for (auto &[x, y] : vet) {
      if (x <= qx && qx <= y) {
        answer.emplace_back(x, y);
      }
    }
    sort(all(answer));
    bool first = true;
    for (auto &[x, y] : answer) {
      if (!first) cout << " ";
      cout << "(" << x << "," << y << ")";
      first = false;
    }
    cout << "\n";
  }
}
