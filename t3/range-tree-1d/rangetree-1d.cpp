#include <bits/stdc++.h>

// Implementação da rangetree 1d - seguindo as especificações do livro

#define int long long
#define all(x) x.begin(), x.end()

using namespace std;

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

#define MAX 21234
int tree[MAX];
int tam = 1;

int build(vi &pontos, int pos, int lx, int rx){
    if (rx - lx == 1){
        if (lx < pontos.size()){
            tree[pos] = pontos[lx];
        }else{
            tree[pos] = oo;
        }
        return tree[pos];
    }
    int mid = lx + (rx - lx)/2;
    int x = build(pontos, 2 * pos + 1, lx, mid);
    int y = build(pontos, 2 * pos + 2, mid, rx);
    tree[pos] = x;
    return y;
}

void dump(int pos, int lx, int rx, int h = 0){
    for (int i=0; i < h; i++){
        cout << " ";
    }
    if (rx - lx == 1){
        cout << tree[pos] << "(" << pos << ")\n";
        return;
    }
    cout << tree[pos] << "(" << pos << ")\n";
    int mid = lx + (rx - lx)/2;
    dump(2 * pos + 1, lx, mid, h + 1);
    dump(2 * pos + 2, mid, rx, h + 1);
}

bool ehfolha(int v){
    return v >= (tam - 1);
}

int findSplit(int l, int r){
    int v = 0;
    // TODO: substitui o 'menor ou igual' para só 'menor'
    while ( !ehfolha(v) && (r < tree[v] || l > tree[v]) ){
        if (r <= tree[v]){
            v = 2 * v + 1;
        }else{
            v = 2 * v + 2;
        }
    }
    return v;
}

void reportSubtree(int pos, vi &answer){
    if (ehfolha(pos)){
        answer.emplace_back(tree[pos]);
        return;
    }
    reportSubtree(2 * pos + 1, answer);
    reportSubtree(2 * pos + 2, answer);
}

vi query(int l, int r){
    vi answer;
    int pos = findSplit(l, r);
    if (ehfolha(pos)){
        // check if the point stored at v_split must be reported
        if ( l <= tree[pos] && tree[pos] <= r){
            answer.emplace_back(tree[pos]);
        }
        return answer;
    }
    // follow the path to x and report the points in subtrees right to the path
    int now = pos;
    pos = 2 * pos + 1;
    while (!ehfolha(pos)){
        if (l <= tree[pos]){
            reportSubtree(2 * pos + 2, answer);
            pos = 2 * pos + 1;
        }else{
            pos = 2 * pos + 2;
        }
    }
    if ( l <= tree[pos] && tree[pos] <= r){
        answer.emplace_back(tree[pos]);
    }

    pos = now;
    pos = 2 * pos + 2;
    while (!ehfolha(pos)){
        if (r >= tree[pos]){
            reportSubtree(2 * pos + 1, answer);
            pos = 2 * pos + 2;
        }else{
            pos = 2 * pos + 1;
        }
    }
    if ( l <= tree[pos] && tree[pos] <= r){
        answer.emplace_back(tree[pos]);
    }
    return answer;
}


int32_t main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    vi pontos(n);
    for (auto &x: pontos) cin >> x;
    sort(all(pontos));

    while (tam < n){
        tam *= 2;
    }
    build(pontos, 0, 0, tam);
 //   dump(0, 0, tam);

    int q;
    cin >> q;
    while (q--){
        int l, r;
        cin >> l >> r;
        vi answer = query(l, r);
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

