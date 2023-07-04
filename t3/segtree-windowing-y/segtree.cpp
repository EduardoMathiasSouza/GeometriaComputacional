#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(), x.end()

#include "util.hpp"

// TODO: simplificar mais o codigo
// TODO: colocar comentarios

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
const int oo = 1987654321987654321;

template <class It>
void db(It b, It e) {
  for (auto it = b; it != e; it++) cout << *it << ' ';
  cout << endl;
}

struct item {
  int l, r;
  bool closed_left = false;
  bool closed_right = false;
  item(int _l, int _r, bool _closed_left, bool _closed_right)
      : l{_l}, r{_r}, closed_left{_closed_left}, closed_right{_closed_right} {}

  bool closed() { return closed_left && closed_right; }
  bool half() { return (!closed_left) && (!closed_right); }

  void echo() {
    if (closed_left) {
      cout << "[";
    } else {
      cout << "(";
    }
    cout << l << "," << r;
    if (closed_right) {
      cout << "]";
    } else {
      cout << ")";
    }
  }
};

struct node {
  item limites = item(oo, oo, false, false);
  vector<pair<ii, ii>> segmentos;
  // TODO:

  node operator+(node oth) {
    node c;
    c.limites = item(this->limites.l, oth.limites.r, this->limites.closed_left,
                     oth.limites.closed_right);
    return c;
  }

  bool subseteq(int l, int r) {
    bool f1;
    if (limites.closed_left) {
      f1 = l <= limites.l;
    } else {
      f1 = l <= limites.l;
    }

    bool f2;
    if (limites.closed_right) {
      f2 = limites.r <= r;
    } else {
      f2 = limites.r <= r;
    }
    return f1 && f2;
  }

  // Int(lc(v)) interseção [l:r] não for vazia
  bool intersect(int l, int r) {  //[l, r]
    if (limites.closed_left) {
      if (r < limites.l) {
        return false;
      }
    } else {
      if (r <= limites.l) {
        return false;
      }
    }

    if (limites.closed_right) {
      if (l > limites.r) {
        return false;
      }
    } else {
      if (l >= limites.r) {
        return false;
      }
    }
    return true;
  }

  void dump(){
   limites.echo();
   cout << "\n";
   
   bool first = true;
    for (auto &[x, y] : segmentos) {
      if (!first) cout << " ";
      cout << "(" << x.first << "," << x.second << ") -- (" << y.first << "," << y.second << ")";
      first = false;
    }
    cout << "\n";
  }
};

#define MAX 2123
vector<node> seg(MAX);  // TODO
int tamseg = 1;


vector<pair<ii, ii>> query(int qx, int y1, int y2, int pos, int lx, int rx) {
 //  cout << "(query) pos: " << pos << "\n";
//   seg[pos].dump();
  //  report all the interval in I(pos)
  
  
  vector<pair<ii, ii>> retval;


  // TODO: mudar para busca binaria
  auto good = [](int i, int qx, int y1, int pos){
    if (seg[pos].segmentos.empty()) return false;
    assert( 0 <= i && i < seg[pos].segmentos.size());
    
 /*   cout << "good: (";
    cout << seg[pos].segmentos[i].first.first << ",";
    cout << seg[pos].segmentos[i].first.second << ") (";
    cout << seg[pos].segmentos[i].second.first << ",";
    cout << seg[pos].segmentos[i].second.second << ")\n";
    cout << "qx:" << qx << " y1: " << y1 << "\n";
*/
    return cw(seg[pos].segmentos[i].first, 
               seg[pos].segmentos[i].second,
               ii(qx, y1));
    point a(seg[pos].segmentos[i].first), 
          b(seg[pos].segmentos[i].second), 
          c(qx, y1);
    return ccw(a, b, c);
  };

  int start = 0;

  if (!seg[pos].segmentos.empty() && (!good(start, qx, y1, pos))){
    int a = 0; // bad
    int b = seg[pos].segmentos.size() - 1; // good

    while (b - a > 1){
        int mid = a + (b - a)/2;
        if (good(mid, qx, y1, pos)){
            b = mid;
        }else{
            a = mid;
        }
    }
    start = b;
  }
  if (!seg[pos].segmentos.empty()){
    //cout << "good: "  << good(0, qx, y1, pos) << " qx: " << qx << " y1: " << y1 << "\n";
  }

  //cout << "start:"  << start << "\n";
  for (int i=start; i < seg[pos].segmentos.size(); i++) {
      auto [l, r] = seg[pos].segmentos[i];
//      cout << "(" << l.first << "," << l.second << ") -- (" << r.first << "," << r.second << ")";
    seg_t a(point(l.first, l.second), point(r.first, r.second)), 
        b(point(qx, y1), point(qx, y2));
    if (intersect(a, b)){ // intersect
        retval.emplace_back(l, r);
 //       cout << " <--\n";
    }else{
        break;
 //       cout << " :(\n";
    }
  }

  if (rx - lx == 1) return retval;
  int mid = lx + (rx - lx) / 2;

  // qx \in Int(lc(v));
  int l, r;
  l = seg[2 * pos + 1].limites.l;
  r = seg[2 * pos + 1].limites.r;
  bool cl, cr;
  cl = seg[2 * pos + 1].limites.closed_left;
  cr = seg[2 * pos + 1].limites.closed_right;

  bool flag = true;
  if (cl) {
    flag &= qx >= l;
  } else {
    flag &= qx > l;
  }
  if (cr) {
    flag &= qx <= r;
  } else {
    flag &= qx < r;
  }

  if (flag) {
    vector<pair<ii, ii>> left = query(qx, y1, y2, 2 * pos + 1, lx, mid);
    retval.insert(retval.end(), all(left));
  } else {
    vector<pair<ii, ii>> right = query(qx, y1, y2, 2 * pos + 2, mid, rx);
    retval.insert(retval.end(), all(right));
  }
  return retval;
}

void insert(ii l, ii r, int pos, int lx, int rx) {
  int mid = lx + (rx - lx) / 2;
  // Int(v) \subseteq [l : r]
  if (seg[pos].subseteq(l.first, r.first)) {
    seg[pos].segmentos.emplace_back(l, r);
  } else {
    // Int(lc(v)) interseção [l:r] não for vazia
    if (seg[2 * pos + 1].intersect(l.first, r.first)) {
      insert(l, r, 2 * pos + 1, lx, mid);
    }
    if (seg[2 * pos + 2].intersect(l.first, r.first)) {
      insert(l, r, 2 * pos + 2, mid, rx);
    }
  }
}

void buildseg(vector<item> &elementares, int pos, int lx, int rx) {
  if (rx - lx == 1) {
    if (lx < elementares.size()) {
      seg[pos].limites = elementares[lx];
    } else {
      seg[pos].limites = item(oo, oo, false, false);
    }
    return;
  }
  int mid = lx + (rx - lx) / 2;
  buildseg(elementares, 2 * pos + 1, lx, mid);
  buildseg(elementares, 2 * pos + 2, mid, rx);
  seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
}

void dump(int pos, int lx, int rx, int h = 0) {
  cout << "(id: " << pos << ") ";
  for (int i = 0; i < h; i++) {
    cout << " ";
  }
  seg[pos].limites.echo();
  cout << ", seg: ";
  if (seg[pos].segmentos.empty()) cout << "(vazio)";
  for (auto &[x, y] : seg[pos].segmentos) {
  //  cout << "[" << x << "," << y << "] ";
  }
  cout << "\n";

  if (rx - lx == 1) {
    return;
  }
  int mid = lx + (rx - lx) / 2;
  dump(2 * pos + 1, lx, mid, h + 2);
  dump(2 * pos + 2, mid, rx, h + 2);
}

void build(vector<pair<ii, ii>> &vet) {
  vector<int> endpoints;
  for (auto &[x, y] : vet) {
    endpoints.emplace_back(x.first);
    endpoints.emplace_back(y.first);
  }
  sort(all(endpoints));
  endpoints.resize(distance(endpoints.begin(), unique(all(endpoints))));

  // cout << "endpoints:\n";
  //  db(all(endpoints));

  vector<item> elementares;

  // -oo, p[0]
  elementares.emplace_back(-oo, endpoints[0], false, false);

  // contruir a segment tree a partir dos elementares
  for (int i = 0; i < endpoints.size(); i++) {
    // closed interval
    elementares.emplace_back(endpoints[i], endpoints[i], true, true);

    if (i + 1 < endpoints.size()) {
      // half interval both ends
      elementares.emplace_back(endpoints[i], endpoints[i + 1], false, false);
    }
  }
  // p[m], oo
  elementares.emplace_back(endpoints.back(), oo, false, false);

  /*   cout << "elementares:";
     for (int i=0; i < elementares.size(); i++){
         elementares[i].echo();
         cout << " ";
     }
     cout << "\n";
 */

  tamseg = 1;
  while (tamseg < elementares.size()) tamseg *= 2;

  buildseg(elementares, 0, 0, tamseg);

  sort(all(vet),[](pair<ii, ii> a, pair<ii, ii> b){
        ii x, y, z;
        x = a.first;
        y = a.second;
        z = b.first;
        if (z == x || z == y) z = b.second;
        return ccw(x, y, z);
    }
          );
  // inserir os segmentos o mais alto possível
  for (auto &[x, y] : vet) {
    insert(x, y, 0, 0, tamseg);
  }
  // dump(0, 0, tamseg);
}

int32_t main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;

  // Leitura dos segmentos
  vector<pair<ii, ii>> vet(n);
  for (auto &[a, b] : vet) {
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
  }
  build(vet);

  // Consultas
  int q;
  cin >> q;
  while (q--) {
    int qx, y1, y2;
    cin >> qx >> y1 >> y2;
    vector<pair<ii, ii>> answer = query(qx, y1, y2, 0, 0, tamseg);

    sort(all(answer));

    bool first = true;
    for (auto &[x, y] : answer) {
      if (!first) cout << " ";
      cout << "(" << x.first << "," << x.second << ") -- (" << y.first << "," << y.second << ")";
      first = false;
    }
    cout << "\n";
  }
}
