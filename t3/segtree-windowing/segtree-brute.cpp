#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "util.hpp"

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
    vector<pair<ii, ii>> segmentos(n);
    for (auto &[x, y] : segmentos){
        cin >> x.first >> x.second;
        cin >> y.first >> y.second;
    
        if (x.first > y.first){
            swap(x, y);
        }
    }
    int q;
    cin >> q;
    while (q--){
        int qx, y1, y2;
        cin >> qx >> y1 >> y2;
        if (y2 < y1) swap(y1, y2);


 //       cout << "qx: " << qx << " y1: " << y1 << " y2: " << y2 << "\n";

        vector<pair<ii, ii>> answer;
        for (auto &[x, y] : segmentos){
            seg_t a(x, y);
            seg_t b(ii(qx, y1), ii(qx, y2));
            
            int d = dss(a, b);
           // cout << "(" << x.first << "," << x.second << ") -- ";
           // cout << "(" << y.first << "," << y.second << ") ";

           // cout << "d: " << d << "\n";
            if (d == 0 || b.on_segment(x) || b.on_segment(y) || a.on_segment(ii(qx, y1)) || a.on_segment(ii(qx, y2))){
                answer.emplace_back(x, y);
            }
        }

 
        sort(all(answer));
        bool first = true;
        for (auto &[x, y] : answer){
            if (!first) cout << " ";
            cout << "(" << x.first << "," << x.second << ") -- ";
            cout << "(" << y.first << "," << y.second << ")";
            first = false;
        }
        cout << "\n";
    }
}

