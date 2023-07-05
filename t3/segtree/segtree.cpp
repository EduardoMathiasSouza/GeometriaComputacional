#include "segtree.hpp"

#include <bits/stdc++.h>

item::item(int _l, int _r, bool _closed_left, bool _closed_right)
    : l{_l}, r{_r}, closed_left{_closed_left}, closed_right{_closed_right} {}

bool item::closed() { return closed_left && closed_right; }
bool item::half() { return (!closed_left) && (!closed_right); }

node node::operator+(node oth) {
  node c;
  c.limites = item(this->limites.l, oth.limites.r, this->limites.closed_left,
                   oth.limites.closed_right);
  return c;
}

bool node::subseteq(int l, int r) {
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
bool node::intersect(int l, int r) {  //[l, r]
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

bool Segtree::good(int i, int qx, int y1, int y2, int pos) {
  if (seg[pos].segmentos.empty()) return false;
  if (seg_t(get<0>(seg[pos].segmentos[i]), get<1>(seg[pos].segmentos[i]))
          .on_segment(ii(qx, y1)))
    return true;
  if (seg_t(get<0>(seg[pos].segmentos[i]), get<1>(seg[pos].segmentos[i]))
          .on_segment(ii(qx, y2)))
    return true;

  if (seg_t(ii(qx, y1), ii(qx, y2)).on_segment(get<0>(seg[pos].segmentos[i])))
    return true;
  if (seg_t(ii(qx, y1), ii(qx, y2)).on_segment(get<1>(seg[pos].segmentos[i])))
    return true;

  return cw(get<0>(seg[pos].segmentos[i]), get<1>(seg[pos].segmentos[i]),
            ii(qx, y1));
};

vector<int> Segtree::query(int qx, int y1, int y2) {
  return query(qx, y1, y2, 0, 0, tamseg);
}
vector<int> Segtree::query(int qx, int y1, int y2, int pos, int lx, int rx) {
  //  report all the interval in I(pos)
  vector<int> retval;

  int start = 0;
  if (!seg[pos].segmentos.empty() &&
      (!good(start, qx, min(y1, y2), max(y1, y2), pos))) {
    int a = 0;                              // bad
    int b = seg[pos].segmentos.size() - 1;  // good

    while (b - a > 1) {
      int mid = a + (b - a) / 2;
      if (good(mid, qx, min(y1, y2), max(y1, y2), pos)) {
        b = mid;
      } else {
        a = mid;
      }
    }
    start = b;
  }
  for (int i = start; i < seg[pos].segmentos.size(); i++) {
    auto [l, r, id] = seg[pos].segmentos[i];
    seg_t a(l, r);
    seg_t b(ii(qx, min(y1, y2)), ii(qx, max(y1, y2)));
    int d = dss(a, b);

    // if (intersect(a, b)) {  // intersect
    if (d == 0 || b.on_segment(l) || b.on_segment(r) ||
        a.on_segment(ii(qx, min(y1, y2))) ||
        a.on_segment(ii(qx, max(y1, y2)))) {  // intersect
      retval.emplace_back(id);
    } else {
      break;
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
    vector<int> left = query(qx, y1, y2, 2 * pos + 1, lx, mid);
    retval.insert(retval.end(), all(left));
  } else {
    vector<int> right = query(qx, y1, y2, 2 * pos + 2, mid, rx);
    retval.insert(retval.end(), all(right));
  }
  return retval;
}

void Segtree::insert(ii l, ii r, int id, int pos, int lx, int rx) {
  int mid = lx + (rx - lx) / 2;
  // Int(v) \subseteq [l : r]
  if (seg[pos].subseteq(l.first, r.first)) {
    seg[pos].segmentos.emplace_back(l, r, id);
  } else {
    // Int(lc(v)) interseção [l:r] não for vazia
    if (seg[2 * pos + 1].intersect(l.first, r.first)) {
      insert(l, r, id, 2 * pos + 1, lx, mid);
    }
    if (seg[2 * pos + 2].intersect(l.first, r.first)) {
      insert(l, r, id, 2 * pos + 2, mid, rx);
    }
  }
}

void Segtree::buildseg(vector<item> &elementares, int pos, int lx, int rx) {
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

bool Segtree::vertical(tuple<ii, ii, int> a) {
  return get<0>(a).first == get<1>(a).first;
}

bool Segtree::cmp(tuple<ii, ii, int> a, tuple<ii, ii, int> b) {
  int a1, b1, c1, d1;
  tie(a1, b1) = get<0>(a);
  tie(c1, d1) = get<1>(a);

  int w, x, y, z;
  tie(w, x) = get<0>(b);
  tie(y, z) = get<1>(b);

  ii max_y2, min_y2;
  if (x > z) {
    max_y2 = get<0>(b);
    min_y2 = get<1>(b);
  } else {
    max_y2 = get<1>(b);
    min_y2 = get<0>(b);
  }

  ii max_y1, min_y1;
  if (b1 > d1) {
    max_y1 = get<0>(a);
    min_y1 = get<1>(a);
  } else {
    max_y1 = get<1>(a);
    min_y1 = get<0>(a);
  }
  // vertical
  if (vertical(a) && vertical(b)) {
    return max_y1.second < max_y2.second;
  } else if (vertical(a)) {
    return !ccw(get<0>(b), get<1>(b), max_y1);
  } else if (vertical(b)) {
    return ccw(get<0>(a), get<1>(a), max_y2);
  }

  if (a1 < w) {
    vet u(point(a1, b1), point(c1, d1)), v(point(a1, b1), point(w, x));
    return cross(u, v) > 0;
  } else {
    vet u(point(w, x), point(y, z)), v(point(w, x), point(a1, b1));
    return cross(u, v) < 0;
  }
};

void Segtree::sortseg(int pos, int lx, int rx) {
  sort(all(seg[pos].segmentos), cmp);
  if (rx - lx == 1) {
    return;
  }
  int mid = lx + (rx - lx) / 2;
  sortseg(2 * pos + 1, lx, mid);
  sortseg(2 * pos + 2, mid, rx);
}

Segtree::Segtree(vector<pair<pair<ii, ii>, int>> &vet) {
  vector<int> endpoints;
  for (auto &[xy, id] : vet) {
    pair<int, int> x, y;
    tie(x, y) = xy;
    endpoints.emplace_back(x.first);
    endpoints.emplace_back(y.first);
  }
  sort(all(endpoints));
  endpoints.resize(distance(endpoints.begin(), unique(all(endpoints))));

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

  tamseg = 1;
  while (tamseg < elementares.size()) tamseg *= 2;

  seg.resize(2 * tamseg);
  buildseg(elementares, 0, 0, tamseg);

  // inserir os segmentos o mais alto possível
  for (auto &[xy, id] : vet) {
    pair<int, int> x, y;
    tie(x, y) = xy;
    insert(x, y, id, 0, 0, tamseg);
  }
  sortseg(0, 0, tamseg);
}
