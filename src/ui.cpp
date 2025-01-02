/*
 * Copyright (c) 2025, Xedokyah
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE in the project root for license terms.
 *
 * ui.cpp
 * DijkstraDemo
 *
 * Created on 2024/11/28
 */

#include "dijkstra_demo.h"

void entryView() {
    settextcolor(settings.textColor);
    settextstyle((int)(20 * scale), 0, _T("Consolas"));
    drawScaledText(10, 10, _T("请点击“开始”|“清空状态”|“重置”|“退出”按钮"));
    startNode = -1;
    endNode = -1;
    drawButtons();
    drawStatusTable();
    drawGraph(-1, -1);
    drawCode(-1);
    drawAdjTable();
}

int main() {
    readFiles();
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_HIDE);
    initgraph((int)(1600 * scale), int(800 * scale));
    setbkcolor(settings.bgColor);
    cleardevice();
    srand((unsigned int)time(NULL));
    if (settings.dataSource == 1) {
        readGraphFromFile();
    }
    else {
        generateGraph();
    }
    generateNodePositions();
    entryView();
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (isBeginned(msg.x, msg.y)) {
                    handleUserInput();
                }
                else if (isReseted(msg.x, msg.y) && !settings.dataSource) {
                    cleardevice();
                    clearGraph();
                    generateGraph();
                    generateNodePositions();
                    entryView();
                }
                else if (isExited(msg.x, msg.y)) {
                    clearGraph();
                    closegraph();
                    break;
                }
                else if (isCleared(msg.x, msg.y)) {
                    for (int i = 0; i < positions.size; ++i) {
                        positions.pot[i].dist = INT_MAX;
                        positions.pot[i].visited = 0;
                    }
                    cleardevice();
                    entryView();
                }
            }
        }
        Sleep(settings.clickDelay);
    }
    clearCodeArea();
    return 0;
}