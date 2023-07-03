#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(), x.end()
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
const ll oo = 1987654321987654321;

mt19937 rnd;
int gen(int a, int b) {
  uniform_int_distribution<int> dist(a, b);
  return dist(rnd);
}

#define MAXN 80 // Quantidade maxima de pontos gerados
#define MAXX 100 // Coordenada x máxima
#define MAXY 100 // Coordenada y máxima
#define MAXQ 100 // Quantidade máxima de queries
#define LESS_THAN false // Garante que x1 <= x2 && y1 <= y2 (coordenadas da caixa) 

int32_t main(int32_t argc, char *argv[]) {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  if (argc < 2) {
    cout << "usage: " << argv[0] << " <seed>\n";
    exit(1);
  }
  rnd = mt19937(atoi(argv[1]));

  int n = gen(1, MAXN);
  cout << n << "\n";
  for (int i=0; i < n; i++){
    int x = gen(1, MAXX);
    int y = gen(1, MAXY);
    cout << x << " " << y << "\n";
  }
  int q = MAXQ;
  cout << q << "\n";
  while (q--){
    int x1 = gen(1, MAXX - 5);
    int x2 = gen(1, MAXX + 5);
    int y1 = gen(1, MAXY - 5);
    int y2 = gen(1, MAXY + 5);

    if (LESS_THAN){
        if (x2 < x1) swap(x1, x2);
        if (y2 < y1) swap(y1, y2);
    }
    cout << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
  }

}
