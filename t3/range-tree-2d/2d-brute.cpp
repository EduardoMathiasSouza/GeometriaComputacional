#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
#define all(x) x.begin(), x.end()

using namespace __gnu_pbds;
using namespace std;

template<class T> using ordered_set = tree<T, null_type , less<T> , rb_tree_tag , tree_order_statistics_node_update> ;
typedef long double ld; 
typedef long long ll; 
typedef pair<int, int> ii; 
typedef tuple<int, int, int> iii;
typedef vector<int> vi; 
const ll oo = 1987654321987654321;

template<class It> void db(It b, It e) {
    for (auto it = b; it != e; it++) cout << *it << ' ';
    cout<< endl;
}

int32_t main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    vector<ii> pontos(n);
    for (auto &[x, y] : pontos) cin >> x >> y;

    int q;
    cin >> q;
    while (q--){
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;

        int tmp = min(x1, x2);
        x2 = max(x1, x2);
        x1 = tmp;

        tmp = min(y1, y2);
        y2 = max(y1, y2);
        y1 = tmp;


        vector<ii> answer;
        for (auto &[x, y] : pontos){
            if ( x1 <= x && x <= x2 &&
                 y1 <= y && y <= y2){
                answer.emplace_back(x, y);
            }
        }
        sort(all(answer));
        bool first = true;
        for (auto &[x, y] : answer){
            if (!first) cout << " ";
            cout << "(" << x << "," << y << ")";
            first = false;
        }
        cout << "\n";
    }
}

