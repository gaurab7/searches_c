#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int n=5;                 // number of nodes
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
};     // Cost between nodes    // cost matrix (edge weights)
int visited[MAX];      // visited array
int heuristic[MAX];    // heuristic values

// Function to find the best next node based on minimum heuristic value
int getBestNode(int current) {
    int min = 9999;
    int bestNode = -1;

    for (int i = 0; i < n; i++) {
        if (adj[current][i] == 1 && !visited[i]) { // edge exists
            if (heuristic[i] < min) {
                min = heuristic[i];
                bestNode = i;
            }
        }
    }

    return bestNode;
}

void greedyBestFirstSearch(int start, int goal) {
    int current = start;
    int totalCost = 0;

    visited[current] = 1;
    printf("Greedy Best First Search Path: %d ", current);

    while (current != goal) {
        int next = getBestNode(current);

        if (next == -1) {
            printf("\nNo path found to the goal.\n");
            return;
        }

        totalCost += cost[current][next]; // add from cost matrix
        visited[next] = 1;
        printf("-> %d ", next);
        current = next;
    }

    printf("\nPath Cost: %d\n", totalCost);
}

int main() {
    int start, goal;

    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        printf("Heuristic for node %d: ", i);
        scanf("%d", &heuristic[i]);
    }

    printf("Enter the start node (0 to %d): ", n - 1);
    scanf("%d", &start);
    printf("Enter the goal node (0 to %d): ", n - 1);
    scanf("%d", &goal);

    // Initialize visited array
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    greedyBestFirstSearch(start, goal);

    return 0;
}
