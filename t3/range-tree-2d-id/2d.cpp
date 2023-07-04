#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "1d.hpp"

#define int long long
#define all(x) x.begin(), x.end()

using namespace __gnu_pbds;
using namespace std;

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long double ld;
typedef long long ll;
typedef pair<int, int> ii;
// typedef tuple<int, int, int> iii;
typedef vector<int> vi;
// const ll oo = 1987654321987654321;

template <class It>
void db(It b, It e) {
  for (auto it = b; it != e; it++) cout << *it << ' ';
  cout << endl;
}

struct item {
  RangeTree1d assoc;
  int xmid = oo;
  bool ehfolha = false;
  int tam = 0;  // TODO: remover
};

struct RangeTree2d {
  vector<item> tree2d;

  RangeTree2d(vector<iii> pontos) {
    int tam = 1;
    while (tam < pontos.size()) tam *= 2;
    tree2d.resize(2 * tam);

    sort(all(pontos));
    build2dRangeTree(pontos);
  }

  void build2dRangeTree(vector<iii> pontos, int pos = 0) {
    // cout << "pos: " << pos << " sz: " << pontos.size() << endl;

    //  contruir a 1d para o y, armazenando os pontos
    RangeTree1d rangeTree(pontos);


       int tam = 1;
       while (tam < pontos.size()) tam *= 2;


    tree2d[pos].tam = tam;  // TODO: remover
    tree2d[pos].assoc = rangeTree;
    if (pontos.size() == 1) {
      tree2d[pos].ehfolha = true;
      tree2d[pos].xmid = get<0>(pontos[0]);
      return;
    }

    for (int i = 0; i < pontos.size() - 1; i++) {
      assert(pontos[i] <= pontos[i + 1]);
    }

    size_t mediana = pontos.size() / 2;
    tree2d[pos].xmid = get<0>(pontos[mediana]);

    vector<iii> left, right;
    for (int i = 0; i < pontos.size(); i++) {
      if (i < mediana) {
        left.emplace_back(pontos[i]);
      } else
        right.emplace_back(pontos[i]);
    }
    //  cout << "pontos: " << pontos.size() << " left: " << left.size() << "
    //  right: " << right.size() << endl;
    build2dRangeTree(left, 2 * pos + 1);
    build2dRangeTree(right, 2 * pos + 2);
    //  dump(0);
  }

  bool ehfolha(int v) { return tree2d[v].ehfolha; }

  int findSplit(int l, int r) {
    int v = 0;
    while (!ehfolha(v) && (r < tree2d[v].xmid || l > tree2d[v].xmid)) {
      if (r <= tree2d[v].xmid) {
        v = 2 * v + 1;
      } else {
        v = 2 * v + 2;
      }
    }
    return v;
  }

  vector<int> query(int x1, int x2, int y1, int y2) {
    vector<int> answer;
    int pos = findSplit(x1, x2);
    int l = x1, r = x2;
    if (ehfolha(pos)) {
      if (x1 <= tree2d[pos].xmid && tree2d[pos].xmid <= x2) {
        answer = tree2d[pos].assoc.query(y1, y2);
      }
      return answer;
    }
    // follow the path to x and report the points in subtrees right to the path
    int now = pos;
    pos = 2 * pos + 1;
    while (!ehfolha(pos)) {
      if (l <= tree2d[pos].xmid) {
        // reportSubtree(2 * pos + 2, answer);
        vector<int> toadd = tree2d[2 * pos + 2].assoc.query(y1, y2);
        /*   cout << "going left:\n";
           tree2d[2 * pos + 2].assoc.dump(0, 0, tree2d[2 * pos + 2].tam);
           cout << "\n";*/

        /*
        cout << "toadd:\n";
        for (auto &[x, y] : toadd){
          cout << "(" << x << "," << y << ")\n";
        }*/
        answer.insert(answer.end(), all(toadd));

        pos = 2 * pos + 1;
      } else {
        pos = 2 * pos + 2;
      }
    }
    if (l <= tree2d[pos].xmid && tree2d[pos].xmid <= r) {
      vector<int> toadd = tree2d[pos].assoc.query(y1, y2);
      answer.insert(answer.end(), all(toadd));
    }

    pos = now;
    pos = 2 * pos + 2;
    while (!ehfolha(pos)) {
      if (r >= tree2d[pos].xmid) {
        // reportSubtree(2*pos + 1, answer);
        vector<int> toadd = tree2d[2 * pos + 1].assoc.query(y1, y2);
        answer.insert(answer.end(), all(toadd));
        /* cout << "going right:\n";
         tree2d[2 * pos + 1].assoc.dump(0, 0, tree2d[2 * pos + 1].tam);
         cout << "\n";*/

        /*
        cout << "toadd:\n";
        for (auto &[x, y] : toadd){
          cout << "(" << x << "," << y << ")\n";
        }*/
        pos = 2 * pos + 2;
      } else {
        pos = 2 * pos + 1;
      }
    }
    if (l <= tree2d[pos].xmid && tree2d[pos].xmid <= r) {
      vector<int> toadd = tree2d[pos].assoc.query(y1, y2);
      answer.insert(answer.end(), all(toadd));
    }
    return answer;
  }

  // Funcao de debug
  void dump(int pos, int h = 0) {
    cout << "id: " << pos << " xmid: " << tree2d[pos].xmid << "\n";
    tree2d[pos].assoc.dump(0, 0, tree2d[pos].tam);
    cout << "---\n\n";
    if (ehfolha(pos)) {
      return;
    }
    dump(2 * pos + 1, h + 1);
    dump(2 * pos + 2, h + 1);
  }
};

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
