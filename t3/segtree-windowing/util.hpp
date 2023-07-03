#include <bits/stdc++.h>
#define int long long
using namespace std;

struct point {
  int x, y;
  point(int _x, int _y) : x(_x), y(_y) {}
  point(pair<int, int> p) : x(p.first), y(p.second) {}
  point() {}
};

struct vet {
  int x, y;
  vet(int _x, int _y) : x(_x), y(_y) {}
  vet(point a, point b) : x(b.x - a.x), y(b.y - a.y) {}
  vet() {}
  vet operator-(vet oth) {
    vet c;
    c.x = this->x - oth.x;
    c.y = this->y - oth.y;
    return c;
  }
};

struct seg_t {
  point a, b;
  seg_t(point _a, point _b) : a(_a), b(_b) {}
  seg_t() {}
};

// produto vetorial
int cross(vet u, vet v) { return u.x * v.y - u.y * v.x; }

// produto escalar
int dot(vet u, vet v) { return u.x * v.x + u.y * v.y; }

// counter clockwise test
bool ccw(point p, point q, point r) {
    return cross(vet(p, q), vet(p, r)) >= 0; 
}

// clockwise test
bool cw(point p, point q, point r) {
    return cross(vet(p, q), vet(p, r)) <= 0; 
}

// retorna verdadeiro se dois segmentos de reta se intersectam interiormente
bool intersect(seg_t x, seg_t y) {
   // cout << "segmento: " << x.a.x << " " << x.a.y << ", " << x.b.x << " " << x.b.y << "\n";
   // cout << "   outro: " << y.a.x << " " << y.a.y << ", " << y.b.x << " " << y.b.y << "\n";
  // TODO: deixei menor ou igual a zero  
  vet u(x.a, x.b), v(x.b, y.a), w(x.b, y.b);
  vet _u(y.a, y.b), _v(y.b, x.a), _w(y.b, x.b);
  return (cross(u, v) * cross(u, w) <= 0) &&
         (cross(_u, _v) * cross(_u, _w) <= 0);
}

// distancia ponto ponto
/*ld dpp(point &a, point &b) {
  vet u(a, b);
  return sqrtl(dot(u, u));
}
*/
// distancia ponto segmento
/*ld dps(point &a, seg_t &x) {
  vet u(x.a, a), v(x.a, x.b);
  if (dot(v, v) < EPS) return dpp(x.a, a);
  ld lambda = dot(u, v) / dot(v, v);
  if (lambda < -EPS) return dpp(a, x.a);
  if (lambda > 1.) return dpp(a, x.b);
  return sqrtl(dot(u, u) - lambda * lambda * dot(v, v));
}*/

// distancia segmento segmento
/*ld dss(seg_t &x, seg_t &y) {
  if (intersect(x, y)) return 0;
  return min(dps(x.a, y), min(dps(x.b, y), min(dps(y.a, x), dps(y.b, x))));
}*/

