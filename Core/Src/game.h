/*
 * game.h
 *
 *  Created on: Nov 28, 2023
 *      Author: luker
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "main.h"
#include <stdio.h>

typedef struct state {
	char board[3][3];
	uint8_t greenTurn;
} TicTacToe_State;

typedef struct moveToMake {
	uint8_t rowToMove;
	uint8_t colToMove;
} moveToMake;

typedef struct moveValuePair {
	int8_t value;
	uint8_t rowToMove;
	uint8_t colToMove;
} moveValuePair;

typedef struct actions {
	uint8_t rows[9];
	uint8_t cols[9];
	int numOfActions;
} actions;

TicTacToe_State getInitialState();
moveToMake findMoveByAI(TicTacToe_State* state);
moveValuePair maxValue(TicTacToe_State* state, int8_t depth);
moveValuePair minValue(TicTacToe_State* state, int8_t depth);

int8_t utility(TicTacToe_State* state);
actions actionsAt(TicTacToe_State* state);
TicTacToe_State act(TicTacToe_State* state, uint8_t row, uint8_t col);
uint8_t isTerminal(TicTacToe_State* state);
uint8_t boardIsFull(TicTacToe_State* state);
uint8_t boardHasSolution(TicTacToe_State* state);

uint8_t hasWon(TicTacToe_State* state, char whoWon);
#endif /* SRC_GAME_H_ */
