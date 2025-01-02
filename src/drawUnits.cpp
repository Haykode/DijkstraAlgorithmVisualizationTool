/*
 * Copyright (c) 2025, Xedokyah
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE in the project root for license terms.
 *
 * drawUnits.cpp
 * DijkstraDemo
 *
 * Created on 2024/12/23
 */

#include "dijkstra_demo.h"

int startNode = -1;
int endNode = -1;
int currNode = -1;
int updatingNode = -1;

void drawScaledRectangle(int x1, int y1, int x2, int y2) {
    rectangle(int(x1 * scale), int(y1 * scale), int(x2 * scale), int(y2 * scale));
}

void drawScaledFillRectangle(int x1, int y1, int x2, int y2) {
    fillrectangle(int(x1 * scale), int(y1 * scale), int(x2 * scale), int(y2 * scale));
}

void drawScaledText(int x, int y, const wchar_t* text) {
    outtextxy(int(x * scale), int(y * scale), text);
}

void drawScaledSolidCircle(int x, int y, int radius) {
    solidcircle(int(x * scale), int(y * scale), int(radius * scale));
}

void drawScaledLine(int x1, int y1, int x2, int y2) {
    line(int(x1 * scale), int(y1 * scale), int(x2 * scale), int(y2 * scale));
}

void drawGraphArrow(int x1, int y1, int x2, int y2, COLORREF color, int thickness, int weight, bool isHighlighted) {
    setlinecolor(color);
    setlinestyle(PS_SOLID, thickness);
    double angle = atan2(y2 - y1, x2 - x1);
    int nodeRadius = 20;
    int arrowSize = 10;
    int newX1 = x1 + (int)(nodeRadius * cos(angle));
    int newY1 = y1 + (int)(nodeRadius * sin(angle));
    int newX2 = x2 - (int)(nodeRadius * cos(angle));
    int newY2 = y2 - (int)(nodeRadius * sin(angle));
    int arrowX1 = newX2 - (int)(arrowSize * cos(angle - 3.1415926 / 6));
    int arrowY1 = newY2 - (int)(arrowSize * sin(angle - 3.1415926 / 6));
    int arrowX2 = newX2 - (int)(arrowSize * cos(angle + 3.1415926 / 6));
    int arrowY2 = newY2 - (int)(arrowSize * sin(angle + 3.1415926 / 6));
    drawScaledLine(newX1, newY1, newX2, newY2);
    drawScaledLine(newX2, newY2, arrowX1, arrowY1);
    drawScaledLine(newX2, newY2, arrowX2, arrowY2);
    double edgeLength = sqrt(pow(newX2 - newX1, 2.0) + pow(newY2 - newY1, 2.0));
    double lengthFactor = log(edgeLength + 1) * 0.020;
    double angleFactor = fabs(sin(2 * angle)) * 0.3 + 0.3;
    int offset = (int)(edgeLength * lengthFactor * angleFactor);
    int midX = (newX1 + newX2) >> 1;
    int midY = (newY1 + newY2) >> 1;
    int textX = midX - (int)(offset * sin(angle));
    int textY = midY + (int)(offset * cos(angle));
    TCHAR weightText[16];
    swprintf_s(weightText, _T("%d"), weight);
    LOGFONT font = { 0 };
    if (isHighlighted) {
        font.lfHeight = (int)(25 * scale);
        font.lfWeight = FW_BOLD;
    }
    else {
        font.lfHeight = (int)(20 * scale);
    }
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(color);
    drawScaledText(textX, textY, weightText);
}

void drawGraph(int u, int v) {
    setlinecolor(settings.bgColor);
    setfillcolor(settings.bgColor);
    drawScaledFillRectangle(0, 50, 560, 650);
    for (int i = 0; i < graph.size; ++i) {
        Node* curr = graph.adj[i];
        while (curr) {
            if (!((i == u && curr->v == v))) {
                drawGraphArrow(positions.pot[i].x, positions.pot[i].y,
                    positions.pot[curr->v].x, positions.pot[curr->v].y,
                    settings.edgeColor, (int)(2 * scale), curr->weight, false);
            }
            curr = curr->next;
        }
    }
    for (int i = 0; i < graph.size; ++i) {
        Node* curr = graph.adj[i];
        while (curr) {
            COLORREF edgeColor = settings.edgeColor;
            int thickness = (int)(5 * scale);
            if (i == u && curr->v == v) {
                edgeColor = settings.visitedEdgeColor;
            }
            if (edgeColor != settings.edgeColor) {
                drawGraphArrow(positions.pot[i].x, positions.pot[i].y,
                    positions.pot[curr->v].x, positions.pot[curr->v].y,
                    edgeColor, thickness, curr->weight, true);
            }
            curr = curr->next;
        }
    }
    for (int i = 0; i < positions.size; ++i) {
        if (i == currNode) {
            setfillcolor(settings.visitNodeColor);
        }
        else if (i == startNode) {
            setfillcolor(settings.startNodeColor);
        }
        else if (i == endNode) {
            setfillcolor(settings.endNodeColor);
        }
        else if (positions.pot[i].visited == 0) {
            setfillcolor(settings.nodeColor);
        }
        else if (positions.pot[i].visited == 1) {
            setfillcolor(settings.visitNodeColor);
        }
        else {
            setfillcolor(settings.visitedNodeColor);
        }
        drawScaledSolidCircle(positions.pot[i].x, positions.pot[i].y, 20);
        TCHAR id[5];
        swprintf_s(id, _T("%2d"), i);
        if (i == currNode) {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(30 * scale);
            font.lfWeight = FW_BOLD;
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.tableNodeUColor);
        }
        else if (i == updatingNode) {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(30 * scale);
            font.lfWeight = FW_BOLD;
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.tableNodeVColor);
        }
        else {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(25 * scale);
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.textColor);
        }
        drawScaledText(positions.pot[i].x - 13, positions.pot[i].y - 13, id);
    }
}

void drawPauseButton() {
    setlinecolor(settings.lineColor);
    setlinestyle(PS_SOLID, 2);
    setfillcolor(settings.buttonColor);
    drawScaledFillRectangle(1050, 700, 1150, 750);
    settextcolor(settings.textColor);
    LOGFONT font = { 0 };
    font.lfHeight = (int)(24 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    drawScaledText(1080, 715, _T("暂停"));
}

void drawButtons() {
    setlinecolor(settings.lineColor);
    setlinestyle(PS_SOLID, 2);
    setfillcolor(settings.buttonColor);
    settextcolor(settings.textColor);
    LOGFONT font = { 0 };
    font.lfHeight = (int)(24 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    drawScaledFillRectangle(1050, 700, 1150, 750);
    drawScaledText(1055, 715, _T("清空状态"));
    drawScaledFillRectangle(1180, 700, 1280, 750);
    drawScaledText(1210, 715, _T("开始"));
    drawScaledFillRectangle(1310, 700, 1410, 750);
    drawScaledText(1340, 715, _T("重置"));
    drawScaledFillRectangle(1440, 700, 1540, 750);
    drawScaledText(1470, 715, _T("退出"));
}

void drawStatusTable() {
    int startX = 15;
    int startY = 710;
    int cellWidth = 50;
    int cellHeight = 40;
    int tableWidth = positions.size * cellWidth;
    setlinecolor(settings.bgColor);
    setfillcolor(settings.bgColor);
    drawScaledFillRectangle(startX, startY, startX + cellWidth * positions.size, startY + cellHeight * 2);
    setlinecolor(settings.lineColor);
    setlinestyle(PS_SOLID, 2);
    drawScaledLine(startX, startY, startX + tableWidth, startY);
    drawScaledLine(startX, startY + cellHeight, startX + tableWidth, startY + cellHeight);
    drawScaledLine(startX, startY, startX, startY + cellHeight);
    for (int i = 1; i <= positions.size; ++i) {
        drawScaledLine(startX + i * cellWidth, startY, startX + i * cellWidth, startY + cellHeight);
    }
    LOGFONT font = { 0 };
    font.lfHeight = (int)(20 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(settings.textColor);
    drawScaledText(startX, startY - 25, _T("dist[]"));
    for (int i = 0; i < positions.size; ++i) {
        TCHAR buffer[50];
        if (positions.pot[i].dist == INT_MAX) {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(20 * scale);
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(RED);
            swprintf_s(buffer, _T("INF"));
        }
        else if (i == updatingNode) {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(24 * scale);
            font.lfWeight = FW_BOLD;
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.tableNodeVColor);
            swprintf_s(buffer, _T("%3d"), positions.pot[i].dist);
        }
        else {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(20 * scale);
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.textColor);
            swprintf_s(buffer, _T("%3d"), positions.pot[i].dist);
        }
        drawScaledText(startX + 1 + i * cellWidth + 10, startY + 10, buffer);
    }
    for (int i = 0; i < positions.size; ++i) {
        TCHAR buffer[50];
        if (i == currNode) {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(24 * scale);
            font.lfWeight = FW_BOLD;
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.tableNodeUColor);
        }
        else if (i == updatingNode) {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(24 * scale);
            font.lfWeight = FW_BOLD;
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.tableNodeVColor);
        }
        else {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(20 * scale);
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.textColor);
        }
        swprintf_s(buffer, _T("%d"), i);
        drawScaledText(startX + 3 + i * cellWidth + 10, startY + cellHeight + 10, buffer);
    }
}

void drawCode(int currLine) {
    LOGFONT font = { 0 };
    font.lfHeight = (int)(25 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    for (int i = 0; i < codeLinesSize; ++i) {
        if (i == currLine) {
            font.lfWeight = FW_BOLD;
            settextcolor(settings.highlightColor);
        }
        else {
            settextcolor(settings.textColor);
        }
        wchar_t wBuffer[256];
        MultiByteToWideChar(CP_ACP, 0, codeLines[i], -1, wBuffer, 256);
        drawScaledText(1010, 50 + i * 30, wBuffer);
    }
}

void drawNodeArrow(int x, int y) {
    setlinecolor(settings.lineColor);
    drawScaledLine(x - 5, y + 15, x + 5, y + 15);
    drawScaledLine(x + 5, y + 15, x + 3, y + 14);
    drawScaledLine(x + 5, y + 15, x + 3, y + 16);
}

void drawNode(int u, int v, int w, int x1, int y1, int x2, int y2) {
    setlinecolor(settings.lineColor);
    drawScaledRectangle(x1, y1, x2, y2);
    drawScaledLine(x1 + 25, y1, x1 + 25, y2);
    drawScaledLine(x1 + 50, y1, x1 + 50, y2);
    TCHAR vertex[3], weight[3];
    if (v == updatingNode && u == currNode) {
        LOGFONT font = { 0 };
        font.lfHeight = (int)(20 * scale);
        font.lfWeight = FW_BOLD;
        _tcscpy_s(font.lfFaceName, _T("Consolas"));
        settextstyle(&font);
        settextcolor(settings.tableNodeVColor);
    }
    else {
        LOGFONT font = { 0 };
        font.lfHeight = (int)(20 * scale);
        _tcscpy_s(font.lfFaceName, _T("Consolas"));
        settextstyle(&font);
        settextcolor(settings.textColor);
    }
    swprintf_s(vertex, _T("%2d"), v);
    swprintf_s(weight, _T("%2d"), w);
    drawScaledText(x1 + 5, y1 + 5, vertex);
    drawScaledText(x1 + 30, y1 + 5, weight);
}

void drawAdjTable() {
    int startX = 600, startY = 50;
    int tableWidth = 60, tableHeight = 30;
    LOGFONT font = { 0 };
    font.lfHeight = (int)(18 * scale);
    _tcscpy_s(font.lfFaceName, _T("Consolas"));
    settextstyle(&font);
    settextcolor(settings.textColor);
    drawScaledText(startX - 18, startY - 20, _T("u  v  w"));
    for (int u = 0; u < graph.size; ++u) {
        setlinecolor(settings.lineColor);
        setlinestyle(PS_SOLID, 0);
        drawScaledRectangle(startX, startY + u * tableHeight, startX + tableWidth, startY + (u + 1) * tableHeight);
        TCHAR id[3];
        if (u == currNode) {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(20 * scale);
            font.lfWeight = FW_BOLD;
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.tableNodeUColor);
        }
        else {
            LOGFONT font = { 0 };
            font.lfHeight = (int)(20 * scale);
            _tcscpy_s(font.lfFaceName, _T("Consolas"));
            settextstyle(&font);
            settextcolor(settings.textColor);
        }
        swprintf_s(id, _T("%2d"), u);
        drawScaledText(startX - 25, startY + u * tableHeight + 5, id);
        Node* curr = graph.adj[u];
        if (!curr) {
            continue;
        }
        int adjCowSize = 1;
        drawNode(u, curr->v, curr->weight,
            startX, startY + u * tableHeight,
            startX + tableWidth, startY + (u + 1) * tableHeight);
        while (curr->next) {
            curr = curr->next;
            drawNodeArrow(startX + adjCowSize * tableWidth + (adjCowSize - 1) * 5, startY + u * tableHeight);
            drawNode(u, curr->v, curr->weight,
                startX + adjCowSize * (tableWidth + 5), startY + 2 + u * tableHeight,
                startX + tableWidth + adjCowSize * (tableWidth + 5), startY + tableHeight - 2 + u * tableHeight);
            ++adjCowSize;
        }
    }
}