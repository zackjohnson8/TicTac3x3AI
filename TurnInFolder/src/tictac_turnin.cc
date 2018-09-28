#include <tictac_support.h>
#include <stdio.h>
#include <iostream>

struct positionCordinates{
	int x;
	int y;
};

using namespace std;

//positionCordinates minimaxMove(int board[][3], int action);

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

bool isMovesLeft(int board[][3]);
positionCordinates bestMove(int board [][3], int state);
int minimax(int board[][3], int depth, bool isMax, int state);
int evaluate(int b[][3], int state);
bool gameWinningMoveCheck(int b[][3], int state);

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

	positionCordinates chosenMove;
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
					return make_move( board );
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


					///// Determine if this move is a winning move ///
					for( int i = 0; i < 3; i++ ){
						for( int j = 0; j < 3; j++ ){
							if(board[i][j] == 0)
							{
								board[i][j] = state;

								if(gameWinningMoveCheck(board, state))
								{
									chosenMove.x = i;
									chosenMove.y = j;
									printf( "player [%d] made move: [%d,%d]\n", state, chosenMove.x, chosenMove.y );
									return 1;
								}else
								{
									board[i][j] = 0;
								}
							}
						}
					}
					////////
					///// Determine if next opponent move is winning move ///
					for( int i = 0; i < 3; i++ ){
						for( int j = 0; j < 3; j++ ){
							if(board[i][j] == 0)
							{
								board[i][j] = state * -1;

								if(gameWinningMoveCheck(board, state * -1))
								{
									chosenMove.x = i;
									chosenMove.y = j;
									board[i][j] = state;
									printf( "player [%d] made move: [%d,%d]\n", state, chosenMove.x, chosenMove.y );
									return 1;
								}else
								{
									board[i][j] = 0;
								}
							}
						}
					}
					////////
					chosenMove = bestMove( board, state );
					printf( "player [%d] made move: [%d,%d]\n", state, chosenMove.x, chosenMove.y );
					board[chosenMove.x][chosenMove.y] = state;
					return 1;
				}
	}



	// no move was made (board was full)
	return 0;
}

bool gameWinningMoveCheck(int b[][3], int state)
{


	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++)
	{
			if (b[row][0]==b[row][1] &&
					b[row][1]==b[row][2])
			{
					if (b[row][0]==state)
							return true;

			}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
			if (b[0][col]==b[1][col] &&
					b[1][col]==b[2][col])
			{
					if (b[0][col]==state)
							return true;
			}
	}

	// Checking for Diagonals for X or O victory.
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
	{
			if (b[0][0]==state)
					return true;
	}

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
	{
			if (b[0][2]==state)
					return true;
	}

	// Else if none of them have won then return 0
	return false;

}


// Using a board and the current move determine the best move.
// Return a graded board to determine the best move
// Return the best move
// TODO: May Remove
/*positionCordinates minimaxMove(int board[][3], int action)
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
				}else // Middle N,S,E,W
				if(i == 0 && j == 1)
				{
					gradedBoard[i+1][j] += 1;
					gradedBoard[i+2][j] += 1;
					gradedBoard[i][j-1] += 1;
					gradedBoard[i][j+1] += 1;
				}else
				if(i == 1 && j == 0)
				{
					gradedBoard[i+1][j] += 1;
					gradedBoard[i-1][j] += 1;
					gradedBoard[i][j+1] += 1;
					gradedBoard[i][j+2] += 1;
				}else
				if(i == 1 && j == 2)
				{
					gradedBoard[i+1][j] += 1;
					gradedBoard[i-1][j] += 1;
					gradedBoard[i][j-1] += 1;
					gradedBoard[i][j-2] += 1;
				}else
				if(i == 2 && j == 1)
				{
					gradedBoard[i-1][j] += 1;
					gradedBoard[i-2][j] += 1;
					gradedBoard[i][j-1] += 1;
					gradedBoard[i][j+1] += 1;
				}
				// Center Spot
				else
				if(i == 1 && j == 1)
				{
					gradedBoard[i-1][j-1] += 1; // top left
					gradedBoard[i-1][j] += 1; // top mid
					gradedBoard[i-1][j+1] += 1; // top right
					gradedBoard[i][j-2] += 1; // mid left
					gradedBoard[i][j+1] += 1; // mid right
					gradedBoard[i+1][j-1] += 1; // bot left
					gradedBoard[i+1][j] += 1; // bot mid
					gradedBoard[i+1][j+1] += 1; // bot right
				}else
				{
					// Position doesn't exist
					std::cout << "position does not exist on board (tictac_turnin.cc Line 170)" << std::endl;
				}


			}

		}
	}

	// Determine best position
	int highestPosition = -100;
	positionCordinates bestMove;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(gradedBoard[i][j] >= highestPosition)
			{
				highestPosition = gradedBoard[i][j];
				bestMove.x = i;
				bestMove.y = j;
			}
		}
	}

	return bestMove;

}
*/

positionCordinates bestMove(int board[][3], int state)
{
		int bestVal = -1000;
    positionCordinates bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

		//if(winThisTurn)
		//{

		//}

    // Traverse all cells, evalutae minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]==0)
            {
                // Make the move
                board[i][j] = state;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false, state);

                // Undo the move
                board[i][j] = 0;

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.x = i;
                    bestMove.y = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(int board[][3], int depth, bool isMax, int state)
{

		int opponent = state * -1;

    int score = evaluate(board, state);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(board)==false)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==0)
                {
                    // Make the move
                    board[i][j] = state;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = max( best,
                        minimax(board, depth+1, !isMax, state) );

                    // Undo the move
                    board[i][j] = 0;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==0)
                {
                    // Make the move
                    board[i][j] = opponent;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                           minimax(board, depth+1, !isMax, state));

                    // Undo the move
                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
}

// This is the evaluation function as discussed
// in the previous article ( http://goo.gl/sJgv68 )
int evaluate(int b[][3], int state)
{

		int opponent = state * -1;

    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==state)
                return +10;
            else if (b[row][0]==opponent)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==state)
                return +10;

            else if (b[0][col]==opponent)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==state)
            return +10;
        else if (b[0][0]==opponent)
            return -10;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==state)
            return +10;
        else if (b[0][2]==opponent)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(int board[][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]==0)
                return true;
    return false;
}
