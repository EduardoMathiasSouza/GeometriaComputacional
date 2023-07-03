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

#define MAXN 100
#define MAXX 100
#define MAXQ 100

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

  for (int i = 0; i < n; i++) {
    int x = gen(1, MAXX);
    int y = gen(x, MAXX);
    cout << x << " " << y << "\n";
  }
  int q = gen(1, MAXQ);
  cout << q << "\n";

  while (q--) {
    int qx = gen(-5, MAXX + 5);
    cout << qx << "\n";
  }
}
