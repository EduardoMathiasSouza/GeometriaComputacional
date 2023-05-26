#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    int index;
    int opposite;
    Point vertices[3];
} Triangle;

int isEar(Point a, Point b, Point c, Point* vertices, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Point p = vertices[i];
        if (p.x == a.x && p.y == a.y || p.x == b.x && p.y == b.y || p.x == c.x && p.y == c.y)
            continue;
        if (isPointInsideTriangle(p, a, b, c))
            return 0;
    }
    return 1;
}

int isPointInsideTriangle(Point p, Point a, Point b, Point c) {
    float areaABC = calculateTriangleArea(a, b, c);
    float areaPAB = calculateTriangleArea(p, a, b);
    float areaPBC = calculateTriangleArea(p, b, c);
    float areaPCA = calculateTriangleArea(p, c, a);
    return (areaABC == areaPAB + areaPBC + areaPCA);
}

float calculateTriangleArea(Point a, Point b, Point c) {
    return fabs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2);
}

void printTriangle(Triangle t) {
    printf("Triangle %d:\n", t.index);
    for (int i = 0; i < 3; i++) {
        printf("   Vertex %d: (%.2f, %.2f)\n", i, t.vertices[i].x, t.vertices[i].y);
    }
    printf("   Opposite: %d\n", t.opposite);
    printf("\n");
}

void printTriangles(Triangle* triangles, int numTriangles) {
    for (int i = 0; i < numTriangles; i++) {
        printTriangle(triangles[i]);
    }
}

void earClippingTriangulation(Point* vertices, int numVertices) {
    Triangle* triangles = malloc((numVertices - 2) * sizeof(Triangle));
    int numTriangles = 0;

    Point* remainingVertices = malloc(numVertices * sizeof(Point));
    for (int i = 0; i < numVertices; i++) {
        remainingVertices[i] = vertices[i];
    }

    int currentIndex = 0;

    while (numVertices > 3) {
        Point a = remainingVertices[currentIndex % numVertices];
        Point b = remainingVertices[(currentIndex + 1) % numVertices];
        Point c = remainingVertices[(currentIndex + 2) % numVertices];

        if (isEar(a, b, c, remainingVertices, numVertices)) {
            Triangle triangle;
            triangle.index = numTriangles;
            triangle.opposite = (currentIndex + 1) % numVertices;

            triangle.vertices[0] = a;
            triangle.vertices[1] = b;
            triangle.vertices[2] = c;

            triangles[numTriangles] = triangle;
            numTriangles++;

            int vertexIndex = (currentIndex + 1) % numVertices;

            for (int i = vertexIndex; i < numVertices - 1; i++) {
                remainingVertices[i] = remainingVertices[i + 1];
            }

            numVertices--;

            currentIndex = 0;
        } else {
            currentIndex++;
        }
    }

    Triangle lastTriangle;
    lastTriangle.index = numTriangles;
    lastTriangle.opposite = -1;
    lastTriangle.vertices[0] = remainingVertices[0];
    lastTriangle.vertices[1] = remainingVertices[1];
    lastTriangle.vertices[2] = remainingVertices[2];
    triangles[numTriangles] = lastTriangle;

    printTriangles(triangles, numTriangles + 1);

    free(triangles);
    free(remainingVertices);
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
        printf("%f %f\n", points[i].x, points[i].y);
    }
}

int main() {
    int n_points;
    scanf("%d", &n_points);
    Point *points = malloc(n_points * sizeof(Point));
    for(int i = 0; i < n_points; i++){
        scanf("%f %f",&points[i].x, &points[i].y);
    }

    qsort(points, n_points, sizeof(Point), compare);

    printPoints(points, n_points);
    earClippingTriangulation(points, n_points);
    return 0;
}
