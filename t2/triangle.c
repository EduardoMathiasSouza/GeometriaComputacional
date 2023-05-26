#include <stdio.h>
#include <stdlib.h>

struct point {
    int index;
    double x;
    double y;
};

struct triangle {
    struct point a;
    struct point b;
    struct point c;
};

int is_ear(struct point a, struct point b, struct point c, struct point *points, int num_points) {
    int i;
    double cross_product = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (cross_product <= 0) {
        return 0; // not a convex corner
    }
    for (i = 0; i < num_points; i++) {
        if ((points[i].x == a.x && points[i].y == a.y) || (points[i].x == b.x && points[i].y == b.y) || (points[i].x == c.x && points[i].y == c.y)) {
            continue;
        }
        double cross_product1 = (b.x - a.x) * (points[i].y - a.y) - (b.y - a.y) * (points[i].x - a.x);
        double cross_product2 = (c.x - b.x) * (points[i].y - b.y) - (c.y - b.y) * (points[i].x - b.x);
        double cross_product3 = (a.x - c.x) * (points[i].y - c.y) - (a.y - c.y) * (points[i].x - c.x);
        if (cross_product1 >= 0 && cross_product2 >= 0 && cross_product3 >= 0) {
            return 0; // point inside triangle
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
    int orientation = 0; // 0 for counterclockwise, 1 for clockwise
    double cross_product = 0;
    for (i = 0; i < num_points; i++) {
        j = (i + 1) % num_points;
        k = (i + 2) % num_points;
        cross_product = (points[j].x - points[i].x) * (points[k].y - points[i].y) - (points[j].y - points[i].y) * (points[k].x - points[i].x);
        if (cross_product != 0) {
            orientation = (cross_product > 0) ? 0 : 1;
            break;
        }
    }
    if (orientation == 1) {
        for (i = 0; i < num_points; i++) {
            j = (i + 1) % num_points;
            indices[i] = (num_points - 1) - i;
        }
    }
    while (num_points >= 3) {
        for (i = 0; i < num_points; i++) {
            j = (i + 1) % num_points;
            k = (i + 2) % num_points;
            if (is_ear(points[indices[i]], points[indices[j]], points[indices[k]], points, num_points)) {
                struct triangle t = {points[indices[i]], points[indices[j]], points[indices[k]]};
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

int main() {
    int n_points= 0;
    scanf("%d", &n_points);
    struct point *points = malloc(n_points * sizeof(struct point));
    for(int i = 0; i < n_points; i++){
        scanf("%le %le",&points[i].x, &points[i].y);
        points[i].index = i+1;
    }

    struct triangle *triangles;
    int num_triangles;
    for(int i = 0; i < n_points; i++)
        printf("%d: (%f, %f)\n", i+1, points[i].x, points[i].y);
    triangulate(points, n_points, &triangles, &num_triangles);
    printf("%d triangles:\n", num_triangles);
    int i;
    for (i = 0; i < num_triangles; i++) {
        printf("Triangle %d: (%d, %f, %f), (%d, %f, %f), (%d, %f, %f)\n", i+1,triangles[i].a.index, triangles[i].a.x, triangles[i].a.y,triangles[i].b.index, triangles[i].b.x, triangles[i].b.y,triangles[i].c.index, triangles[i].c.x, triangles[i].c.y);
    }
    free(triangles);
    return 0;
}
