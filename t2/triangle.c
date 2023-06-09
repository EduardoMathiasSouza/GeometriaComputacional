#include <stdio.h>
#include <stdlib.h>

struct point {
    int index;
    int opposite;
    int x;
    int y;
};

struct triangle {
    struct point a;
    struct point b;
    struct point c;
    int index;
};

int is_ear(struct point a, struct point b, struct point c, struct point *points, int num_points) {
    int i;
    int cross_product = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (cross_product <= 0) {
        return 0; // nao eh orelha
    }
    for (i = 0; i < num_points; i++) {
        if ((points[i].x == a.x && points[i].y == a.y) || (points[i].x == b.x && points[i].y == b.y) || (points[i].x == c.x && points[i].y == c.y)) {
            continue;
        }
        int cross_product1 = (b.x - a.x) * (points[i].y - a.y) - (b.y - a.y) * (points[i].x - a.x);
        int cross_product2 = (c.x - b.x) * (points[i].y - b.y) - (c.y - b.y) * (points[i].x - b.x);
        int cross_product3 = (a.x - c.x) * (points[i].y - c.y) - (a.y - c.y) * (points[i].x - c.x);
        if (cross_product1 >= 0 && cross_product2 >= 0 && cross_product3 >= 0) {
            return 0; // ponto esta dentro do triangulo logo nao eh orelha
        }
    }
    return 1;
}

void triangulate(struct point *points, int num_points, struct triangle **triangles, int *num_triangles) {
    int i, j, k;
    int *indices = malloc(num_points * sizeof(int));
    for (i = 0; i < num_points; i++) {
        indices[i] = i;
    }
    *triangles = NULL;
    *num_triangles = 0;
    int orientation = 0; // 0 para antihoraria, 1 para horaria
    int cross_product = 0;
    for (i = 0; i < num_points; i++) {
        j = (i + 1) % num_points;
        k = (i + 2) % num_points;
        cross_product = (points[j].x - points[i].x) * (points[k].y - points[i].y) - (points[j].y - points[i].y) * (points[k].x - points[i].x);
        if (cross_product != 0) {
            orientation = (cross_product > 0) ? 0 : 1;
            break;
        }
    }
    if (orientation == 1) { //Caso horario, inverte a ordem dos pontos no vetor de indices
        for (i = 0; i < num_points; i++) {
            indices[i] = (num_points - 1) - i;
        }
    }
    while (num_points >= 3) {
        for (i = 0; i < num_points; i++) {
            j = (i + 1) % num_points;
            k = (i + 2) % num_points;
            if (is_ear(points[indices[i]], points[indices[j]], points[indices[k]], points, num_points)) {
                struct triangle t = {points[indices[i]], points[indices[j]], points[indices[k]], (*num_triangles+1)};
                (*triangles) = realloc(*triangles, (*num_triangles + 1) * sizeof(struct triangle));
                (*triangles)[*num_triangles] = t;
                (*num_triangles)++;
                for (j = i + 1; j < num_points - 1; j++) {
                    indices[j] = indices[j + 1];
                }
                num_points--;
                break;
            }
        }
    }
    free(indices);
}

int is_vertex(struct point p, struct triangle t){
    if(p.index == t.a.index || p.index == t.b.index || p.index == t.c.index){
        return 1;
    }
    return 0;
}

void find_opposite(int num_triangles, struct triangle **triangles){
    for(int i = 0; i < num_triangles; i++){
        struct triangle t = (*triangles)[i];
        int flag = 0;
        for(int j = 0; j < num_triangles; j++){
            if(t.a.index != (*triangles)[j].a.index && t.a.index != (*triangles)[j].b.index && t.a.index != (*triangles)[j].c.index){
                if(is_vertex(t.b, (*triangles)[j]) && is_vertex(t.c, (*triangles)[j])){
                    (*triangles)[i].a.opposite = (*triangles)[j].index;
                    flag = 1;
                }
            }
            if(t.b.index != (*triangles)[j].a.index && t.b.index != (*triangles)[j].b.index && t.b.index != (*triangles)[j].c.index){
                if(is_vertex(t.a, (*triangles)[j]) && is_vertex(t.c, (*triangles)[j])){
                    (*triangles)[i].b.opposite = (*triangles)[j].index;
                    flag = 1;
                    }
            }
            if(t.c.index != (*triangles)[j].a.index && t.c.index != (*triangles)[j].b.index && t.c.index != (*triangles)[j].c.index){
                if(is_vertex(t.a, (*triangles)[j]) && is_vertex(t.b, (*triangles)[j])){
                    (*triangles)[i].c.opposite = (*triangles)[j].index;    
                    flag = 1;
                    }
            }
            if(flag){
                break;
            }
        }
    }
}

void order_points_triangle(struct triangle *t){
    struct point a = t->a;
    struct point b = t->b;
    struct point c = t->c;
    struct point temp;
    if(a.index > b.index){
        temp = a;
        a = b;
        b = temp;
    }
    if(a.index > c.index){
        temp = a;
        a = c;
        c = temp;
    }
    if(b.index > c.index){
        temp = b;
        b = c;
        c = temp;
    }
    t->a = a;
    t->b = b;
    t->c = c;
}

int main() {
    int n_points= 0;
    scanf("%d", &n_points);
    struct point *points = malloc(n_points * sizeof(struct point));
    for(int i = 0; i < n_points; i++){
        scanf("%d %d",&points[i].x, &points[i].y);
        points[i].index = i+1;
        points[i].opposite = 0;
    }

    struct triangle *triangles;
    int num_triangles;
    printf("%d\n", n_points);
    for(int i = 0; i < n_points; i++)
        printf("%d %d\n", points[i].x, points[i].y);
    triangulate(points, n_points, &triangles, &num_triangles);
    printf("%d\n", num_triangles);
    for(int i = 0; i < num_triangles; i++)
        order_points_triangle(&triangles[i]);
    find_opposite(num_triangles, &triangles);
    for (int i = 0; i < num_triangles; i++) {
        printf("%d %d %d %d %d %d\n", triangles[i].a.index, triangles[i].b.index, triangles[i].c.index, triangles[i].a.opposite, triangles[i].b.opposite, triangles[i].c.opposite);
    }

    free(triangles);
    return 0;
}
