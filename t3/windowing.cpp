#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii; 

int main(){
    int n, // numero de segmentos 
        w; // numero de janelas
    cin >> n >> w;
    vector<pair<pair<ii, ii>, int>> segmentos(n);
    for (int i=0; i < n; i++){
        auto &[a, b] = segmentos[i].first;
        cin >> a.first >> b.first;
        cin >> a.second >> b.second;

        segmentos[i].second = i + 1; // id
    }

    while (w--){
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        // Resposta com a rangeTree(pontos que tem alguma ponta na janela)
        
        // Resposta com a segtree(pontos que cruzam a janela)

        // Imprimir resposta(sem repeticao)
    }
}

