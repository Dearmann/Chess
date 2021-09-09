#include <iostream>
#include "chess.h"
#include "SFML/Graphics.hpp"

bool Board::isMouseClickInsideWindow(sf::Vector2i coordInPixels)
{
	if (coordInPixels.x >= 0 && coordInPixels.x <= boardSize && coordInPixels.y >= 0 && coordInPixels.y <= boardSize)
	{
		return true;
	}
	else
		return false;
}
void Board::setClickedBoardSquare(sf::Vector2i coordInPixels)
{
	xPressed = coordInPixels.x / (boardSize / 8);
	yPressed = coordInPixels.y / (boardSize / 8);
	clickedBoardSquare = boardArray[xPressed][yPressed];
}
void Board::setClickedPieceAsActive(Piece* clickedPiece)
{
	if (clickedPiece && clickedPiece != pieceCurrentlyActive && pieceCurrentlyActive == NULL)	// Activating piece
	{
		pieceCurrentlyActive = clickedPiece;
		pieceActiveVisuals.setPosition(xPressed * (boardSize / 8), yPressed * (boardSize / 8));
	}
	else if (clickedPiece && clickedPiece == pieceCurrentlyActive)	// Deactivating piece
		pieceCurrentlyActive = NULL;
}
sf::RectangleShape Board::getActivePieceVisuals()
{
	return pieceActiveVisuals;
}
Piece* Board::getActivePiece()
{
	return pieceCurrentlyActive;
}
Color Board::getCurrentTurn()
{
	return turn;
}
Piece* Board::getClickedBoardSquare()
{
	return clickedBoardSquare;
}
Piece* Board::getPiecePointer(int x, int y)
{
	return boardArray[x][y];
}
sf::Vector2i Board::getClickedCoordinates()
{
	sf::Vector2i clickedCoordinates;
	clickedCoordinates.x = xPressed;
	clickedCoordinates.y = yPressed;
	return clickedCoordinates;
}
void Board::startNewGame(Piece** p)
{ 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boardArray[i][j] = NULL;
		}
	}
	turn = Color::White;
	for (int i = 0; i < 8; i++)
	{
		p[i + 8]->changePieceLocation(i, 1);
	}
	for (int i = 0; i < 8; i++)
	{
		p[i + 16]->changePieceLocation(i, 6);
	}
	p[0]->changePieceLocation(0, 0);
	p[7]->changePieceLocation(7, 0);
	p[1]->changePieceLocation(1, 0);
	p[6]->changePieceLocation(6, 0);
	p[2]->changePieceLocation(2, 0);
	p[5]->changePieceLocation(5, 0);
	p[4]->changePieceLocation(4, 0);
	p[3]->changePieceLocation(3, 0);
	p[24]->changePieceLocation(0, 7);
	p[31]->changePieceLocation(7, 7);
	p[25]->changePieceLocation(1, 7);
	p[30]->changePieceLocation(6, 7);
	p[26]->changePieceLocation(2, 7);
	p[29]->changePieceLocation(5, 7);
	p[28]->changePieceLocation(4, 7);
	p[27]->changePieceLocation(3, 7);
	winType = 0;
	pieceCurrentlyActive = NULL;
}
void Board::setKings(Piece* whiteKing, Piece* blackKing)
{
	whiteKingPointer = whiteKing;
	blackKingPointer = blackKing;
}
int Board::getWinType()
{
	return winType;
}



void Piece::placePieceOnBoard()
{
	board->boardArray[x][y] = this;
	visualOfPiece.setPosition(sf::Vector2f(x * board->boardSize / 8, y * board->boardSize / 8));
}
sf::RectangleShape Piece::getVisualOfPiece()
{
	return this->visualOfPiece;
}
void Piece::moveActivePiece()
{
	if (board->boardArray[board->xPressed][board->yPressed] == NULL)	// Moving to empty place
	{
		int oldX = board->pieceCurrentlyActive->x;
		int oldY = board->pieceCurrentlyActive->y;
		board->pieceCurrentlyActive->x = board->xPressed;
		board->pieceCurrentlyActive->y = board->yPressed;
		board->pieceCurrentlyActive->movesMade++;
		board->pieceCurrentlyActive->placePieceOnBoard();
		board->boardArray[oldX][oldY] = NULL;
		if (board->pieceCurrentlyActive->pieceColor == Color::White)	// Turn change
			board->turn = Color::Black;
		else
			board->turn = Color::White;
		board->pieceCurrentlyActive = NULL;
	}
	else if (board->pieceCurrentlyActive->pieceColor != board->boardArray[board->xPressed][board->yPressed]->pieceColor)	// Moving to occupied place
	{
		int oldX = board->pieceCurrentlyActive->x;
		int oldY = board->pieceCurrentlyActive->y;
		removePiece(board->xPressed, board->yPressed);
		board->pieceCurrentlyActive->x = board->xPressed;
		board->pieceCurrentlyActive->y = board->yPressed;
		board->pieceCurrentlyActive->movesMade++;
		board->pieceCurrentlyActive->placePieceOnBoard();
		board->boardArray[oldX][oldY] = NULL;
		if (board->pieceCurrentlyActive->pieceColor == Color::White)	// Turn change
			board->turn = Color::Black;
		else
			board->turn = Color::White;
		board->pieceCurrentlyActive = NULL;
	}
	else if (board->pieceCurrentlyActive->pieceColor == board->boardArray[board->xPressed][board->yPressed]->pieceColor) // Castling
	{
		if (board->pieceCurrentlyActive->x == 0)
		{
			board->pieceCurrentlyActive->x = 3;
			board->pieceCurrentlyActive->movesMade++;
			board->pieceCurrentlyActive->placePieceOnBoard();
			board->boardArray[0][board->pieceCurrentlyActive->y] = NULL;
			board->boardArray[board->xPressed][board->yPressed]->x = 2;
			board->boardArray[board->xPressed][board->yPressed]->movesMade++;
			board->boardArray[board->xPressed][board->yPressed]->placePieceOnBoard();
			board->boardArray[4][board->pieceCurrentlyActive->y] = NULL;
			if (board->pieceCurrentlyActive->pieceColor == Color::White)	// Turn change
				board->turn = Color::Black;
			else
				board->turn = Color::White;
			board->pieceCurrentlyActive = NULL;
		}
		else if (board->pieceCurrentlyActive->x == 7)
		{
			board->pieceCurrentlyActive->x = 5;
			board->pieceCurrentlyActive->movesMade++;
			board->pieceCurrentlyActive->placePieceOnBoard();
			board->boardArray[7][board->pieceCurrentlyActive->y] = NULL;
			board->boardArray[board->xPressed][board->yPressed]->x = 6;
			board->boardArray[board->xPressed][board->yPressed]->movesMade++;
			board->boardArray[board->xPressed][board->yPressed]->placePieceOnBoard();
			board->boardArray[4][board->pieceCurrentlyActive->y] = NULL;
			if (board->pieceCurrentlyActive->pieceColor == Color::White)	// Turn change
				board->turn = Color::Black;
			else
				board->turn = Color::White;
			board->pieceCurrentlyActive = NULL;
		}
	}
}
void Piece::removePiece(int x, int y)
{
	if (board->boardArray[x][y] == board->whiteKingPointer)
		board->winType = 1;
	if (board->boardArray[x][y] == board->blackKingPointer)
		board->winType = 2;
	board->boardArray[x][y] = NULL;
}
std::string Piece::getPieceName()
{
	return pieceName;
}
int Piece::getMovesMade()
{
	return movesMade;
}
void Piece::changePieceLocation(int x, int y)
{
	this->x = x;
	this->y = y;
	this->movesMade = 0;
	this->placePieceOnBoard();
}

bool King::isMoveCorrect(sf::Vector2i coordinatesToMoveTo)
{
	if (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) //There is piece in destination coordinates
		&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->pieceColor == this->pieceColor) //and its' color is the same -> move is not possible
		return false;
	if ((coordinatesToMoveTo.x == x + 1 || coordinatesToMoveTo.x == x - 1 || coordinatesToMoveTo.x == x)
		&& (coordinatesToMoveTo.y == y + 1 || coordinatesToMoveTo.y == y - 1 || coordinatesToMoveTo.y == y))
		return true;
	return false;
}

bool Queen::isMoveCorrect(sf::Vector2i coordinatesToMoveTo)
{
	if (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) //There is piece in destination coordinates
		&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->pieceColor == this->pieceColor) //and its' color is the same -> move is not possible
		return false;
	int xTemp = x;
	int yTemp = y;
	if (x == coordinatesToMoveTo.x)
	{
		while (++yTemp < coordinatesToMoveTo.y)
		{
			if (board->getPiecePointer(coordinatesToMoveTo.x, yTemp)) //True == collision met
				return false;
		}
		xTemp = x;
		yTemp = y;
		while (--yTemp > coordinatesToMoveTo.y)
		{
			if (board->getPiecePointer(coordinatesToMoveTo.x, yTemp)) //True == collision met
				return false;
		}
		return true;
	}
	else if (y == coordinatesToMoveTo.y)
	{
		while (++xTemp < coordinatesToMoveTo.x)
		{
			if (board->getPiecePointer(xTemp, coordinatesToMoveTo.y)) //True == collision met
				return false;
		}
		xTemp = x;
		yTemp = y;
		while (--xTemp > coordinatesToMoveTo.x)
		{
			if (board->getPiecePointer(xTemp, coordinatesToMoveTo.y)) //True == collision met
				return false;
		}
		return true;
	}
	else if (coordinatesToMoveTo.x > xTemp && coordinatesToMoveTo.y > yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0) //Stop when coordinates run out of board
		{
			xTemp++;
			yTemp++;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL) //Return false if piece is met halfway through
				return false;
		}
	}
	else if (coordinatesToMoveTo.x > xTemp && coordinatesToMoveTo.y < yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0)
		{
			xTemp++;
			yTemp--;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL)
				return false;
		}
	}
	else if (coordinatesToMoveTo.x < xTemp && coordinatesToMoveTo.y > yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0)
		{
			xTemp--;
			yTemp++;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL)
				return false;
		}
	}
	else if (coordinatesToMoveTo.x < xTemp && coordinatesToMoveTo.y < yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0)
		{
			xTemp--;
			yTemp--;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL)
				return false;
		}
	}
	return false;
}

bool Rook::isMoveCorrect(sf::Vector2i coordinatesToMoveTo)
{
	if (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) != NULL
		&& ((board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->getPieceName() == "White king" && this->pieceColor == Color::White)
		|| (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->getPieceName() == "Black king" && this->pieceColor == Color::Black))
		&& (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->getMovesMade() == 0 && this->movesMade == 0)) //Castling requirements
	{
		if ((this->y == 0 && this->x == 0) || (this->y == 7 && this->x == 0))
		{
			for (int i = 1; i <= 3; i++)
			{
				if (board->getPiecePointer(i, y) != NULL)
					return false;
			}
		}
		else if ((this->y == 0 && this->x == 7) || (this->y == 7 && this->x == 7))
		{
			for (int i = 5; i <= 6; i++)
			{
				if (board->getPiecePointer(i, y) != NULL)
					return false;
			}
		}
		return true;
	}
	if (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) //There is piece in destination coordinates
		&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->pieceColor == this->pieceColor) //and its' color is the same -> move is not possible
		return false;
	int xTemp = x;
	int yTemp = y;
	if (x == coordinatesToMoveTo.x)
	{
		while (++yTemp < coordinatesToMoveTo.y)
		{
			if (board->getPiecePointer(coordinatesToMoveTo.x, yTemp)) //True == collision met
				return false;
		}
		xTemp = x;
		yTemp = y;
		while (--yTemp > coordinatesToMoveTo.y)
		{
			if (board->getPiecePointer(coordinatesToMoveTo.x, yTemp)) //True == collision met
				return false;
		}
		return true;
	}
	if (y == coordinatesToMoveTo.y)
	{
		while (++xTemp < coordinatesToMoveTo.x)
		{
			if (board->getPiecePointer(xTemp, coordinatesToMoveTo.y)) //True == collision met
				return false;
		}
		xTemp = x;
		yTemp = y;
		while (--xTemp > coordinatesToMoveTo.x)
		{
			if (board->getPiecePointer(xTemp, coordinatesToMoveTo.y)) //True == collision met
				return false;
		}
		return true;
	}
	return false;
}

bool Knight::isMoveCorrect(sf::Vector2i coordinatesToMoveTo)
{
	if (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) //There is piece in destination coordinates
		&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->pieceColor == this->pieceColor) //and its' color is the same -> move is not possible
		return false;
	if ((coordinatesToMoveTo.x == x + 2 || coordinatesToMoveTo.x == x - 2) && (coordinatesToMoveTo.y == y + 1 || coordinatesToMoveTo.y == y - 1))
		return true;
	if ((coordinatesToMoveTo.x == x + 1 || coordinatesToMoveTo.x == x - 1) && (coordinatesToMoveTo.y == y + 2 || coordinatesToMoveTo.y == y - 2))
		return true;
	return false;
}

bool Bishop::isMoveCorrect(sf::Vector2i coordinatesToMoveTo)
{
	if (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) //There is piece in destination coordinates
		&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->pieceColor == this->pieceColor) //and its' color is the same -> move is not possible
		return false;
	int xTemp = x;
	int yTemp = y;
	if (coordinatesToMoveTo.x > xTemp && coordinatesToMoveTo.y > yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0) //Stop when coordinates run out of board
		{
			xTemp++;
			yTemp++;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL) //Return false if piece is met halfway through
				return false;
		}
	}
	else if (coordinatesToMoveTo.x > xTemp && coordinatesToMoveTo.y < yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0)
		{
			xTemp++;
			yTemp--;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL)
				return false;
		}
	}
	else if (coordinatesToMoveTo.x < xTemp && coordinatesToMoveTo.y > yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0)
		{
			xTemp--;
			yTemp++;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL)
				return false;
		}
	}
	else if (coordinatesToMoveTo.x < xTemp && coordinatesToMoveTo.y < yTemp)
	{
		while (xTemp <= 7 && xTemp >= 0 && yTemp <= 7 && yTemp >= 0)
		{
			xTemp--;
			yTemp--;
			if (xTemp == coordinatesToMoveTo.x && yTemp == coordinatesToMoveTo.y)
				return true;
			if (board->getPiecePointer(xTemp, yTemp) != NULL)
				return false;
		}
	}
	return false;
}

bool Pawn::isMoveCorrect(sf::Vector2i coordinatesToMoveTo)
{
	if (board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) //There is piece in destination coordinates
		&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y)->pieceColor == this->pieceColor) //and its' color is the same -> move is not possible
		return false;
	if (this->pieceColor == Color::White)
	{
		if (coordinatesToMoveTo.y == y - 1 && coordinatesToMoveTo.x == x && board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) == NULL)
			return true;
		if (coordinatesToMoveTo.y == y - 2 && coordinatesToMoveTo.x == x
			&& this->movesMade == 0
			&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) == NULL
			&& board->getPiecePointer(x, y - 1) == NULL)
			return true;
		if (coordinatesToMoveTo.y == y - 1 && (coordinatesToMoveTo.x == x + 1 || coordinatesToMoveTo.x == x - 1)
			&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) != NULL)
			return true;
		return false;
	}
	else //Black pawn
	{
		if (coordinatesToMoveTo.y == y + 1 && coordinatesToMoveTo.x == x && board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) == NULL)
			return true;
		if (coordinatesToMoveTo.y == y + 2 && coordinatesToMoveTo.x == x
			&& this->movesMade == 0
			&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) == NULL
			&& board->getPiecePointer(x, y + 1) == NULL)
			return true;
		if (coordinatesToMoveTo.y == y + 1 && (coordinatesToMoveTo.x == x + 1 || coordinatesToMoveTo.x == x - 1)
			&& board->getPiecePointer(coordinatesToMoveTo.x, coordinatesToMoveTo.y) != NULL)
			return true;
		return false;
	}
}