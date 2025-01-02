/*
 * Copyright (c) 2025, Xedokyah
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE in the project root for license terms.
 *
 * readFiles.cpp
 * DijkstraDemo
 *
 * Created on 2024/12/26
 */

#include "dijkstra_demo.h"

Settings settings;
double scale = 1.0;
char* codeLines[128];
int codeLinesSize = 0;

void setScale(int newScale) {
    if (newScale <= 0) {
        fprintf(stderr, "Invalid scale value. Must be positive.\n");
        exit(1);
    }
    scale = 1.0 * newScale / 100.0;
}

void trimWhitespace(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) {
        str++;
    }
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
}

COLORREF parseColor(const char* colorString) {
    char color[16];
    strncpy_s(color, colorString, sizeof(color) - 1);
    color[sizeof(color) - 1] = '\0';
    trimWhitespace(color);
    if (!strcmp(color, "blue")) {
        return BLUE;
    }
    if (!strcmp(color, "green")) {
        return GREEN;
    }
    if (!strcmp(color, "cyan")) {
        return CYAN;
    }
    if (!strcmp(color, "red")) {
        return RED;
    }
    if (!strcmp(color, "magenta")) {
        return MAGENTA;
    }
    if (!strcmp(color, "brown")) {
        return BROWN;
    }
    if (!strcmp(color, "lightgray")) {
        return LIGHTGRAY;
    }
    if (!strcmp(color, "darkgray")) {
        return DARKGRAY;
    }
    if (!strcmp(color, "lightblue")) {
        return LIGHTBLUE;
    }
    if (!strcmp(color, "lightgreen")) {
        return LIGHTGREEN;
    }
    if (!strcmp(color, "lightcyan")) {
        return LIGHTCYAN;
    }
    if (!strcmp(color, "lightred")) {
        return LIGHTRED;
    }
    if (!strcmp(color, "lightmagenta")) {
        return LIGHTMAGENTA;
    }
    if (!strcmp(color, "yellow")) {
        return YELLOW;
    }
    if (!strcmp(color, "white")) {
        return WHITE;
    }
    return BLACK;
}

void readCodeArea() {
    FILE* file;
    errno_t err = fopen_s(&file, "config_txts/codeArea.txt", "r");
    if (err != 0 || !file) {
        perror("Can't open file!\a");
        exit(1);
    }
    char buffer[100];
    while (fgets(buffer, 100, file) && codeLinesSize < 100) {
        codeLines[codeLinesSize] = (char*)malloc(strlen(buffer) + 1);
        if (codeLines[codeLinesSize] == NULL) {
            perror("The memory is not enough!\a");
            exit(0);
        }
        strcpy_s(codeLines[codeLinesSize], strlen(buffer) + 1, buffer);
        codeLines[codeLinesSize][strcspn(codeLines[codeLinesSize], "\n")] = '\0';
        ++codeLinesSize;
    }
    fclose(file);
}

void clearCodeArea() {
    for (int i = 0; i < codeLinesSize; ++i) {
        free(codeLines[i]);
    }
}

void readSetting() {
    FILE* file;
    errno_t err = fopen_s(&file, "config_txts/setting.txt", "r");
    if (err != 0 || file == NULL) {
        perror("Can't open setting.txt");
        exit(1);
    }
    char line[512];
    int lineNum = 0;
    while (fgets(line, sizeof(line), file)) {
        ++lineNum;
        char* commentStart = strstr(line, "//");
        if (commentStart) {
            *commentStart = '\0';
        }
        switch (lineNum) {
        case 1:
            sscanf_s(line, "%d", &settings.animationSpeed);
            break;
        case 2:
            sscanf_s(line, "%d", &settings.dataSource);
            break;
        case 3:
            sscanf_s(line, "%s", settings.dataFilePath, (unsigned int)sizeof(settings.dataFilePath));
            break;
        case 4:
            sscanf_s(line, "%d %d", &settings.nodeCount, &settings.randomNodeFlag);
            break;
        case 5:
            sscanf_s(line, "%d %d", &settings.edgeCount, &settings.randomEdgeFlag);
            break;
        case 6:
            sscanf_s(line, "%d", &settings.maxWeight);
            break;
        case 7:
            sscanf_s(line, "%d", &settings.windowScale);
            break;
        case 8:
            sscanf_s(line, "%d", &settings.clickDelay);
            break;
        case 9:
            settings.bgColor = parseColor(line);
            break;
        case 10:
            settings.textColor = parseColor(line);
            break;
        case 11:
            settings.buttonColor = parseColor(line);
            break;
        case 12:
            settings.nodeColor = parseColor(line);
            break;
        case 13:
            settings.startNodeColor = parseColor(line);
            break;
        case 14:
            settings.endNodeColor = parseColor(line);
            break;
        case 15:
            settings.visitNodeColor = parseColor(line);
            break;
        case 16:
            settings.visitedNodeColor = parseColor(line);
            break;
        case 17:
            settings.edgeColor = parseColor(line);
            break;
        case 18:
            settings.visitedEdgeColor = parseColor(line);
            break;
        case 19:
            settings.shortestPathColor = parseColor(line);
            break;
        case 20:
            sscanf_s(line, "%d", &settings.shortestPathSpeed);
            break;
        case 21:
            settings.lineColor = parseColor(line);
            break;
        case 22:
            settings.highlightColor = parseColor(line);
            break;
        case 23:
            settings.tableNodeUColor = parseColor(line);
            break;
        case 24:
            settings.tableNodeVColor = parseColor(line);
            break;
        default:
            fprintf(stderr, "Unexpected extra line in setting.txt\n");
            fclose(file);
            exit(1);
        }
    }
    fclose(file);
    if (settings.animationSpeed <= 0) {
        settings.animationSpeed = 500;
    }
    if (settings.dataSource != 0 && settings.dataSource != 1) {
        settings.dataSource = 0;
    }
    if (settings.nodeCount < 0 || settings.nodeCount > 20 || (settings.randomNodeFlag != 1 && settings.randomNodeFlag != 0)) {
        settings.nodeCount = 20;
        settings.randomNodeFlag = 1;
    }
    if (settings.edgeCount < 0 || settings.edgeCount > 6 || (settings.randomEdgeFlag != 1 && settings.randomEdgeFlag != 0)) {
        settings.edgeCount = 6;
        settings.randomEdgeFlag = 1;
    }
    if (settings.maxWeight < 0 || settings.maxWeight > 50) {
        settings.maxWeight = 50;
    }
    if (settings.windowScale <= 0 || settings.windowScale > 200) {
        settings.windowScale = 100;
    }
    else {
        setScale(settings.windowScale);
    }
    if (settings.clickDelay < 0) {
        settings.clickDelay = 10;
    }
    if (settings.shortestPathSpeed < 0) {
        settings.shortestPathSpeed = 300;
    }
}

void readFiles() {
    readCodeArea();
    readSetting();
}