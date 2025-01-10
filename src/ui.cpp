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
    LOGFONT font = { 0 };
    font.lfHeight = (int)(24 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(settings.textColor);
    drawScaledText(10, 10, _T("请点击“开始”|“新生成”|“重置”|“退出”按钮"));
    startNode = -1;
    endNode = -1;
    drawButtons();
    drawStatusTable();
    drawHeap(-1, -1, 2);
    drawGraph(-1, -1);
    drawCodeArea(-1);
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
    bool running = true;
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (isBeginned(msg.x, msg.y) && running) {
                    handleUserInput();
                    running = false;
                }
                else if (isGenerated(msg.x, msg.y) && !settings.dataSource) {
                    cleardevice();
                    clearGraph();
                    generateGraph();
                    generateNodePositions();
                    entryView();
                    running = true;
                }
                else if (isExited(msg.x, msg.y)) {
                    clearGraph();
                    closegraph();
                    break;
                }
                else if (isReseted(msg.x, msg.y)) {
                    for (int i = 0; i < positions.size; ++i) {
                        positions.pot[i].dist = INT_MAX;
                        positions.pot[i].visited = 0;
                    }
                    cleardevice();
                    entryView();
                    running = true;
                }
            }
        }
        Sleep(settings.clickDelay);
    }
    clearCodeArea();
    return 0;
}