#include <tictac_support.h>
#include <stdio.h>
/**
	make_move: takes a board state and makes a legal
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		 -1: o

	returns (int):
		the number of steps it took to choose the best move
		(current implementation returns 1 by default, 0 if no move made)
**/

int make_move( int board[][3] )
{

	// -1 = o, 1 = x, 0 = empty

	// Figures out who's move it is by adding and subtracting all the current moves
	int state = 0;
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			state += board[i][j];

	// if the state is 0
	state = -state;
	if( state == 0 )
		state = 1;
	else
		state = -1;

	if(state == 1)
	{
		// default behavior: find any unoccupied square and make the move
		for( int i = 0; i < 3; i++ )
			for( int j = 0; j < 3; j++ )
				// find an empty square
				if( board[i][j] == 0 )
				{
					// that's the move
					printf( "player [%d] made move: [%d,%d]\n", state, i, j );
					board[i][j] = state;
					// makes move and recursively calls make move again
					make_move( board );
				}
	}else
	{
		// default behavior: find any unoccupied square and make the move
		for( int i = 0; i < 3; i++ )
			for( int j = 0; j < 3; j++ )
				// TODO: Pick an optimal move and make that move. Currently makes first avail move.
				// TODO: Fix recursive call to only preform one move instead of finishing board.
				// IDEA: Create a graded board to determine the best choice for a move.
				// find an empty square
				if( board[i][j] == 0 )
				{
					// that's the move
					printf( "player [%d] made move: [%d,%d]\n", state, i, j );
					minimaxMove( board, state );
					board[i][j] = state;
					return 1;
				}
	}



	// no move was made (board was full)
	return 0;
}

// Using a board and the current move determine the best move.
// Return a graded board to determine the best move
// Return the best move
void minimaxMove(int board[][3], int action)
{

	int gradedBoard[3][3];
	int opponentAction = action * -1;

	// copy board
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){

			if(board[i][j] != 0)
			{
				gradedBoard[i][j] = -100; // Can't make a move where there is already a move
			}else
			{
				gradedBoard[i][j] = 0; // Blank the board on empty spots
			}

		}
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){

			// there is an opponentAction here
			if(board[i][j] == opponentAction)
			{
				// Corners
				if(i == 0 && j == 0)
				{
					gradedBoard[i+1][j] += 1;
					gradedBoard[i+2][j] += 1;
					gradedBoard[i][j+1] += 1;
					gradedBoard[i][j+2] += 1;
					gradedBoard[i+1][j+1] += 1;
					gradedBoard[i+2][j+2] += 1;
				}else
				if(i == 0 && j == 2)
				{
					gradedBoard[i+1][j] += 1;
					gradedBoard[i+2][j] += 1;
					gradedBoard[i][j-1] += 1;
					gradedBoard[i][j-2] += 1;
					gradedBoard[i+1][j-1] += 1;
					gradedBoard[i+2][j-2] += 1;
				}else
				if(i == 2 && j == 0)
				{
					gradedBoard[i-1][j] += 1;
					gradedBoard[i-2][j] += 1;
					gradedBoard[i][j+1] += 1;
					gradedBoard[i][j+2] += 1;
					gradedBoard[i-1][j+1] += 1;
					gradedBoard[i-2][j+2] += 1;
				}else
				if(i == 2 && j == 2)
				{
					gradedBoard[i-1][j] += 1;
					gradedBoard[i-2][j] += 1;
					gradedBoard[i][j-1] += 1;
					gradedBoard[i][j-2] += 1;
					gradedBoard[i-1][j-1] += 1;
					gradedBoard[i-2][j-2] += 1;
				}


			}

		}
	}

}
