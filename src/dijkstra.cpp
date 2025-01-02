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
    drawCode(1);
    pauseOrContinue(settings.animationSpeed);
    positions.pot[start].dist = 0;
    drawCode(2);
    pauseOrContinue(settings.animationSpeed);
    push({ start, 0 });
    drawCode(3);
    drawStatusTable();
    pauseOrContinue(settings.animationSpeed);
    while (!isHeapEmpty()) {
        drawCode(4);
        pauseOrContinue(settings.animationSpeed);
        int u = top().u;
        pop();
        currNode = u;
        updatingNode = -1;
        drawCode(5);
        drawGraph(u, -1);
        drawAdjTable();
        drawStatusTable();
        pauseOrContinue(settings.animationSpeed);
        if (positions.pot[u].visited == 2) {
            drawCode(6);
            pauseOrContinue(settings.animationSpeed);
            continue;
        }
        drawCode(6);
        pauseOrContinue(settings.animationSpeed);
        positions.pot[u].visited = 2;
        drawCode(7);
        drawAdjTable();
        drawStatusTable();
        pauseOrContinue(settings.animationSpeed);
        Node* curr = graph.adj[u];
        drawCode(8);
        pauseOrContinue(settings.animationSpeed);
        while (curr) {
            drawCode(9);
            pauseOrContinue(settings.animationSpeed);
            int v = curr->v, w = curr->weight;
            updatingNode = v;
            drawCode(10);
            drawGraph(u, v);
            drawStatusTable();
            drawAdjTable();
            pauseOrContinue(settings.animationSpeed);
            if (positions.pot[v].dist > positions.pot[u].dist + w) {
                drawCode(11);
                pauseOrContinue(settings.animationSpeed);
                positions.pot[v].dist = positions.pot[u].dist + w;
                drawCode(12);
                drawStatusTable();
                pauseOrContinue(settings.animationSpeed);
                push({ v, positions.pot[v].dist });
                predecessor[v] = u;
                positions.pot[v].visited = 1;
                drawCode(13);
                drawGraph(u, v);
                drawStatusTable();
                drawAdjTable();
                pauseOrContinue(settings.animationSpeed);
            }
            drawCode(11);
            pauseOrContinue(settings.animationSpeed);
            curr = curr->next;
            drawCode(15);
            pauseOrContinue(settings.animationSpeed);
        }
        drawCode(9);
        pauseOrContinue(settings.animationSpeed);
    }
    drawCode(4);
    pauseOrContinue(settings.animationSpeed);
    clearHeap();
    drawCode(-1);
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
        Sleep(settings.shortestPathSpeed);
        curr = prev;
    }
    free(predecessor);
}
