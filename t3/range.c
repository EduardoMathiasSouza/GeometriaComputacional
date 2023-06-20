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
        printf("Segment: (%d, %d) - (%d, %d)\n", root->segment.x1, root->segment.y1, root->segment.x2, root->segment.y2);
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

// Structure to represent a node in the segment tree
typedef struct {
    int count;  // Number of intervals in the subtree
    struct Segment* segment; // Array of intervals in the subtree
} Node;

// Function to build the segment tree
Node* buildSegmentTree(struct Segment* segments, int start, int end) {
    if (start > end)
        return NULL;

    // Create a new node for the current segment range
    Node* node = (Node*)malloc(sizeof(Node));
    if (start == end) {
        node->count = 1;
        node->segment = &segments[start];
    } else {
        int mid = (start + end) / 2;
        Node* leftChild = buildSegmentTree(segments, start, mid);
        Node* rightChild = buildSegmentTree(segments, mid + 1, end);
        node->count = leftChild->count + rightChild->count;
        node->segment = (struct Segment*)malloc(node->count * sizeof(struct Segment));
        int i, j, k;
        i = j = k = 0;
        while (i < leftChild->count && j < rightChild->count) {
            if (leftChild->segment[i].x1 <= rightChild->segment[j].x1) {
                node->segment[k] = leftChild->segment[i];
                i++;
            } else {
                node->segment[k] = rightChild->segment[j];
                j++;
            }
            k++;
        }
        while (i < leftChild->count) {
            node->segment[k] = leftChild->segment[i];
            i++;
            k++;
        }
        while (j < rightChild->count) {
            node->segment[k] = rightChild->segment[j];
            j++;
            k++;
        }
        free(leftChild->segment);
        free(rightChild->segment);
        free(leftChild);
        free(rightChild);
    }
    return node;
}

// Function to query the segment tree and find intervals containing the query point
void querySegmentTree(Node* node, int queryX, int queryY) {
    if (node == NULL)
        return;

    int i;
    for (i = 0; i < node->count; i++) {
        struct Segment segment = node->segment[i];
        if (segment.x1 <= queryX && queryX <= segment.x2 &&
            segment.y1 <= queryY && queryY <= segment.y2) {
            // The query point lies inside this interval
            printf("Segment (%d,%d) to (%d,%d) contains the query point.\n",
                   segment.x1, segment.y1, segment.x2, segment.y2);
        }
    }

    // Recurse on the left or right child based on the query point's x-coordinate
    if (queryX < node->segment[0].x1)
        querySegmentTree(node->left, queryX, queryY);
    else
        querySegmentTree(node->right, queryX, queryY);
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
        printf("asdfasdfasdf\n");
        queryRangeTree(root, windows[i], 0);
    }

    return 0;
}
