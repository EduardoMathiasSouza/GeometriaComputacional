#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    int v1;
    int v2;
    int v3;
} Triangle;

int isEarTip(Point* polygon, int numVertices, int v1, int v2, int v3) {
    int i;
    for (i = 0; i < numVertices; i++) {
        if (i != v1 && i != v2 && i != v3) {
            float cross1 = (polygon[v2].x - polygon[v1].x) * (polygon[i].y - polygon[v2].y) -
                           (polygon[v2].y - polygon[v1].y) * (polygon[i].x - polygon[v2].x);
            float cross2 = (polygon[v3].x - polygon[v2].x) * (polygon[i].y - polygon[v3].y) -
                           (polygon[v3].y - polygon[v2].y) * (polygon[i].x - polygon[v3].x);
            float cross3 = (polygon[v1].x - polygon[v3].x) * (polygon[i].y - polygon[v1].y) -
                           (polygon[v1].y - polygon[v3].y) * (polygon[i].x - polygon[v1].x);
            
            if (cross1 >= 0 && cross2 >= 0 && cross3 >= 0)
                return 0;
        }
    }
    
    return 1;
}

Triangle* earClippingTriangulation(Point* polygon, int numVertices) {
    int i, v1, v2, v3;
    int numTriangles = numVertices - 2;
    Triangle* triangles = (Triangle*)malloc(numTriangles * sizeof(Triangle));
    
    v1 = 0;
    v2 = 1;
    v3 = 2;
    Triangle triangle = {v1, v2, v3};
    triangles[0] = triangle;
    
    for (i = 3; i < numVertices; i++) {
        v2 = v3;
        v3 = i;
        
        if (isEarTip(polygon, numVertices, v1, v2, v3)) {
            Triangle triangle = {v1, v2, v3};
            triangles[i - 2] = triangle;
        } else {
            v1 = v2;
            v2 = v3;
            v3++;
        }
    }
    
    return triangles;
}

void printTriangles(Triangle* triangles, int numTriangles) {
    printf("Triangulation:\n");
    for (int i = 0; i < numTriangles; i++) {
        printf("Triangle %d: %d %d %d\n", i+1, triangles[i].v1, triangles[i].v2, triangles[i].v3);
    }
}

int main() {
    // Define the polygon vertices in counterclockwise order
    Point polygon[] = {{1, 4}, {1, 20}, {15, 20}, {15, 4}};
    int numVertices = sizeof(polygon) / sizeof(Point);
    
    // Triangulate the polygon
    Triangle* triangles = earClippingTriangulation(polygon, numVertices);
    int numTriangles = numVertices - 2;
    
    // Print the triangles
    printTriangles(triangles, numTriangles);
    
    // Cleanup
    free(triangles);
    
    return 0;
}
