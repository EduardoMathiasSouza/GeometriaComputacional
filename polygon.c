#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x;
  double y;
} Point;

typedef struct {
  Point* points;
  int num_points;
} Polygon;

int do_edges_intersect(Point a1, Point a2, Point b1, Point b2) {
  double d1 = ((b2.x-b1.x)*(a1.y-b1.y)-(b2.y-b1.y)*(a1.x-b1.x));
  double d2 = ((b2.x-b1.x)*(a2.y-b1.y)-(b2.y-b1.y)*(a2.x-b1.x));
  double d3 = ((a2.x-a1.x)*(b1.y-a1.y)-(a2.y-a1.y)*(b1.x-a1.x));
  double d4 = ((a2.x-a1.x)*(b2.y-a1.y)-(a2.y-a1.y)*(b2.x-a1.x));
  return (d1 * d2 < 0) && (d3 * d4 < 0);
}

int is_polygon_simple(Polygon p) {
  for (int i = 0; i < p.num_points; i++) {
    Point a1 = p.points[i];
    Point a2 = p.points[(i+1)%p.num_points];
    for (int j = i+2; j < p.num_points; j++) {
      Point b1 = p.points[j];
      Point b2 = p.points[(j+1)%p.num_points];
      if (do_edges_intersect(a1, a2, b1, b2)) {
        return 0;
      }
    }
  }
  return 1;
}

double crossProduct(Point p1, Point p2, Point p3) {
    double x1 = p2.x - p1.x;
    double y1 = p2.y - p1.y;
    double x2 = p3.x - p2.x;
    double y2 = p3.y - p2.y;
    return x1 * y2 - x2 * y1;
}


int isConvex(Polygon p) {
    int i, j, k;
    int flag = 0;
    for (i = 0; i < p.num_points; i++) {
        j = (i + 1) % p.num_points;
        k = (i + 2) % p.num_points;
        double cross_product = crossProduct(p.points[i], p.points[j], p.points[k]);
        if (cross_product < 0) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        return 0; // polygon is not convex
    } else {
        return 1; // polygon is convex
    }
}

int isInside(Polygon p, Point point) {
    int i, j, count = 0;
    for (i = 0, j = p.num_points - 1; i < p.num_points; j = i++) {
        if (((p.points[i].y > point.y) != (p.points[j].y > point.y)) &&
            (point.x < (p.points[j].x - p.points[i].x) * (point.y - p.points[i].y) / (p.points[j].y - p.points[i].y) + p.points[i].x)) {
            count++;
        }
    }
    return (count % 2 == 1);
}


int main() {
  int n_polygons= 0;
  int n_points= 0;
  int n_vertices=0;
  scanf("%d %d", &n_polygons, &n_points);
  printf("%d %d\n", n_polygons, n_points);

  //Verifica se o polígono é simples e convexo
  Polygon *polygons = malloc(n_polygons * sizeof(Polygon));

  for(int i = 0; i < n_polygons; i++){
    scanf("%d", &n_vertices);
    printf("%d\n", n_vertices);
    Point *points = malloc(n_vertices * sizeof(Point));
    for(int j = 0; j < n_vertices; j++){
      scanf("%le %le", &points[j].x, &points[j].y);
      printf("%le %le\n", points[j].x, points[j].y);
    }
    polygons[i].points = points;
    polygons[i].num_points = n_vertices;
  }
  for(int i = 0; i < n_polygons; i++){
    printf("%d", i+1);
    if(is_polygon_simple(polygons[i])) {
      printf(" simples");
      if(isConvex(polygons[i])) {
          printf(" e convexo\n");
      } else {
          printf(" e nao convexo\n");
      }
    }
    else {
      printf("nao simples\n");
    }
  }

  //Verifica se um ponto está dentro do polígono
  Point *points_avulsos = malloc(n_points * sizeof(Point));
  for(int i = 0; i < n_points; i++){
    scanf("%le %le", &points_avulsos[i].x, &points_avulsos[i].y);
    printf("%d:", i+1);
    for(int j = 0; j < n_polygons; j++){
      if(isInside(polygons[j], points_avulsos[i])) {
        printf("%d ", j+1);
      }
    }
    printf("\n");
  }
  return 0;
}

