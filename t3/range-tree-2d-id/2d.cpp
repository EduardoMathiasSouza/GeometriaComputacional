#include "2d.hpp"

#include <bits/stdc++.h>

RangeTree2d::RangeTree2d(vector<iii> pontos) {
  int tam = 1;
  while (tam < pontos.size()) tam *= 2;
  tree2d.resize(2 * tam);

  sort(all(pontos));
  build2dRangeTree(pontos);
}

void RangeTree2d::build2dRangeTree(vector<iii> pontos, int pos) {
  // cout << "pos: " << pos << " sz: " << pontos.size() << endl;

  //  contruir a 1d para o y, armazenando os pontos
  RangeTree1d rangeTree(pontos);

  int tam = 1;
  while (tam < pontos.size()) tam *= 2;

  tree2d[pos].tam = tam;  // TODO: remover
  tree2d[pos].assoc = rangeTree;
  if (pontos.size() == 1) {
    tree2d[pos].ehfolha = true;
    tree2d[pos].xmid = get<0>(pontos[0]);
    return;
  }

  for (int i = 0; i < pontos.size() - 1; i++) {
    assert(pontos[i] <= pontos[i + 1]);
  }

  size_t mediana = pontos.size() / 2;
  tree2d[pos].xmid = get<0>(pontos[mediana]);

  vector<iii> left, right;
  for (int i = 0; i < pontos.size(); i++) {
    if (i < mediana) {
      left.emplace_back(pontos[i]);
    } else
      right.emplace_back(pontos[i]);
  }
  //  cout << "pontos: " << pontos.size() << " left: " << left.size() << "
  //  right: " << right.size() << endl;
  build2dRangeTree(left, 2 * pos + 1);
  build2dRangeTree(right, 2 * pos + 2);
  //  dump(0);
}

bool RangeTree2d::ehfolha(int v) { return tree2d[v].ehfolha; }

int RangeTree2d::findSplit(int l, int r) {
  int v = 0;
  while (!ehfolha(v) && (r < tree2d[v].xmid || l > tree2d[v].xmid)) {
    if (r <= tree2d[v].xmid) {
      v = 2 * v + 1;
    } else {
      v = 2 * v + 2;
    }
  }
  return v;
}

vector<int> RangeTree2d::query(int x1, int x2, int y1, int y2) {
  vector<int> answer;
  int pos = findSplit(x1, x2);
  int l = x1, r = x2;
  if (ehfolha(pos)) {
    if (x1 <= tree2d[pos].xmid && tree2d[pos].xmid <= x2) {
      answer = tree2d[pos].assoc.query(y1, y2);
    }
    return answer;
  }
  // follow the path to x and report the points in subtrees right to the path
  int now = pos;
  pos = 2 * pos + 1;
  while (!ehfolha(pos)) {
    if (l <= tree2d[pos].xmid) {
      // reportSubtree(2 * pos + 2, answer);
      vector<int> toadd = tree2d[2 * pos + 2].assoc.query(y1, y2);
      /*   cout << "going left:\n";
         tree2d[2 * pos + 2].assoc.dump(0, 0, tree2d[2 * pos + 2].tam);
         cout << "\n";*/

      /*
      cout << "toadd:\n";
      for (auto &[x, y] : toadd){
        cout << "(" << x << "," << y << ")\n";
      }*/
      answer.insert(answer.end(), all(toadd));

      pos = 2 * pos + 1;
    } else {
      pos = 2 * pos + 2;
    }
  }
  if (l <= tree2d[pos].xmid && tree2d[pos].xmid <= r) {
    vector<int> toadd = tree2d[pos].assoc.query(y1, y2);
    answer.insert(answer.end(), all(toadd));
  }

  pos = now;
  pos = 2 * pos + 2;
  while (!ehfolha(pos)) {
    if (r >= tree2d[pos].xmid) {
      // reportSubtree(2*pos + 1, answer);
      vector<int> toadd = tree2d[2 * pos + 1].assoc.query(y1, y2);
      answer.insert(answer.end(), all(toadd));
      /* cout << "going right:\n";
       tree2d[2 * pos + 1].assoc.dump(0, 0, tree2d[2 * pos + 1].tam);
       cout << "\n";*/

      /*
      cout << "toadd:\n";
      for (auto &[x, y] : toadd){
        cout << "(" << x << "," << y << ")\n";
      }*/
      pos = 2 * pos + 2;
    } else {
      pos = 2 * pos + 1;
    }
  }
  if (l <= tree2d[pos].xmid && tree2d[pos].xmid <= r) {
    vector<int> toadd = tree2d[pos].assoc.query(y1, y2);
    answer.insert(answer.end(), all(toadd));
  }
  return answer;
}

// Funcao de debug
void RangeTree2d::dump(int pos, int h) {
  cout << "id: " << pos << " xmid: " << tree2d[pos].xmid << "\n";
  tree2d[pos].assoc.dump(0, 0, tree2d[pos].tam);
  cout << "---\n\n";
  if (ehfolha(pos)) {
    return;
  }
  dump(2 * pos + 1, h + 1);
  dump(2 * pos + 2, h + 1);
}
