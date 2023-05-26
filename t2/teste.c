#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int index;
    int vertex1;
    int vertex2;
    int vertex3;
    int opposite;
} Triangle;

float crossProduct(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

int isPointInsideTriangle(Point p, Point p1, Point p2, Point p3) {
    float d1, d2, d3;
    int hasNeg, hasPos;

    d1 = crossProduct(p, p1, p2);
    d2 = crossProduct(p, p2, p3);
    d3 = crossProduct(p, p3, p1);

    hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(hasNeg && hasPos);
}

void printTriangle(Point* points, Triangle triangle) {
    printf("%d %d %d ",triangle.vertex1, triangle.vertex2, triangle.vertex3);
}

void printOppositeTriangle(Triangle* triangles, int numTriangles, int vertexIndex) {
    for (int i = 0; i < numTriangles; i++) {
        Triangle currentTriangle = triangles[i];
        if (currentTriangle.vertex1 != vertexIndex && currentTriangle.vertex2 != vertexIndex && currentTriangle.vertex3 != vertexIndex &&
            currentTriangle.opposite != 0) {
            printf("%d ", currentTriangle.opposite);
            return;
        }
    }
    printf("0 ");
}

void triangulate(Point* points, int numPoints) {
    if (numPoints < 3)
        return;

    Triangle* triangles = malloc((numPoints - 2) * sizeof(Triangle));
    int numTriangles = numPoints - 2;

    for (int i = 0; i < numTriangles; i++) {
        triangles[i].index = i + 1;
        triangles[i].vertex1 = i + 1;
        triangles[i].vertex2 = i + 2;
        triangles[i].vertex3 = i + 3;
        triangles[i].opposite = 0;
    }

    int count = numTriangles;
    printf("%d\n", numTriangles);
    for (int i = 0; i < numTriangles; i++) {
        Triangle currentTriangle = triangles[i];
        Point p1 = points[currentTriangle.vertex1 - 1];
        Point p2 = points[currentTriangle.vertex2 - 1];
        Point p3 = points[currentTriangle.vertex3 - 1];

        for (int j = 0; j < numTriangles; j++) {
            if (j != i) {
                Triangle otherTriangle = triangles[j];
                Point q1 = points[otherTriangle.vertex1 - 1];
                Point q2 = points[otherTriangle.vertex2 - 1];
                Point q3 = points[otherTriangle.vertex3 - 1];

                if (isPointInsideTriangle(p1, q1, q2, q3) &&
                    isPointInsideTriangle(p2, q1, q2, q3) &&
                    isPointInsideTriangle(p3, q1, q2, q3)) {
                    triangles[i].opposite = otherTriangle.index;
                    break;
                }
            }
        }

        printTriangle(points, currentTriangle);
        printOppositeTriangle(triangles, numTriangles, currentTriangle.vertex1);
        printOppositeTriangle(triangles, numTriangles, currentTriangle.vertex2);
        printOppositeTriangle(triangles, numTriangles, currentTriangle.vertex3);
        printf("\n");
    }

    free(triangles);
}

int compare(const void* a, const void* b) {
    Point p0 = *((Point*)a);
    Point p1 = *((Point*)b);
    int cross = (p1.x * p0.y) - (p0.x * p1.y);
    if (cross > 0)
        return -1;
    else if (cross < 0)
        return 1;
    else
        return 0;
}

void printPoints(Point* points, int n_points) {
    for (int i = 0; i < n_points; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }
}

int main() {
    int n_points;
    scanf("%d", &n_points);
    Point *points = malloc(n_points * sizeof(Point));
    for(int i = 0; i < n_points; i++){
        scanf("%d %d",&points[i].x, &points[i].y);
    }

    qsort(points, n_points, sizeof(Point), compare);

    printPoints(points, n_points);

    triangulate(points, n_points);
    return 0;
}
