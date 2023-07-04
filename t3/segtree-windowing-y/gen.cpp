#include <bits/stdc++.h>

#include "util.hpp"

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

#define MAXX 10
#define MAXY 10
#define MAXQ 10
#define MAXN 20

int32_t main(int32_t argc, char *argv[]) {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  if (argc < 2) {
    cout << "usage: " << argv[0] << " <seed>\n";
    exit(1);
  }
  rnd = mt19937(atoi(argv[1]));

  int n = gen(1, MAXN);
  //cout << n << ""
  
  vector<pair<ii, ii>> segmentos(n);
  for (int i=0; i < n; i++){
    segmentos[i].first.first = gen(1, MAXX);
    segmentos[i].first.second = gen(1, MAXY);
  

    segmentos[i].second.first = gen(1, MAXX);
    segmentos[i].second.second = gen(1, MAXY);
  
    while (segmentos[i].first == segmentos[i].second){
        segmentos[i].second.first = gen(1, MAXX);
        segmentos[i].second.second = gen(1, MAXY);
    }
  }
  vector<bool> invalid(n, false);
  for (int i=0; i < n; i++){
    if (!invalid[i]){
        for (int j=0; j < i; j++){
            if (!invalid[j]){
                seg_t a(segmentos[i].first, segmentos[i].second), 
                      b(segmentos[j].first, segmentos[j].second);
                // intersect
                if (intersect(a, b) ||
                    a.on_segment(b.a) || a.on_segment(b.b) ||
                    b.on_segment(a.a) || b.on_segment(a.b)){
                    invalid[i] = true;
                }
            }
        }
    }
  }
  int tam = 0;
  for (int i=0; i < n; i++){
    if (!invalid[i]){
        tam++;
    }
  }
  cout << tam << "\n";
  for (int i=0; i < n; i++){
    if (!invalid[i]){
        cout << segmentos[i].first.first << " " << segmentos[i].first.second << " " << segmentos[i].second.first << " " << segmentos[i].second.second << "\n";
    }
  }
  int q = gen(1,MAXQ);

  cout << q << "\n";
  while (q--){
    int qy, x1, x2;
    qy = gen(1, MAXY);
    x1 = gen(1, MAXX);
    x2 = gen(1, MAXX);
    while (x1 == x2){
       x2 = gen(1, MAXY);
    }
    if (x2 > x1) swap(x1, x2);
    
    cout << qy << " " << x1 << " " << x2 << "\n";
  }
  
}

