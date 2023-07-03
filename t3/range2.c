#include <stdio.h>
#include <stdlib.h>

struct Point
{
    double x;
    double y;
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

void printYTree(struct YNode *t, int indent)
{
    if (!t)
        return;

    for (int i = 0; i < indent; i++) printf("  ");
    printf("%lf %lf\n", t->p.x, t->p.y);
    printYTree(t->left, indent + 1);
    printYTree(t->right, indent + 1);
}

void queryYTree(struct YNode *t, double y0, double y1)
{
    struct YNode *split = findSplitYNode(t, y0, y1);
    if (split->p.y >= y0 && split->p.y <= y1)
        printf("%lf %lf\n", split->p.x, split->p.y);

    // report the subtrees that are to the left of the split vertex
    struct YNode *v = split->left;
    while (v && (v->left || v->right))
    {
        if (v->p.y >= y0 && v->p.y <= y1)
            printf("%lf %lf\n", v->p.x, v->p.y);

        if (y0 <= v->p.y)
        {
            printYTree(v->right, 0);
            v = v->left;
        }
        else
            v = v->right;
    }

    if (v && v->p.y >= y0 && v->p.y <= y1)
        printf("%lf %lf\n", v->p.x, v->p.y);

    // report the subtrees that are to the right of the split vertex
    v = split->right;
    while (v && (v->left || v->right))
    {
        if (v->p.y >= y0 && v->p.y <= y1)
            printf("%lf %lf\n", v->p.x, v->p.y);

        if (v->p.y < y1)
        {
            printYTree(v->left, 0);
            v = v->right;
        }
        else
            v = v->left;
    }

    if (v && v->p.y >= y0 && v->p.y <= y1)
        printf("%lf %lf\n", v->p.x, v->p.y);
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
        queryYTree(split->tAssoc, y0, y1);

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
        if (p[i].x < p[mid].x)
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

int main(int argc, char** argv)
{
    struct Point p[] = {
        { 2, 1 },
        { 5, 2 },
        { 9, 4 },
        { 4, 5 },
        { 8, 8 },
        { 7, 10 }
    };

    struct Node *rangeTree = build2DRangeTree(p, 6);
    query2DRangeTree(rangeTree, 3.5, 8.5, 3.5, 8.5);
}
