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
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
// const ll oo = 1987654321987654321;

template <class It>
void db(It b, It e) {
  for (auto it = b; it != e; it++) cout << *it << ' ';
  cout << endl;
}

struct item {
  rangeTree1d assoc;
  int xmid = oo;
  bool ehfolha = false;
  int tam = 0; // TODO: remover
};

#define MAX 2123
item tree2d[MAX];

bool cmp(ii a, ii b) { return a.first < b.first; }

int mediana(vector<ii> &v) {
  size_t n = v.size() / 2;
  nth_element(v.begin(), v.begin() + n, v.end(), cmp);  // by_xcoordinate
  return v[n].first;
}

bool cmp2(ii a, ii b){
    return a.second < b.second;
}

/*
void build2dRangeTree(vector<ii> pontos, int pos = 0) {
  //cout << "pos: " << pos << " sz: " << pontos.size() << endl;
  // contruir a 1d para o y, armazenando os pontos
  rangeTree1d rangeTree;

  rangeTree.initseg();  // TODO: mudar de nome
  assert(pontos.size() > 0);
  int tam = 1;
  while (tam < pontos.size()) tam *= 2;
  vector<ii> pontos_tmp(all(pontos));// TODO
  sort(all(pontos_tmp), cmp2);
  rangeTree.build(pontos_tmp, 0, 0, tam);

  tree2d[pos].tam = tam; // TODO: remover
  tree2d[pos].assoc = rangeTree;
  if (pontos.size() == 1) {
    tree2d[pos].ehfolha = true;
    tree2d[pos].xmid = pontos[0].first;
    return;
  }


  for (int i=0; i < pontos.size() -1; i++){
    assert(pontos[i] <= pontos[i + 1]);
  }

  //int xmid = mediana(pontos);
  size_t mediana = pontos.size() / 2;
  tree2d[pos].xmid = pontos[mediana].first;

  vector<ii> left, right;
  for (int i=0; i < pontos.size(); i++){
    if (i < mediana){
      left.emplace_back(pontos[i]);
    }else
      right.emplace_back(pontos[i]);
  }
//  cout << "pontos: " << pontos.size() << " left: " << left.size() << " right: " << right.size() << endl;
  build2dRangeTree(left, 2 * pos + 1);
  build2dRangeTree(right, 2 * pos + 2);
}*/

void build2dRangeTree(vector<ii> pontos, int pos = 0) {
  //cout << "pos: " << pos << " sz: " << pontos.size() << endl;
  // contruir a 1d para o y, armazenando os pontos
  rangeTree1d rangeTree;

  rangeTree.initseg();  // TODO: mudar de nome
  assert(pontos.size() > 0);
  int tam = 1;
  while (tam < pontos.size()) tam *= 2;
  vector<ii> pontos_tmp(all(pontos));// TODO
  sort(all(pontos_tmp), cmp2);
  rangeTree.build(pontos_tmp, 0, 0, tam);

  tree2d[pos].tam = tam; // TODO: remover
  tree2d[pos].assoc = rangeTree;
  if (pontos.size() == 1) {
    tree2d[pos].ehfolha = true;
    tree2d[pos].xmid = pontos[0].first;
    return;
  }


  for (int i=0; i < pontos.size() -1; i++){
    assert(pontos[i] <= pontos[i + 1]);
  }

  //int xmid = mediana(pontos);
  size_t mediana = pontos.size() / 2;
  tree2d[pos].xmid = pontos[mediana].first;

  vector<ii> left, right;
  for (int i=0; i < pontos.size(); i++){
    if (i < mediana){
      left.emplace_back(pontos[i]);
    }else
      right.emplace_back(pontos[i]);
  }
//  cout << "pontos: " << pontos.size() << " left: " << left.size() << " right: " << right.size() << endl;
  build2dRangeTree(left, 2 * pos + 1);
  build2dRangeTree(right, 2 * pos + 2);
}

bool ehfolha(int v) { return tree2d[v].ehfolha; }


void dump(int pos, int h = 0){
    cout << "id: " << pos << " xmid: " << tree2d[pos].xmid << "\n";
    tree2d[pos].assoc.dump(0, 0, tree2d[pos].tam);
    cout << "---\n\n";
    if (ehfolha(pos)){
        return;
    }
    dump(2 * pos + 1, h + 1);
    dump(2 * pos + 2, h + 1);
}


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

vector<ii> query(int x1, int x2, int y1, int y2) {
  vector<ii> answer;
  int pos = findSplit(x1, x2);
  int l = x1, r = x2;
  if (ehfolha(pos)) {
    if (x1 <= tree2d[pos].xmid && tree2d[pos].xmid <= x2) {
      answer = tree2d[pos].assoc.query(0, y1, y2);
    }
    return answer;
  }
  // follow the path to x and report the points in subtrees right to the path
  int now = pos;
  pos = 2 * pos + 1;
  while (!ehfolha(pos)) {
    if (l <= tree2d[pos].xmid) {
      // reportSubtree(2 * pos + 2, answer);
      vector<ii> toadd = tree2d[2 * pos + 2].assoc.query(0, y1, y2);
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
    vector<ii> toadd = tree2d[pos].assoc.query(0, y1, y2);
    answer.insert(answer.end(), all(toadd));
  }

  pos = now;
  pos = 2 * pos + 2;
  while (!ehfolha(pos)) {
    if (r >= tree2d[pos].xmid) {
      // reportSubtree(2*pos + 1, answer);
      vector<ii> toadd = tree2d[2 * pos + 1].assoc.query(0, y1, y2);
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
    vector<ii> toadd = tree2d[pos].assoc.query(0, y1, y2);
    answer.insert(answer.end(), all(toadd));
  }
  return answer;
}


int32_t main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  vector<ii> pontos(n);
  for (auto &[x, y] : pontos) {
    cin >> x >> y;
  }
  sort(all(pontos));
/*  cout << "pontos: ";
  for (auto &[x, y] : pontos){
     cout << "(" << x << "," << y << ") ";
  }
  cout << "\n";*/
  build2dRangeTree(pontos);
//  dump(0);
  int q;
  cin >> q;
  while (q--) {
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
 
    if (x2 < x1) swap(x1, x2);
    if (y2 < y1) swap(y1, y2);

    vector<ii> answer = query(x1, x2, y1, y2);
    bool first = true;
    sort(all(answer));
    for (auto &[x, y] : answer) {
      if (!first) cout << " ";
      cout << "(" << x << "," << y << ")";
      first = false;
    }
    cout << "\n";
  }
}
