/*
 * Copyright (c) 2025, Xedokyah
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE in the project root for license terms.
 *
 * eventUnits.cpp
 * DijkstraDemo
 *
 * Created on 2024/12/23
 */

#include "dijkstra_demo.h"

bool paused = false;

bool isGenerated(short x, short y) {
    return x >= (int)(1310 * scale) && x <= (int)(1410 * scale) && y >= (int)(720 * scale) && y <= (int)(750 * scale);
}

bool isPaused(short x, short y) {
    return x >= (int)(1050 * scale) && x <= (int)(1150 * scale) && y >= (int)(720 * scale) && y <= (int)(750 * scale);
}

bool isReseted(short x, short y) {
    return x >= (int)(1050 * scale) && x <= (int)(1150 * scale) && y >= (int)(720 * scale) && y <= (int)(750 * scale);
}

bool isBeginned(short x, short y) {
    return x >= (int)(1180 * scale) && x <= (int)(1280 * scale) && y >= (int)(720 * scale) && y <= (int)(750 * scale);
}

bool isExited(short x, short y) {
    return x >= (int)(1440 * scale) && x <= (int)(1540 * scale) && y >= (int)(720 * scale) && y <= (int)(750 * scale);
}

void pauseOrContinue(int totalDelay) {
    int step = 10;
    int elapsed = 0;
    while (elapsed < totalDelay) {
        while (true) {
            if (MouseHit()) {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    if (isPaused(msg.x, msg.y)) {
                        paused = !paused;
                        setlinecolor(settings.lineColor);
                        setlinestyle(PS_SOLID, 2);
                        setfillcolor(settings.buttonColor);
                        drawScaledFillRectangle(1050, 720, 1150, 750);
                        setfillcolor(settings.bgColor);
                        setlinecolor(settings.bgColor);
                        drawScaledFillRectangle(1010, 760, 1600, 800);
                        setbkmode(TRANSPARENT);
                        LOGFONT font = { 0 };
                        font.lfHeight = (int)(24 * scale);
                        font.lfWeight = 0;
                        _tcscpy_s(font.lfFaceName, _T("Consolas"));
                        settextstyle(&font);
                        settextcolor(settings.textColor);
                        if (!paused) {
                            drawScaledText(1080, 725, _T("暂停"));
                            drawScaledText(1050, 765, _T("算法执行时可以点击“暂停”|“退出”按钮"));
                        }
                        else {
                            drawScaledText(1080, 725, _T("继续"));
                            drawScaledText(1050, 765, _T("已暂停，请点击“继续”|“退出”按钮"));
                        }
                        setbkmode(OPAQUE);
                    }
                    else if (isExited(msg.x, msg.y)) {
                        clearGraph();
                        closegraph();
                        exit(0);
                    }
                }
            }
            if (!paused) {
                break;
            }
            Sleep(settings.clickDelay);
        }
        Sleep(step);
        elapsed += step;
    }
}

int getNodeSelection(const TCHAR* prompt) {
    LOGFONT font = { 0 };
    font.lfHeight = (int)(24 * scale);
    font.lfWeight = 0;
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(settings.textColor);
    drawScaledText(1050, 765, prompt);
    int selected = -1;
    while (selected == -1) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            for (int i = 0; i < positions.size; ++i) {
                int scaledNodeX = int(positions.pot[i].x * scale);
                int scaledNodeY = int(positions.pot[i].y * scale);
                if ((msg.x - scaledNodeX) * (msg.x - scaledNodeX) +
                        (msg.y - scaledNodeY) * (msg.y - scaledNodeY) <=
                    int(400 * scale * scale)) {
                    selected = i;
                    break;
                }
            }
        }
        Sleep(settings.clickDelay);
    }
    return selected;
}

void handleUserInput() {
    setfillcolor(settings.bgColor);
    setlinecolor(settings.bgColor);
    drawScaledFillRectangle(1010, 760, 1600, 800);
    startNode = getNodeSelection(_T("点击一个点作为起点"));
    drawGraph(-1, -1);
    endNode = getNodeSelection(_T("点击一个点作为终点"));
    setfillcolor(settings.bgColor);
    setlinecolor(settings.bgColor);
    drawScaledFillRectangle(1010, 760, 1600, 800);
    drawGraph(-1, -1);
    setlinecolor(settings.lineColor);
    setlinestyle(PS_SOLID, 2);
    setfillcolor(settings.buttonColor);
    drawScaledFillRectangle(1050, 720, 1150, 750);
    LOGFONT font = { 0 };
    font.lfHeight = (int)(24 * scale);
    font.lfWeight = 0;
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(settings.textColor);
    setbkmode(TRANSPARENT);
    drawScaledText(1080, 725, _T("暂停"));
    drawScaledText(1050, 765, _T("算法执行时可以点击“暂停”|“退出”按钮"));
    setbkmode(OPAQUE);
    findShortestPath(startNode, endNode);
    drawButtons();
    setfillcolor(settings.bgColor);
    setlinecolor(settings.bgColor);
    drawScaledFillRectangle(1010, 760, 1600, 800);
    font.lfHeight = (int)(24 * scale);
    font.lfWeight = 0;
    settextstyle(&font);
    settextcolor(settings.textColor);
    drawScaledText(1050, 765, _T("算法执行完毕，请点击“重置”|“新生成”|“退出”按钮"));
}