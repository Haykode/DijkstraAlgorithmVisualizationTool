/*
 * Copyright (c) 2025, Xedokyah
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE in the project root for license terms.
 *
 * dijkstra.cpp
 * DijkstraDemo
 *
 * Created on 2024/11/28
 */

#include "dijkstra_demo.h"

int dijkstra(int start, int end, int* predecessor) {
    initHeap(graph.size);
    drawCodeArea(1);
    pauseOrContinue(settings.animationSpeed);
    positions.pot[start].dist = 0;
    drawCodeArea(2);
    pauseOrContinue(settings.animationSpeed);
    drawCodeArea(3);
    push({ start, 0 });
    drawStatusTable();
    pauseOrContinue(settings.animationSpeed);
    drawHeap(-1, -1, 2);
    while (!isHeapEmpty()) {
        currNode = -1;
        updatingNode = -1;
        drawGraph(-1, -1);
        drawAdjTable();
        drawStatusTable();
        drawCodeArea(4);
        pauseOrContinue(settings.animationSpeed);
        drawCodeArea(5);
        int u = top().u;
        pop();
        currNode = u;
        drawGraph(u, -1);
        drawAdjTable();
        drawStatusTable();
        pauseOrContinue(settings.animationSpeed);
        drawHeap(-1, -1, 2);
        if (positions.pot[u].visited == 2) {
            drawCodeArea(6);
            pauseOrContinue(settings.animationSpeed);
            continue;
        }
        drawCodeArea(6);
        pauseOrContinue(settings.animationSpeed);
        positions.pot[u].visited = 2;
        drawCodeArea(7);
        pauseOrContinue(settings.animationSpeed);
        Node* curr = graph.adj[u];
        drawCodeArea(8);
        pauseOrContinue(settings.animationSpeed);
        while (curr) {
            drawCodeArea(9);
            pauseOrContinue(settings.animationSpeed);
            int v = curr->v, w = curr->weight;
            updatingNode = v;
            drawCodeArea(10);
            drawGraph(u, v);
            drawAdjTable();
            drawStatusTable();
            pauseOrContinue(settings.animationSpeed);
            if (positions.pot[v].dist > positions.pot[u].dist + w) {
                drawCodeArea(11);
                pauseOrContinue(settings.animationSpeed);
                positions.pot[v].dist = positions.pot[u].dist + w;
                drawCodeArea(12);
                drawStatusTable();
                pauseOrContinue(settings.animationSpeed);
                drawCodeArea(13);
                push({ v, positions.pot[v].dist });
                predecessor[v] = u;
                positions.pot[v].visited = 1;
                drawGraph(u, v);
                pauseOrContinue(settings.animationSpeed);
                drawHeap(-1, -1, 2);
            }
            drawCodeArea(11);
            pauseOrContinue(settings.animationSpeed);
            curr = curr->next;
            drawCodeArea(15);
            pauseOrContinue(settings.animationSpeed);
        }
        drawCodeArea(9);
        pauseOrContinue(settings.animationSpeed);
    }
    drawCodeArea(4);
    pauseOrContinue(settings.animationSpeed);
    clearHeap();
    drawCodeArea(-1);
    drawHeap(-1, -1, 2);
    currNode = -1;
    updatingNode = -1;
    drawGraph(-1, -1);
    drawStatusTable();
    drawAdjTable();
    return positions.pot[end].dist;
}

void findShortestPath(int start, int end) {
    int* predecessor = (int*)malloc(sizeof(int) * (graph.size + 1));
    if (!predecessor) {
        printf("The memory is not enough!\a");
        exit(0);
    }
    int shortestPathWeights = dijkstra(start, end, predecessor);
    int curr = end;
    while (curr != start && shortestPathWeights != INT_MAX) {
        int prev = predecessor[curr];
        Node* tmp = graph.adj[prev];
        int edgeWeight = 0;
        while (tmp) {
            if (tmp->v == curr) {
                edgeWeight = tmp->weight;
                break;
            }
            tmp = tmp->next;
        }
        drawGraphArrow(positions.pot[prev].x, positions.pot[prev].y,
            positions.pot[curr].x, positions.pot[curr].y,
            settings.shortestPathColor, 5, edgeWeight, true);
        pauseOrContinue(settings.shortestPathSpeed);
        curr = prev;
    }
    free(predecessor);
}
