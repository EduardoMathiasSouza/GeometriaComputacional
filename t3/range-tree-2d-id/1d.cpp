#include "1d.hpp"
#define all(x) x.begin(), x.end()

RangeTree1d::RangeTree1d(vector<iii> pontos){
    _create(); // Criação da raiz

    int tam = 1;
    while (tam < pontos.size()) tam *= 2;

    vector<iii> pontos_tmp(all(pontos));  // TODO
    sort(all(pontos_tmp),
         [](iii a, iii b) {
             return get<1>(a) < get<1>(b);  // ordena por y
         }
    );
    build(pontos_tmp, 0, 0, tam);
}

int RangeTree1d::_create(){
    tree.emplace_back();
    return tree.size() - 1;
}

int RangeTree1d::build(vector<iii> &pontos, int pos, int lx, int rx){
    if (rx - lx == 1){
        if (lx < pontos.size()){
            tree[pos].val = pontos[lx];
        }else{
            tree[pos].val = make_tuple(oo, oo, oo);
        }
        tree[pos].ehfolha = true;
        return get<1>(tree[pos].val);
    }
    int tmp = _create();
    tree[pos].e = tmp;
    tmp = _create();
    tree[pos].d = tmp;

//    cout << "left: " << tree[pos].e << " right: " << tree[pos].d << "\n";
    int mid = lx + (rx - lx)/2;
    int x = build(pontos, tree[pos].e, lx, mid);
    int y = build(pontos, tree[pos].d, mid, rx);
    tree[pos].val = make_tuple(x, x, x); // TODO:
    return y;
}

void RangeTree1d::dump(int pos, int lx, int rx, int h){
    for (int i=0; i < h; i++){
        cout << " ";
    }
    cout << "(" << get<0>(tree[pos].val) << "," << get<1>(tree[pos].val) << ")"<< " id: " << pos << "\n";
    if (rx - lx == 1){
        return;
    }
   // cout << tree[pos].val.second << "(" << pos << ")\n";
    int mid = lx + (rx - lx)/2;
    dump(tree[pos].e, lx, mid, h + 1);
    dump(tree[pos].d, mid, rx, h + 1);
}

bool RangeTree1d::ehfolha(int v){
    return tree[v].ehfolha;
}

int RangeTree1d::findSplit(int root, int l, int r){
    int v = root;
    // TODO: substitui o 'menor ou igual' para só 'menor'
    while ( !ehfolha(v) && (r < get<1>(tree[v].val) || l > get<1>(tree[v].val)) ){
        if (r <= get<1>(tree[v].val)){
            v = tree[v].e;
        }else{
            v = tree[v].d;
        }
    }
    return v;
}

void RangeTree1d::reportSubtree(int pos, vector<int> &answer){
    if (ehfolha(pos)){
        answer.emplace_back(get<2>(tree[pos].val));
        return;
    }
    reportSubtree(tree[pos].e, answer);
    reportSubtree(tree[pos].d, answer);
}

vector<int> RangeTree1d::query(int l, int r){
    int root = 0;
    vector<int> answer;
    int pos = findSplit(root, l, r);
    if (ehfolha(pos)){
        // check if the point stored at v_split must be reported
        if ( l <= get<1>(tree[pos].val) && get<1>(tree[pos].val) <= r){
            answer.emplace_back(get<2>(tree[pos].val));
        }
        return answer;
    }
    // follow the path to x and report the points in subtrees right to the path
    int now = pos;
    pos = tree[pos].e;
    while (!ehfolha(pos)){
        if (l <= get<1>(tree[pos].val)){
            reportSubtree(tree[pos].d, answer);
            pos = tree[pos].e;
        }else{
            pos = tree[pos].d;
        }
    }
    if ( l <= get<1>(tree[pos].val) && get<1>(tree[pos].val) <= r){
        answer.emplace_back(get<2>(tree[pos].val));
    }

    pos = now;
    pos = tree[pos].d;
    while (!ehfolha(pos)){
        if (r >= get<1>(tree[pos].val)){
            reportSubtree(tree[pos].e, answer);
            pos = tree[pos].d;
        }else{
            pos = tree[pos].e;
        }
    }
    if ( l <= get<1>(tree[pos].val) && get<1>(tree[pos].val) <= r){
        answer.emplace_back(get<2>(tree[pos].val));
    }
    return answer;
}
