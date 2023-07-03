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
    vi pontos(n);
    for (auto &x: pontos) cin >> x;
    int q;
    cin >> q;
    while (q--){
        int l, r;
        cin >> l >> r;
        vi answer;
        for (auto &x: pontos){
            if ( l <= x && x <= r){
                answer.emplace_back(x);
            }
        }
        sort(all(answer));
        bool first = true;
        for (auto &x: answer){
            if (!first) cout << " ";
            cout << x;
            first = false;
        }
        cout << "\n";
    }
}

