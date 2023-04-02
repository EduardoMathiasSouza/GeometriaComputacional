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


int main() {
  Point points1[] = {{2, 6},{2,1},{15,2},{20,1},{20,6}};
  Polygon polygon1 = {points1, 4};

  if(is_polygon_simple(polygon1)) {
    printf("simples");
    if(isConvex(polygon1)) {
        printf(" e convexo");
    } else {
        printf(" e nao convexo");
    }
  }
  else {
    printf("Polygon is not simple");
  } 
  return 0;
}

