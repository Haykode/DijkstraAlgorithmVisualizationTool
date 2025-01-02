/*
 * Copyright (c) 2025, Xedokyah
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE in the project root for license terms.
 *
 * dijkstra_demo.h
 * DijkstraDemo
 *
 * Created on 2024/11/28
 */

#ifndef DIJKSTRA_DEMO_H
#define DIJKSTRA_DEMO_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include <ctime>
#include <cmath>
#include <graphics.h>
// Node
struct Node {
    int v, weight;
    Node* next;
};

// Position
struct Point {
    int x, y;
    int dist;
    int visited;
};

struct Points {
    Point* pot;
    int size;
};
extern struct Points positions;

// Graph
struct Graph {
    Node** adj;
    int size;
};

extern struct Graph graph;
void generateNodePositions();
void generateGraph();
void clearGraph();

// Heap
struct HeapNode {
    int u, dist;
};

struct Heap {
    HeapNode* nodes;
    int size;
};

extern struct Heap heap;
void initHeap(int n);
int isHeapEmpty();
void push(HeapNode node);
HeapNode top();
void pop();
void clearHeap();

// Configration
struct Settings {
    int animationSpeed;
    int dataSource;
    char dataFilePath[64];
    int nodeCount;
    int randomNodeFlag;
    int edgeCount;
    int randomEdgeFlag;
    int maxWeight;
    int windowScale;
    int clickDelay;
    int shortestPathSpeed;
    COLORREF buttonColor;
    COLORREF bgColor;
    COLORREF textColor;
    COLORREF nodeColor;
    COLORREF startNodeColor;
    COLORREF endNodeColor;
    COLORREF visitNodeColor;
    COLORREF visitedNodeColor;
    COLORREF edgeColor;
    COLORREF visitedEdgeColor;
    COLORREF shortestPathColor;
    COLORREF lineColor;
    COLORREF highlightColor;
    COLORREF tableNodeUColor;
    COLORREF tableNodeVColor;
};
extern Settings settings;
extern double scale;
extern char* codeLines[128];
extern int codeLinesSize;
void readFiles();
void readGraphFromFile();
void clearCodeArea();

// UI
extern int currNode;
extern int updatingNode;
extern int startNode;
extern int endNode;
void entryView();
void drawGraphArrow(int x1, int y1, int x2, int y2, COLORREF color, int thickness, int weight, bool isHighlighted);
void drawPauseButton();
void drawButtons();
void drawStatusTable();
void drawGraph(int u, int v);
void drawCode(int currLine);
void drawAdjTable();
void drawScaledRectangle(int x1, int y1, int x2, int y2);
void drawScaledFillRectangle(int x1, int y1, int x2, int y2);
void drawScaledText(int x, int y, const wchar_t* text);
void drawScaledSolidCircle(int x, int y, int radius);
void drawScaledLine(int x1, int y1, int x2, int y2);
void pauseOrContinue(int totalDelay);
bool isReseted(short x, short y);
bool isCleared(short x, short y);
bool isBeginned(short x, short y);
bool isExited(short x, short y);
void findShortestPath(int start, int end);
void handleUserInput();
#endif // DIJKSTRA_DEMO_H