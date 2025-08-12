#include <stdio.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

typedef struct { int r, c; } Point;

int grid[ROW][COL] = {
    {0,0,0,1,0},
    {1,0,1,0,0},
    {0,0,0,0,1},
    {0,1,1,0,0},
    {0,0,0,0,0}
};

int visited[ROW][COL];
Point parent[ROW][COL];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int inBounds(int r, int c) {
    return (r >= 0 && r < ROW && c >= 0 && c < COL);
}

int dfsUtil(Point cur, Point goal) {
    visited[cur.r][cur.c] = 1;
    if(cur.r == goal.r && cur.c == goal.c) return 1;

    for(int i=0;i<4;i++) {
        int nr = cur.r + dr[i];
        int nc = cur.c + dc[i];
        if(inBounds(nr, nc) && !visited[nr][nc] && grid[nr][nc] == 0) {
            parent[nr][nc] = cur;
            if(dfsUtil((Point){nr, nc}, goal)) return 1;
        }
    }
    return 0;
}

void printPath(Point start, Point goal) {
    if(!visited[goal.r][goal.c]) {
        printf("No path found!\n");
        return;
    }
    Point path[ROW*COL];
    int length = 0;
    Point cur = goal;
    while(!(cur.r == start.r && cur.c == start.c)) {
        path[length++] = cur;
        cur = parent[cur.r][cur.c];
    }
    path[length++] = start;

    printf("Path (DFS):\n");
    for(int i=length-1; i>=0; i--) {
        printf("(%d,%d) ", path[i].r, path[i].c);
    }
    printf("\nPath Cost: %d\n", length-1);
}

int main() {
    Point start, goal;
    printf("Enter start (row col): ");
    scanf("%d %d", &start.r, &start.c);
    printf("Enter goal (row col): ");
    scanf("%d %d", &goal.r, &goal.c);

    if(!inBounds(start.r, start.c) || !inBounds(goal.r, goal.c) ||
       grid[start.r][start.c] == 1 || grid[goal.r][goal.c] == 1) {
        printf("Invalid start or goal!\n");
        return 0;
    }

    dfsUtil(start, goal);
    printPath(start, goal);
    return 0;
}
