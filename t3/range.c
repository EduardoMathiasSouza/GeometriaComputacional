#include <stdio.h>
#include <stdlib.h>

struct Segment {
    int index;
    int x1, y1;
    int x2, y2;
};

struct Node {
    struct Segment segment;
    struct Node* left;
    struct Node* right;
    struct Node* below;
};

struct Node* createNode(struct Segment segment) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->segment = segment;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->below = NULL;
    return newNode;
}

struct Node* build2DRangeTree(struct Segment segments[], int start, int end, int dimension) {
    if (start > end)
        return NULL;

    if (dimension == 0) {
        // Sort segments by x-coordinate
        int i, j;
        for (i = start + 1; i <= end; i++) {
            struct Segment temp = segments[i];
            j = i - 1;
            while (j >= start && segments[j].x1 > temp.x1) {
                segments[j + 1] = segments[j];
                j--;
            }
            segments[j + 1] = temp;
        }
    } else {
        // Sort segments by y-coordinate
        int i, j;
        for (i = start + 1; i <= end; i++) {
            struct Segment temp = segments[i];
            j = i - 1;
            while (j >= start && segments[j].y1 > temp.y1) {
                segments[j + 1] = segments[j];
                j--;
            }
            segments[j + 1] = temp;
        }
    }

    int mid = (start + end) / 2;
    struct Node* root = createNode(segments[mid]);

    root->left = build2DRangeTree(segments, start, mid - 1, 1 - dimension);
    root->right = build2DRangeTree(segments, mid + 1, end, 1 - dimension);

    return root;
}

void queryRangeTree(struct Node* root, struct Segment rect, int dimension) {
    if (root == NULL)
        return;

    // Check if the segment intersects with the rectangle
    if (root->segment.x1 <= rect.x2 && root->segment.x2 >= rect.x1 &&
        root->segment.y1 <= rect.y2 && root->segment.y2 >= rect.y1) {
        printf("%d ", root->segment.index);
    }

    if (dimension == 0) {
        // Recurse on the left and right subtrees if they can intersect with the rectangle in the x-dimension
        if (root->left != NULL && rect.x1 <= root->segment.x1)
            queryRangeTree(root->left, rect, 1 - dimension);

        if (root->right != NULL && rect.x2 >= root->segment.x1)
            queryRangeTree(root->right, rect, 1 - dimension);
    } else {
        // Recurse on the below subtree if it can intersect with the rectangle in the y-dimension
        if (root->below != NULL && rect.y1 <= root->segment.y1)
            queryRangeTree(root->below, rect, 1 - dimension);
    }
}

void insertSegment(struct Node* root, struct Segment segment, int dimension) {
    if (root == NULL)
        return;

    if (dimension == 0) {
        // Insert segment into the x-dimension subtree
        if (segment.x1 <= root->segment.x1) {
            if (root->left == NULL)
                root->left = createNode(segment);
            else
                insertSegment(root->left, segment, 1 - dimension);
        } else {
            if (root->right == NULL)
                root->right = createNode(segment);
            else
                insertSegment(root->right, segment, 1 - dimension);
        }
    } else {
        // Insert segment into the y-dimension subtree
        if (segment.y1 <= root->segment.y1) {
            if (root->below == NULL)
                root->below = createNode(segment);
            else
                insertSegment(root->below, segment, 1 - dimension);
        }
    }
}

int main() {
    int n_segments = 0, n_windows = 0;

    scanf("%d %d", &n_segments, &n_windows);

    struct Segment *segments = malloc(n_segments * sizeof(struct Segment));
    struct Segment *windows = malloc(n_windows * sizeof(struct Segment));

    for(int i = 0; i < n_segments; i++){
        scanf("%d %d %d %d",&segments[i].x1, &segments[i].x2, &segments[i].y1, &segments[i].y2);
        segments[i].index = i+1;
    }

    for(int i = 0; i < n_windows; i++){
        scanf("%d %d %d %d",&windows[i].x1, &windows[i].x2, &windows[i].y1, &windows[i].y2);
        windows[i].index = i+1;
    }

    // Array of segments
    //struct Segment segments[] = {{0, 1, 0, 10},{10,0,20,0},{1,1,10,10}};
    // Construct the 2D range tree
    //int n = sizeof(segments) / sizeof(segments[0]);
    struct Node* root = build2DRangeTree(segments, 0, n_segments - 1, 0);

    // Perform a range query on the tree for the rectangle [3, 8]x[2, 7]
    //struct Segment queryRect = {8,8,12,12};
    for (int i = 0; i < n_windows; i++){
        queryRangeTree(root, windows[i], 0);
        printf("\n");
    }

    return 0;
}
