/*
 * game.c
 *
 *  Created on: Nov 28, 2023
 *      Author: luker
 */

#include "game.h"

TicTacToe_State getInitialState() {
	/*
	 * r: Red Pin
	 * g: Green Pin
	 * -: Empty Pin
	 */
	TicTacToe_State gameGame = {
			{
				{'-', '-', '-'},
				{'-', '-', '-'},
				{'-', '-', '-'}
			},
			1
	};

	return gameGame;
}

moveToMake findMoveByAI(TicTacToe_State* state) {
	moveValuePair valueMovePair = maxValue(state, 3);

	moveToMake finalMove = {
			valueMovePair.rowToMove,
			valueMovePair.colToMove
	};

	return finalMove;
}

moveValuePair maxValue(TicTacToe_State* state, int8_t depth) {
	if (isTerminal(state) == 1 || depth == 0) {
		moveValuePair terminalPair = {
				utility(state), 10, 10
		};

		return terminalPair;
	}

	moveValuePair currMoveValuePair = {
		-100, 10, 10
	};
	actions possibleActions = actionsAt(state);
	for (int i = 0; i < possibleActions.numOfActions; i++) {
		TicTacToe_State newState = act(state, possibleActions.rows[i], possibleActions.cols[i]);

		moveValuePair minMoveValuePair = minValue(&newState, depth-1);
		if (minMoveValuePair.value > currMoveValuePair.value) {
			currMoveValuePair.value = minMoveValuePair.value;
			currMoveValuePair.rowToMove = possibleActions.rows[i];
			currMoveValuePair.colToMove = possibleActions.cols[i];

		}
	}

	return currMoveValuePair;
}

moveValuePair minValue(TicTacToe_State* state, int8_t depth) {
	if (isTerminal(state) == 1 || depth == 0) {
		moveValuePair terminalPair = {
				utility(state), 10, 10
		};

		return terminalPair;
	}

	moveValuePair currMoveValuePair = {
		100, 10, 10
	};
	actions possibleActions = actionsAt(state);
	for (int i = 0; i < possibleActions.numOfActions; i++) {
		TicTacToe_State newState = act(state, possibleActions.rows[i], possibleActions.cols[i]);

		moveValuePair maxMoveValuePair = maxValue(&newState, depth-1);
		if (maxMoveValuePair.value < currMoveValuePair.value) {
			currMoveValuePair.value = maxMoveValuePair.value;
			currMoveValuePair.rowToMove = possibleActions.rows[i];
			currMoveValuePair.colToMove = possibleActions.cols[i];

		}
	}

	return currMoveValuePair;
}


/**
 * The utility function for minimax game tree search.
 *
 *
 */
int8_t utility(TicTacToe_State* state) {
	if (state->greenTurn == 1) {
		if (hasWon(state, 'g') == 1) {
			return 5;

		} else if (hasWon(state, 'r') == 1) {
			return -10;

		} else {
			return 0;
		}
	} else if (state->greenTurn == 0) {
		if (hasWon(state, 'g') == 1) {
			return -10;
		} else if (hasWon(state, 'r') == 1) {
			return 5;
		} else {
			return 0;
		}
	}
}

/**
 * Calculating the rows and cols of the empty cells in the game state
 * actions
 * @param TicTacToe_State* state:
 *   Reference to the game state, including the board and who's turn it is.
 *
 * @returns action:
 *  A indexable struct of rows and cols, which indicate the empty cells.
 */
actions actionsAt(TicTacToe_State* state) {
	actions possibleActions = {
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			0
	};

	uint8_t i = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (state->board[r][c] == '-') {
				possibleActions.rows[i] = r;
				possibleActions.cols[i] = c;
				possibleActions.numOfActions++;
				i++;
			}
		}
	}

	return possibleActions;
}


/**
 * Taking a row,col pair and 'filling it' on the board, based on who's turn it is.
 *
 * @param TicTacToe_State* state:
 *   Reference to the game state, including the board and who's turn it is.
 *
 * @param row:
 * 	The row to act upon
 *
 * @param col:
 *  The column to act upon.
 *
 * @returns TicTacToe_State:
 * 	A resultant state who state->board[row][col] is filled.
 */
TicTacToe_State act(TicTacToe_State* state, uint8_t row, uint8_t col) {
	TicTacToe_State newState = getInitialState();
	memcpy(&newState, state, sizeof(newState));

	if (newState.greenTurn == 1) {
		newState.board[row][col] = 'g';
		newState.greenTurn = 0;
	} else if (newState.greenTurn == 0) {
		newState.board[row][col] = 'r';
		newState.greenTurn = 1;
	}
	return newState;
}


/**
 * Testing if the game state has reached a terminal point,
 * that being completely full or a player has won.
 *
 * @param TicTacToe_State* state:
 *   Reference to the game state, including the board and who's turn it is.
 *
 * @returns:
 * 	1 if the game is terminal
 * 	0 if not
 */
uint8_t isTerminal(TicTacToe_State* state) {
	if (boardIsFull(state) == 1 || boardHasSolution(state) == 1) {
		return 1;
	}

	return 0;
}

/**
 * Checking if the board is completely filled with 'r' or 'g'.
 *
 * @param TicTacToe_State* state:
 *   Reference to the game state, including the board and who's turn it is.
 *
 * @returns:
 * 	1 if the board is filled.
 * 	0 if not.
 */
uint8_t boardIsFull(TicTacToe_State* state) {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (state->board[r][c] != 'r' && state->board[r][c] != 'g') {
				return 0;
			}
		}
	}

	return 1;
}

/**
 * Checking if any player, red or green, has won.
 *
 * @param TicTacToe_State* state:
 *   Reference to the game state, including the board and who's turn it is.

 * @returns:
 * 	1 if a player has won.
 * 	0 if not.
 */
uint8_t boardHasSolution(TicTacToe_State* state) {
	for (int i = 0; i < 3; i++) {
		// Checking if rows are filled
		if (
			(state->board[i][0] == 'r' || state->board[i][0] == 'g')
			&& state->board[i][0] == state->board[i][1]
			&& state->board[i][1] == state->board[i][2]
		) {
			return 1;
		}

		// Checking if columns are filled
		if (
			(state->board[0][i] == 'r' || state->board[0][i] == 'g')
			&& state->board[0][i] == state->board[1][i]
			&& state->board[1][i] == state->board[2][i]
		) {
			return 1;
		}
	}

	// Checking if diagonals are filled
	if (
		(state->board[0][0] == 'r' || state->board[0][0] == 'g')
		&& state->board[0][0] == state->board[1][1] && state->board[1][1] == state->board[2][2]
	) {
		return 1;
	}

	if (
		(state->board[0][2] == 'r' || state->board[0][2] == 'g')
		&& state->board[0][2] == state->board[1][1] && state->board[1][1] == state->board[2][0]
	) {
		return 1;
	}

	return 0;
}

/**
 * Checking if a player has won the game.
 *
 * @param TicTacToe_State* state:
 *   Reference to the game state, including the board and who's turn it is.
 *
 * @param whoWon:
 * 	 What character to check if its won..
 *
 * @returns:
 * 	1 if 'whoWon' has in fact won.
 * 	0 if not.
 */
uint8_t hasWon(TicTacToe_State* state, char whoWon) {
	for (int i = 0; i < 3; i++) {
		// Checking if rows are filled
		if (
			(state->board[i][0] == whoWon)
			&& state->board[i][0] == state->board[i][1]
			&& state->board[i][1] == state->board[i][2]
		) {
			return 1;
		}

		// Checking if columns
		if (
			(state->board[0][i] == whoWon)
			&& state->board[0][i] == state->board[1][i]
			&& state->board[1][i] == state->board[2][i]
		) {
			return 1;
		}
	}

	// Checking if diagonals
	if (
		(state->board[0][0] == whoWon)
		&& state->board[0][0] == state->board[1][1] && state->board[1][1] == state->board[2][2]
	) {
		return 1;
	}

	if (
		(state->board[0][2] == whoWon)
		&& state->board[0][2] == state->board[1][1] && state->board[1][1] == state->board[2][0]
	) {
		return 1;
	}

	return 0;
}
