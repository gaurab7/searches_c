#include <stdio.h>

#define MAX 10
#define INF 9999

int n=5;                          // Number of nodes
int adj[MAX][MAX] = {
    {0,0,0,1,0},
    {1,0,1,0,0},
    {0,0,0,0,1},
    {0,1,1,0,0},
    {0,0,0,0,0}
};              // Adjacency matrix (0 or 1)
int cost[MAX][MAX] = {
    {0,1,2,0,0},
    {1,0,0,3,0},
    {2,0,0,1,4},
    {0,3,1,0,0},
    {0,0,4,0,0}
};     // Cost between nodes
int heuristic[MAX];             // Heuristic values
int visited[MAX];               // Visited array

void aStar(int start, int goal) {
    int current = start;
    int g[MAX];                 // g[n]: cost from start to node n

    // Initialize
    for (int i = 0; i < n; i++) {
        g[i] = INF;
        visited[i] = 0;
    }

    g[start] = 0;
    printf("Path: %d", start);

    while (current != goal) {
        visited[current] = 1;
        int next = -1;
        int minF = INF;

        for (int i = 0; i < n; i++) {
            if (adj[current][i] && !visited[i]) {
                int newG = g[current] + cost[current][i];
                int f = newG + heuristic[i];

                if (f < minF) {
                    minF = f;
                    next = i;
                    g[i] = newG;
                }
            }
        }

        if (next == -1) {
            printf("\nNo path to goal found.\n");
            return;
        }

        printf(" -> %d", next);
        current = next;
    }

    printf("\nPath Cost: %d\n", g[goal]);
}

int main() {
    int start, goal;

    printf("Enter heuristic values:\n");
    for (int i = 0; i < 5; i++) {
        printf("Heuristic for node %d: ", i);
        scanf("%d", &heuristic[i]);
    }

    printf("Enter start node: ");
    scanf("%d", &start);
    printf("Enter goal node: ");
    scanf("%d", &goal);

    aStar(start, goal);

    return 0;
}