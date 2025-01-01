/*
 * graph.cpp
 * DijkstraDemo
 *
 * Created on 2024/11/30
 */

#include "dijkstra_demo.h"

struct Graph graph;
struct Points positions;

void addEdge(int u, int v, int weight) {
    Node* curr = graph.adj[u];
    while (curr && curr->v != v) {
        curr = curr->next;
    }
    if (!curr) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) {
            printf("The memory is not enough!\a");
            exit(0);
        }
        newNode->v = v;
        newNode->weight = weight;
        newNode->next = graph.adj[u];
        graph.adj[u] = newNode;
    }
    else if (curr->weight > weight) {
        curr->weight = weight;
    }
}

void generateGraph() {
    graph.size = (settings.randomNodeFlag == 1) ? (1 + rand() % settings.nodeCount) : settings.nodeCount;
    graph.adj = (Node**)malloc(sizeof(Node*) * (graph.size + 1));
    if (!graph.adj) {
        printf("The memory is not enough!\a");
        exit(0);
    }
    for (int i = 0; i < graph.size; ++i) {
        graph.adj[i] = NULL;
    }
    for (int u = 0; u < graph.size; ++u) {
        int edgesSize = (settings.randomEdgeFlag == 1) ? (1 + rand() % settings.edgeCount) : settings.edgeCount;
        for (int j = 0; j < edgesSize; ++j) {
            int v = rand() % graph.size;
            int w = rand() % settings.maxWeight + 1;
            if (v != u)
                addEdge(u, v, w);
        }
    }
}

void readGraphFromFile() {
    char fullPath[64] = "testSamples/";
    strcat_s(fullPath, sizeof(fullPath), settings.dataFilePath);
    FILE* file;
    errno_t err = fopen_s(&file, fullPath, "r");
    if (err != 0 || file == NULL) {
        perror("Can't open data file!\a");
        exit(1);
    }
    int nodesCount, edgesCount;
    if (fscanf_s(file, "%d %d", &nodesCount, &edgesCount) != 2) {
        fprintf(stderr, "Error reading node count and edge count from file\n\a");
        fclose(file);
        exit(1);
    }
    if (nodesCount <= 0 || nodesCount > 20) {
        fprintf(stderr, "Error: nodeCount must be in range [1, 20], got %d\n\a", nodesCount);
        fclose(file);
        exit(1);
    }
    graph.size = nodesCount;
    graph.adj = (Node**)malloc(sizeof(Node*) * (graph.size + 1));
    if (!graph.adj) {
        printf("The memory is not enough!\a");
        exit(0);
    }
    for (int i = 0; i < graph.size; ++i) {
        graph.adj[i] = NULL;
    }
    while (edgesCount--) {
        int u, v, w;
        if (fscanf_s(file, "%d %d %d", &u, &v, &w) != 3) {
            fprintf(stderr, "Error reading edge data from file\n\a");
            fclose(file);
            exit(1);
        }
        if ((u < 0 || u >= nodesCount) || (v < 0 || v >= nodesCount)) {
            fprintf(stderr, "Error: Node indices must be in range [0, %d). Invalid edge: %d -> %d\n\a", nodesCount, u, v);
            fclose(file);
            exit(1);
        }
        addEdge(u, v, w);
    }
    fclose(file);
}

void clearGraph() {
    for (int i = 0; i < graph.size; ++i) {
        Node* curr = graph.adj[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph.adj);
    free(positions.pot);
    graph.adj = NULL;
    positions.pot = NULL;
}

void generateNodePositions() {
    positions.size = graph.size;
    positions.pot = (Point*)malloc(sizeof(Point) * positions.size);
    if (!positions.pot) {
        printf("The memory is not enough!\a");
        exit(0);
    }
    int centerX = 300, centerY = 350;
    int radius = 250;
    for (int i = 0; i < positions.size; ++i) {
        double angle = 2.0 * 3.1415926 * i / positions.size;
        int offsetX = rand() % 20 - 20;
        int offsetY = rand() % 20 - 20;
        positions.pot[i].x = centerX + (int)(radius * cos(angle)) + offsetX;
        positions.pot[i].y = centerY + (int)(radius * sin(angle)) + offsetY;
        positions.pot[i].dist = INT_MAX;
        positions.pot[i].visited = 0;
    }
}