﻿/*
 * Copyright (c) 2025, Xedokyah
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE in the project root for license terms.
 *
 * heap.cpp
 * DijkstraDemo
 *
 * Created on 2024/11/30
 */

#include "dijkstra_demo.h"

struct Heap heap;

void swapForHeap(int a, int b) {
    HeapNode tmp = heap.nodes[a];
    heap.nodes[a] = heap.nodes[b];
    heap.nodes[b] = tmp;
}

void initHeap(int n) {
    heap.size = 0;
    heap.nodes = (HeapNode*)malloc(sizeof(HeapNode) * (static_cast<unsigned long long>(n) << 1));
    if (!heap.nodes) {
        printf("The memory is not enough!\a");
        exit(0);
    }
}

void heapify(int i) {
    while ((i << 1) + 1 < heap.size) {
        int left = (i << 1) + 1;
        int right = (i << 1) + 2;
        int min = i;
        if (left < heap.size && heap.nodes[left].dist < heap.nodes[min].dist) {
            min = left;
        }
        if (right < heap.size && heap.nodes[right].dist < heap.nodes[min].dist) {
            min = right;
        }
        if (min == i)
            break;
        swapForHeap(min, i);
        i = min;
    }
}

void push(HeapNode node) {
    int i = heap.size++;
    heap.nodes[i] = node;
    drawHeap(node.u, node.dist, 1);
    pauseOrContinue(settings.animationSpeed);
    while (i > 0) {
        int parent = (i - 1) >> 1;
        if (heap.nodes[parent].dist <= heap.nodes[i].dist)
            break;
        swapForHeap(parent, i);
        i = parent;
    }
    drawHeap(node.u, node.dist, 1);
}

HeapNode top() {
    if (isHeapEmpty()) {
        printf("Heap is empty!");
        exit(0);
    }
    return heap.nodes[0];
}

void pop() {
    if (isHeapEmpty())
        return;
    drawHeap(heap.nodes[0].u, heap.nodes[0].dist, 0);
    pauseOrContinue(settings.animationSpeed);
    swapForHeap(0, --heap.size);
    heapify(0);
}

int isHeapEmpty() {
    return heap.size == 0;
}

void clearHeap() {
    free(heap.nodes);
    heap.nodes = NULL;
    heap.size = 0;
}