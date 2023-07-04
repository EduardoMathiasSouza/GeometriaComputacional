#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "util.hpp"

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
const ll oo = 1987654321987654321;

template <class It>
void db(It b, It e) {
  for (auto it = b; it != e; it++) cout << *it << ' ';
  cout << endl;
}

bool vertical(pair<ii, ii> a){
    return a.first.first == a.second.first;
}

int32_t main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  vector<pair<ii, ii>> segmentos(3);
  for (auto &[x, y] : segmentos) {
    cin >> x.first >> x.second;
    cin >> y.first >> y.second;

    if (x.first > y.first) {
      swap(x, y);
    }
  }
  auto cmp = [](pair<ii, ii> a, pair<ii, ii> b) {
    auto [a1, b1] = a.first;
    auto [c1, d1] = a.second;

    auto [w, x] = b.first;
    auto [y, z] = b.second;

    ii max_y2, min_y2;
    if (b.first.second > b.second.second) {
      max_y2 = b.first;
      min_y2 = b.second;
    } else {
      max_y2 = b.second;
      min_y2 = b.first;
    }
    ii max_y1, min_y1;
    if (a.first.second > a.second.second) {
      max_y1 = a.first;
      min_y1 = a.second;
    } else {
      max_y1 = a.second;
      min_y1 = a.first;
    }
    // vertical
    if (vertical(a) && vertical(b)) {
      return max_y1.second < max_y2.second;
    } else if (vertical(a)) {
      return !ccw(b.first, b.second, max_y1);
        //return max_y1.second < max_y2.second;
    } else if (vertical(b)) {
      return ccw(a.first, a.second, max_y2);
      //  return (max_y2.second > max_y1.second); 
    }

    if (a1 < w) {
      vet u(point(a1, b1), point(c1, d1)), v(point(a1, b1), point(w, x));
      return cross(u, v) > 0;
    } else {
      vet u(point(w, x), point(y, z)), v(point(w, x), point(a1, b1));
      return cross(u, v) < 0;
    }
  };
  sort(all(segmentos), cmp);

  for (auto &[x, y] : segmentos) {
    cout << "(" << x.first << "," << x.second << ") -- ";
    cout << "(" << y.first << "," << y.second << ")\n";
  }
}
