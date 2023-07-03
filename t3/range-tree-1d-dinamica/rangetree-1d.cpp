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

struct node{
    int e = -1, d = -1, val = 0;
    bool ehfolha = false;
};

vector<node> tree;
int tam = 1;


int _create(){
    tree.emplace_back();
    return tree.size() - 1;
}

void initseg(){
    _create();
}

int build(vi &pontos, int pos, int lx, int rx){
    if (rx - lx == 1){
        if (lx < pontos.size()){
            tree[pos].val = pontos[lx];
        }else{
            tree[pos].val = oo;
        }
        tree[pos].ehfolha = true;
        return tree[pos].val;
    }
    int tmp = _create();
    tree[pos].e = tmp;
    tmp = _create();
    tree[pos].d = tmp;

//    cout << "left: " << tree[pos].e << " right: " << tree[pos].d << "\n";
    int mid = lx + (rx - lx)/2;
    int x = build(pontos, tree[pos].e, lx, mid);
    int y = build(pontos, tree[pos].d, mid, rx);
    tree[pos].val = x;
    return y;
}

void dump(int pos, int lx, int rx, int h = 0){
    for (int i=0; i < h; i++){
        cout << " ";
    }
    if (rx - lx == 1){
        cout << tree[pos].val << "(" << pos << ")\n";
        return;
    }
    cout << tree[pos].val << "(" << pos << ")\n";
    int mid = lx + (rx - lx)/2;
    dump(tree[pos].e, lx, mid, h + 1);
    dump(tree[pos].d, mid, rx, h + 1);
}

bool ehfolha(int v){
    return tree[v].ehfolha;
}

int findSplit(int l, int r){
    int v = 0;
    // TODO: substitui o 'menor ou igual' para só 'menor'
    while ( !ehfolha(v) && (r < tree[v].val || l > tree[v].val) ){
        if (r <= tree[v].val){
            v = tree[v].e;
        }else{
            v = tree[v].d;
        }
    }
    return v;
}

void reportSubtree(int pos, vi &answer){
    if (ehfolha(pos)){
        answer.emplace_back(tree[pos].val);
        return;
    }
    reportSubtree(tree[pos].e, answer);
    reportSubtree(tree[pos].d, answer);
}

vi query(int l, int r){
    vi answer;
    int pos = findSplit(l, r);
    if (ehfolha(pos)){
        // check if the point stored at v_split must be reported
        if ( l <= tree[pos].val && tree[pos].val <= r){
            answer.emplace_back(tree[pos].val);
        }
        return answer;
    }
    // follow the path to x and report the points in subtrees right to the path
    int now = pos;
    pos = tree[pos].e;
    while (!ehfolha(pos)){
        if (l <= tree[pos].val){
            reportSubtree(tree[pos].d, answer);
            pos = tree[pos].e;
        }else{
            pos = tree[pos].d;
        }
    }
    if ( l <= tree[pos].val && tree[pos].val <= r){
        answer.emplace_back(tree[pos].val);
    }

    pos = now;
    pos = tree[pos].d;
    while (!ehfolha(pos)){
        if (r >= tree[pos].val){
            reportSubtree(tree[pos].e, answer);
            pos = tree[pos].d;
        }else{
            pos = tree[pos].e;
        }
    }
    if ( l <= tree[pos].val && tree[pos].val <= r){
        answer.emplace_back(tree[pos].val);
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
    initseg();
    build(pontos, 0, 0, tam);
 
 //   dump(0, 0, tam);

 //   exit(0);
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

