#include <stdio.h>
#include <stdlib.h>

struct Segment
{
    int index;
    int reported;
};

struct Point
{
    double x;
    double y;
    struct Segment *s;
};

struct YNode
{
    struct Point p;
    struct YNode *left;
    struct YNode *right;
};

struct Node
{
    double x;
    struct YNode *tAssoc;
    struct Node *left;
    struct Node *right;
};

struct RangeTree
{
    struct Node root;
};

struct YNode *findSplitYNode(struct YNode *t, double y0, double y1)
{
    while ((t->left && t->right) && (y1 <= t->p.y || y0 > t->p.y))
    {
        if (y1 <= t->p.y)
            t = t->right;
        else
            t = t->left;
    }

    return t;
}

void reportPoint(struct Point p)
{
    if (!p.s->reported)
    {
        printf("%d ", p.s->index + 1);
        p.s->reported = 1;
    } 
}

void printYTree(struct YNode *t, int indent)
{
    if (!t)
        return;

    reportPoint(t->p);
    printYTree(t->left, indent + 1);
    printYTree(t->right, indent + 1);
}

void queryYTree(struct YNode *t, double y0, double y1)
{
    struct YNode *split = findSplitYNode(t, y0, y1);
    if (split->p.y >= y0 && split->p.y <= y1)
        reportPoint(split->p);

    // report the subtrees that are to the left of the split vertex
    struct YNode *v = split->left;
    while (v && (v->left || v->right))
    {
        if (v->p.y >= y0 && v->p.y <= y1)
            reportPoint(v->p);

        if (y0 <= v->p.y)
        {
            printYTree(v->right, 0);
            v = v->left;
        }
        else
            v = v->right;
    }

    if (v && v->p.y >= y0 && v->p.y <= y1)
        reportPoint(v->p);

    // report the subtrees that are to the right of the split vertex
    v = split->right;
    while (v && (v->left || v->right))
    {
        if (v->p.y >= y0 && v->p.y <= y1)
            reportPoint(v->p);

        if (v->p.y < y1)
        {
            printYTree(v->left, 0);
            v = v->right;
        }
        else
            v = v->left;
    }

    if (v && v->p.y >= y0 && v->p.y <= y1)
        reportPoint(v->p);
}

// p sorted by y
struct YNode *buildTAssoc(struct Point* p, int n)
{
    if (n == 0)
        return NULL;

    int mid = n / 2;
    struct YNode *tAssoc = malloc(sizeof(struct YNode));
    tAssoc->p = p[mid];
    tAssoc->left = buildTAssoc(p, mid);
    tAssoc->right = buildTAssoc(p + mid + 1, n - mid - 1);

    return tAssoc;
}

struct Node *findSplit2DNode(struct Node *t, double x0, double x1)
{
    while ((t->left && t->right) && (x1 <= t->x || x0 > t->x))
    {
        if (x1 <= t->x)
            t = t->right;
        else
            t = t->left;
    }

    return t;
}

void query2DRangeTree(struct Node *t, double x0, double x1, double y0, double y1)
{
    struct Node *split = findSplit2DNode(t, x0, x1);
    if (split->x >= x0 && split->x <= x1)
        reportPoint(split->tAssoc->p);

    // report the subtrees that are to the left of the split vertex
    struct Node *v = split->left;
    while (v && (v->left || v->right))
    {
        if (v->x >= x0 && v->x <= x1)
            queryYTree(v->tAssoc, y0, y1);

        if (x0 <= v->x)
        {
            if (v->right)
                queryYTree(v->right->tAssoc, y0, y1);
            v = v->left;
        }
        else
            v = v->right;
    }

    if (v && v->x >= y0 && v->x <= y1)
        queryYTree(v->tAssoc, y0, y1);

    // report the subtrees that are to the right of the split vertex
    v = split->right;
    while (v && (v->left || v->right))
    {
        if (v->x >= y0 && v->x <= y1)
            queryYTree(v->tAssoc, y0, y1);

        if (v->x < y1)
        {
            if (v->left)
                queryYTree(v->left->tAssoc, y0, y1);
            v = v->right;
        }
        else
            v = v->left;
    }

    if (v && v->x >= y0 && v->x <= y1)
        queryYTree(v->tAssoc, y0, y1);
}

struct Node *build2DRangeTree(struct Point* p, int n)
{
    struct YNode *tAssoc = buildTAssoc(p, n);

    if (n == 0)
        return NULL;

    if (n == 1)
    {
        struct Node *root = malloc(sizeof(struct Node));
        root->x = p[0].x;
        root->tAssoc = tAssoc;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    int mid = n / 2;
    int leftSize = 0;
    struct Point *left = calloc(n, sizeof(struct Point));

    int rightSize = 0;
    struct Point *right = calloc(n, sizeof(struct Point));

    for (int i = 0; i < n; i++)
    {
        if (p[i].x <= p[mid].x)
            left[leftSize++] = p[i];
        else if (p[i].x > p[mid].x)
            right[rightSize++] = p[i];
    }

    struct Node *root = malloc(sizeof(struct Node));
    root->x = p[mid].x;
    root->tAssoc = tAssoc;
    root->left = build2DRangeTree(left, leftSize);
    root->right = build2DRangeTree(right, rightSize);

    free(left);
    free(right);

    return root;
}

void merge(struct Point points[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Point L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = points[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = points[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].y <= R[j].y)
            points[k++] = L[i++];
        else
            points[k++] = R[j++];
    }

    while (i < n1)
        points[k++] = L[i++];

    while (j < n2)
        points[k++] = R[j++];
}

void mergeSort(struct Point points[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(points, left, mid);
        mergeSort(points, mid + 1, right);

        // Merge the sorted halves
        merge(points, left, mid, right);
    }
}

void print2DRangeTree(struct Node *t, int level)
{
    if (t == NULL)
        return;

    print2DRangeTree(t->left, level + 1);

    for (int i = 0; i < level; i++)
        printf("   ");

    printf("%lf %lf\n", t->tAssoc->p.x, t->tAssoc->p.y);

    print2DRangeTree(t->right, level + 1);
}

int main(int argc, char** argv)
{
    int n_segments = 0, n_windows = 0;

    scanf("%d %d", &n_segments, &n_windows);
    
    struct Segment *segments = calloc(n_segments, sizeof(struct Segment));
    
    struct Point *points = calloc(2 * n_segments, sizeof(struct Point));
    
    for (int i = 0; i < n_segments; i++)
    {
        double x1, x2, y1, y2;
        scanf("%lf %lf %lf %lf",&points[2 * i].x, &points[2 * i + 1].x, &points[2 * i].y, &points[2 * i + 1].y);
        
        points[2 * i].s = &segments[i];
        points[2 * i + 1].s = &segments[i];

        segments[i].reported = 0;
        segments[i].index = i;
    }
    
    mergeSort(points, 0, 2 * n_segments - 1);
    
    struct Node *rangeTree = build2DRangeTree(points, 2 * n_segments);
    
    print2DRangeTree(rangeTree, 0);
    return 0;

    for (int i = 0; i < n_windows; i++)
    {
        double x0, x1, y0, y1;
        scanf("%lf %lf %lf %lf", &x0, &x1, &y0, &y1);

        query2DRangeTree(rangeTree, x0, x1, y0, y1);
        printf("\n");
    }

}
