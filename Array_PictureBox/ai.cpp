#include "moves.h"
#include "board.h"
#include <cmath>
#include <iostream>
using namespace std;

const int CASUAL_CAPTURE_DIR[4][2] = { {-2,-2}, {-2,2}, {2,-2}, {2,2} };
const int CASUAL_MOVE_DIR[4][2] = { {-1,-1}, {-1,1}, {1,-1}, {1,1} };
const int QUEEN_DIR[4][2] = { {-1,-1}, {-1,1}, {1,-1}, {1,1} };

int evaluateBoard(const desk& board, int perspective) {
    int score = 0;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            int pieceValue = 0;
            if (board.place[i][j].type == casual) pieceValue = 10;
            else if (board.place[i][j].type == queen) pieceValue = 30;
            
            if (pieceValue == 0) continue;
            
            if (perspective == board.place[i][j].color) {
                score += pieceValue;
            }
            else if (board.place[i][j].color != colorEmpty) {
                score -= pieceValue;
            }
        }
    }
    return score;
}

void addCasualCaptures(desk& tmp, moveInfo& testStep, moveInfo var[], int& count) {
    for (int d = 0; d < 4; d++) {
        testStep.to.x = testStep.from.x + CASUAL_CAPTURE_DIR[d][0];
        testStep.to.y = testStep.from.y + CASUAL_CAPTURE_DIR[d][1];
        if (isValidPosition(testStep.to) && isCapt(tmp, testStep)) {
            testStep.result = 2;
            if (count < 200) {
                var[count++] = testStep;
            }
        }
    }
}

void addQueenCaptures(desk& tmp, moveInfo& testStep, moveInfo var[], int& count) {
    for (int d = 0; d < 4; d++) {
        int tx = testStep.from.x + QUEEN_DIR[d][0];
        int ty = testStep.from.y + QUEEN_DIR[d][1];
        while (tx >= 0 && tx < boardSize && ty >= 0 && ty < boardSize) {
            testStep.to.x = tx;
            testStep.to.y = ty;
            if (isCapt(tmp, testStep)) {
                testStep.result = 2;
                if (count < 200) {
                    var[count++] = testStep;
                }
            }
            tx += QUEEN_DIR[d][0];
            ty += QUEEN_DIR[d][1];
        }
    }
}

void addQueenMoves(desk& tmp, moveInfo& testStep, bool allowMoves, moveInfo var[], int& count) {
    for (int d = 0; d < 4; d++) {
        int tx = testStep.from.x + QUEEN_DIR[d][0];
        int ty = testStep.from.y + QUEEN_DIR[d][1];
        while (tx >= 0 && tx < boardSize && ty >= 0 && ty < boardSize) {
            testStep.to.x = tx;
            testStep.to.y = ty;
            if (allowMoves && isNormalMove(tmp, testStep)) {
                testStep.result = 1;
                if (count < 200) {
                    var[count++] = testStep;
                }
            }
            tx += QUEEN_DIR[d][0];
            ty += QUEEN_DIR[d][1];
        }
    }
}

void addCasualMoves(desk& tmp, moveInfo& testStep, bool allowMoves, moveInfo var[], int& count) {
    for (int d = 0; d < 4; d++) {
        testStep.to.x = testStep.from.x + CASUAL_MOVE_DIR[d][0];
        testStep.to.y = testStep.from.y + CASUAL_MOVE_DIR[d][1];
        int rv = isValidMove(tmp, testStep);
        if (rv == 1 && allowMoves) {
            testStep.result = 1;
            if (count < 200) var[count++] = testStep;
        }
        else if (rv == 2) {
            testStep.result = 2;
            if (count < 200) {
                var[count++] = testStep;
            }
        }
    }
}

int getAllMoves(const desk& board, moveInfo var[200], int color) {
    moveInfo testStep;
    int count = 0;
    desk tmp = board;
    tmp.currentColor = color;

    bool searchMustCapt = (board.mustCapt && isValidPosition(board.mustKiller) &&
        board.place[board.mustKiller.x][board.mustKiller.y].color == color);

    if (color != black && color != white) {
        color = board.currentColor;
        tmp.currentColor = color;
    }

    if (searchMustCapt) {
        testStep.from = board.mustKiller;

        if (board.place[testStep.from.x][testStep.from.y].type == casual) {
            addCasualCaptures(tmp, testStep, var, count);
        }
        else {
            addQueenCaptures(tmp, testStep, var, count);
        }
    }
    else {
        bool anyCaptGlobal = haveAnyCapt(board, color);
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                testStep.from.x = i;
                testStep.from.y = j;

                if (board.place[i][j].color != color) 
                    continue;

                int capturesBefore = count;

                if (board.place[i][j].type == casual) {
                    addCasualCaptures(tmp, testStep, var, count);
                    if (count == capturesBefore && !anyCaptGlobal) {
                        addCasualMoves(tmp, testStep, true, var, count);
                    }
                }
                else if (board.place[i][j].type == queen) {
                    addQueenCaptures(tmp, testStep, var, count);
                    if (count == capturesBefore && !anyCaptGlobal) {
                        addQueenMoves(tmp, testStep, true, var, count);
                    }
                }
            }
        }
    }
    return count;
}

int minimax(desk& board, int depth, bool isMaximizing, int aiColor, int diff) {
    if (depth == 0) {
        return evaluateBoard(board, aiColor);
    }
    
    bool isMax = (board.currentColor == aiColor);
    moveInfo moves[200];
    int moveCount = getAllMoves(board, moves, board.currentColor);

    if (moveCount == 0) {
        return (board.currentColor == aiColor) ? -100000 : 100000;
    }

    int bestScore = isMax ? -100000 : 100000;
    
    for (int i = 0; i < moveCount; i++) {
        backupInfo backup;
        saveBackup(backup, moves[i], board);
        makeMove(board, moves[i]);
        
        bool nextIsMax = (board.currentColor == aiColor);
        int score;
        
        if (!nextIsMax && diff == 0) {
            score = evaluateBoard(board, aiColor);
        }
        else {
            score = minimax(board, depth - 1, nextIsMax, aiColor, diff);
        }
        
        loadBackup(backup, moves[i], board);
        
        if (isMax && score > bestScore) bestScore = score;
        else if (!isMax && score < bestScore) bestScore = score;
    }
    
    return bestScore;
}

void getBestMove(desk& board, moveInfo& bestMove, int aiColor, int diff) {
    moveInfo moves[200];
    int moveCount = getAllMoves(board, moves, aiColor);

    if (moveCount == 0) return;

    if (diff == 1) {
        bestMove = moves[0];
        return;
    }

    int depth = (diff == 2) ? 2 : 4;
    int bestScore = -100000;

    for (int i = 0; i < moveCount; i++) {
        backupInfo backup;
        saveBackup(backup, moves[i], board);
        makeMove(board, moves[i]);
        int score = minimax(board, depth, false, aiColor, diff);
        loadBackup(backup, moves[i], board);

        if (score > bestScore) {
            bestScore = score;
            bestMove = moves[i];
        }
    }
}
