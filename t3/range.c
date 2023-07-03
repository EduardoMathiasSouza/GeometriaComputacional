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

void merge(struct Segment segments[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Segment L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = segments[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = segments[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].x1 <= R[j].x1)
            segments[k++] = L[i++];
        else
            segments[k++] = R[j++];
    }

    while (i < n1)
        segments[k++] = L[i++];

    while (j < n2)
        segments[k++] = R[j++];
}

void mergeSort(struct Segment segments[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(segments, left, mid);
        mergeSort(segments, mid + 1, right);

        // Merge the sorted halves
        merge(segments, left, mid, right);
    }
}

struct Node* build2DRangeTree(struct Segment segments[], int start, int end, int dimension) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = createNode(segments[mid]);

    root->left = build2DRangeTree(segments, start, mid - 1, 1 - dimension);
    root->right = build2DRangeTree(segments, mid + 1, end, 1 - dimension);

    return root;
}


void queryRangeTree(struct Node* root, struct Segment rect, int dimension) {
    if (root == NULL)
        return;

    // Check if the segment intersects with the rectangle using interval overlap
    if (dimension == 0) {
        // Check if the x-interval of the segment overlaps with the x-interval of the rectangle
        if (root->segment.x1 <= rect.x2 && root->segment.x2 >= rect.x1) {
            // Check if the y-interval of the segment overlaps with the y-interval of the rectangle
            if (root->segment.y1 <= rect.y2 && root->segment.y2 >= rect.y1) {
                printf("%d ", root->segment.index);
            }
        }
    } else {
        // Check if the y-interval of the segment overlaps with the y-interval of the rectangle
        if (root->segment.y1 <= rect.y2 && root->segment.y2 >= rect.y1) {
            // Check if the x-interval of the segment overlaps with the x-interval of the rectangle
            if (root->segment.x1 <= rect.x2 && root->segment.x2 >= rect.x1) {
                printf("%d ", root->segment.index);
            }
        }
    }

    // Recurse on the left and right subtrees if they can intersect with the rectangle in the current dimension
    if (root->left != NULL && rect.x1 <= root->segment.x1 && rect.x2 >= root->segment.x1)
        queryRangeTree(root->left, rect, 1 - dimension);

    if (root->right != NULL && rect.x1 <= root->segment.x2 && rect.x2 >= root->segment.x2)
        queryRangeTree(root->right, rect, 1 - dimension);
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
    mergeSort(segments, 0, n_segments - 1);
    struct Node* root = build2DRangeTree(segments, 0, n_segments - 1, 0);

    for (int i = 0; i < n_windows; i++){
        queryRangeTree(root, windows[i], 0);
        printf("\n");
    }

    return 0;
}
