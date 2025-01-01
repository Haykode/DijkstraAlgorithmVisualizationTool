/*
 * eventUnits.cpp
 * DijkstraDemo
 *
 * Created on 2024/12/23
 */

#include "dijkstra_demo.h"

bool paused = false;

bool isReseted(short x, short y) {
    return x >= (int)(1310 * scale) && x <= (int)(1410 * scale) && y >= (int)(700 * scale) && y <= (int)(750 * scale);
}

bool isPaused(short x, short y) {
    return x >= (int)(1050 * scale) && x <= (int)(1150 * scale) && y >= (int)(700 * scale) && y <= (int)(750 * scale);
}

bool isCleared(short x, short y) {
    return x >= (int)(1050 * scale) && x <= (int)(1150 * scale) && y >= (int)(700 * scale) && y <= (int)(750 * scale);
}

bool isBeginned(short x, short y) {
    return x >= (int)(1180 * scale) && x <= (int)(1280 * scale) && y >= (int)(700 * scale) && y <= (int)(750 * scale);
}

bool isExited(short x, short y) {
    return x >= (int)(1440 * scale) && x <= (int)(1540 * scale) && y >= (int)(700 * scale) && y <= (int)(750 * scale);
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
                    }
                    else if (isExited(msg.x, msg.y)) {
                        clearGraph();
                        closegraph();
                        exit(0);
                    }
                }
            }
            if (!paused) {
                settextcolor(settings.textColor);
                LOGFONT font = { 0 };
                font.lfHeight = (int)(24 * scale);
                _tcscpy_s(font.lfFaceName, _T("Consolas"));
                settextstyle(&font);
                drawScaledText(1080, 715, _T("暂停"));
                setfillcolor(settings.bgColor);
                setlinecolor(settings.bgColor);
                drawScaledFillRectangle(10, 10, 500, 50);
                break;
            }
            else {
                settextcolor(settings.textColor);
                LOGFONT font = { 0 };
                font.lfHeight = (int)(24 * scale);
                _tcscpy_s(font.lfFaceName, _T("Consolas"));
                settextstyle(&font);
                drawScaledText(1080, 715, _T("继续"));
                drawScaledText(10, 10, _T("已暂停，请点击“继续”|“退出”按钮"));
            }
            Sleep(settings.clickDelay);
        }
        Sleep(step);
        elapsed += step;
    }
}

int getNodeSelection(const TCHAR* prompt) {
    LOGFONT font = { 0 };
    font.lfHeight = (int)(20 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(settings.textColor);
    drawScaledText(10, 10, prompt);
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
    drawScaledFillRectangle(10, 10, 500, 50);
    startNode = getNodeSelection(_T("点击一个点作为起点"));
    drawGraph(-1, -1);
    endNode = getNodeSelection(_T("点击一个点作为终点"));
    setfillcolor(settings.bgColor);
    setlinecolor(settings.bgColor);
    drawScaledFillRectangle(10, 10, 500, 50);
    drawGraph(-1, -1);
    drawPauseButton();
    findShortestPath(startNode, endNode);
    drawButtons();
    LOGFONT font = { 0 };
    font.lfHeight = (int)(20 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(settings.textColor);
    drawScaledText(10, 10, _T("算法执行完毕，请点击“重置”|“清空状态”|“退出”按钮"));
}