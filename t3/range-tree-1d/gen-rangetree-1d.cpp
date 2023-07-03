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

#define MAXN 10 // Tamanho máximo do vetor de pontos
#define MAXV 10 // Tamanho máximo das coordenadas
#define MAXQ 10 // Quantidade máxima de queries

#define UNIQUE false // Flag se as coordenadas vão ser necessasriamente únicas ou não

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

  if (UNIQUE){
    vector<int> v;
    set<int> s;
    while (s.size() < n){
        int x = gen(1, MAXV);
        if (!s.count(x)){
            s.insert(x);
            v.emplace_back(x);
        }
    }  
    for (auto &x: v ) cout << x << " ";
    cout << "\n";
  }else{
      for (int i=0; i < n; i++){
        cout << gen(1, MAXV) << " ";
      }
  }
  cout << "\n";
  int q = gen(1, MAXQ);
  cout << q << "\n";
  while (q--){
    int l = gen(1, MAXV + 5);
    int r = gen(l, MAXV + 5);
    cout << l << " " << r << "\n";
  }
}
