#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(), x.end()


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
  vector<ii> segmentos;
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
};

#define MAX 2123
vector<node> seg(MAX);  // TODO
int tamseg = 1;

vector<ii> query(int qx, int pos, int lx, int rx) {
  // cout << "(query) pos: " << pos << "\n";
  //  report all the interval in I(pos)
  vector<ii> retval;
  for (auto &[l, r] : seg[pos].segmentos) {
    retval.emplace_back(l, r);
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
    vector<ii> left = query(qx, 2 * pos + 1, lx, mid);
    retval.insert(retval.end(), all(left));
  } else {
    vector<ii> right = query(qx, 2 * pos + 2, mid, rx);
    retval.insert(retval.end(), all(right));
  }
  return retval;
}

void insert(int l, int r, int pos, int lx, int rx) {
  int mid = lx + (rx - lx) / 2;
  // Int(v) \subseteq [l : r]
  if (seg[pos].subseteq(l, r)) {
    seg[pos].segmentos.emplace_back(l, r);
  } else {
    // Int(lc(v)) interseção [l:r] não for vazia
    if (seg[2 * pos + 1].intersect(l, r)) {
      insert(l, r, 2 * pos + 1, lx, mid);
    }
    if (seg[2 * pos + 2].intersect(l, r)) {
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
    cout << "[" << x << "," << y << "] ";
  }
  cout << "\n";

  if (rx - lx == 1) {
    return;
  }
  int mid = lx + (rx - lx) / 2;
  dump(2 * pos + 1, lx, mid, h + 2);
  dump(2 * pos + 2, mid, rx, h + 2);
}

void build(vector<ii> &vet) {
  vector<int> endpoints;
  for (auto &[x, y] : vet) {
    endpoints.emplace_back(x);
    endpoints.emplace_back(y);
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
  vector<ii> vet(n);
  for (auto &[l, r] : vet) {
    cin >> l >> r;
  }
  build(vet);

  // Consultas
  int q;
  cin >> q;
  while (q--) {
    int qx;
    cin >> qx;
    vector<ii> answer = query(qx, 0, 0, tamseg);

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
