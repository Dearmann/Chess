/** @file */

#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include "SFML/Graphics.hpp"

enum class Color { White, Black }; ///< Kolor do opisu figur szachowych i tury gracza.
enum class PieceType { King, Queen, Rook, Knight, Bishop, Pawn, Abstract }; ///< Typ figury szachowej.

class Piece;
class Board
{
	friend class Piece; 					///< Zaprzyjaźnienie umożliwia realizacje wielu powiązanych metod pomiędzy tymi klasami.
	Piece* boardArray[8][8]; 				///< Tablica dwuwymiarowa reprezentująca szachownice.
	Color turn = Color::White; 				///< Zmienna opisująca aktualną turę gracza.
	float boardSize; 						///< Rozmiar szachownicy w pikselach.
	int xPressed, yPressed;					///< Koordynaty klikniętego miejsca lewym przyciskiem myszy. Przyjmują wartości <0, 7>.
	Piece* pieceCurrentlyActive = NULL;		///< Wskaźnik na aktywną figurę - tylko aktywna figura może się poruszać. Aktywacja odbywa się kliknięciem myszy.
	sf::RectangleShape pieceActiveVisuals;	///< Grafika pola na którym znajduje się aktywowana figura.
	Piece* clickedBoardSquare = NULL;		///< Wskaźnik klikniętego pola szachownicy - może wynosić NULL.
	Piece* whiteKingPointer = NULL;			///< Wskaźnik białego króla.
	Piece* blackKingPointer = NULL;			///< Wskaźnik czarnego króla.
	int winType = 0;						///< Typ wygranej: 0 - aktualnie nikt nie wygrał, 1 - wygrał gracz biały, 2 - wygrał gracz czarny.
public:
	/**
 	 * @brief Tworzy nowy objekt typu Board.
 	 * 
	 * @param boardSizeToSet Wartość w pikselach określająca wielkość szachownicy.
	 * @param pieceActiveVisualsToSet Grafika pola na którym znajduje się aktywowana figura.
	 */
	Board(float boardSizeToSet, sf::RectangleShape pieceActiveVisualsToSet)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardArray[i][j] = NULL;
			}
		}
		boardSize = boardSizeToSet;
		pieceActiveVisuals = pieceActiveVisualsToSet;
	}
	/**
	 * @brief Niszczy objekt typu Board. Iteruje przez wszystkie pola szachownicy i usuwa wszystkie figury.
	 * 
	 */
	~Board()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				delete boardArray[i][j];
			}
		}
	}
	/**
	 * @brief Sprawdza czy koordynaty kliknięcia myszą znajdują się w obrębie szachownicy. Kliknięcie interfejsu pod szachownicą zwraca false.
	 * 
	 * @param coordInPixels Koordynaty w pikselach kliknięte myszą.
	 * @return true - gdy koordynaty są od 0 do boardSize
	 * @return false - gdy koordynaty wychodzą poza szachownicę
	 */
	bool isMouseClickInsideWindow(sf::Vector2i coordInPixels);
	/**
	 * @brief Ustawia wskaźnik klikniętego pola w zmiennej clickedBoardSquare - może wynosić NULL.
	 * 
	 * @param coordInPixels Koordynaty w pikselach kliknięte myszą.
	 */
	void setClickedBoardSquare(sf::Vector2i coordInPixels);
	/**
	 * @brief Aktywuje figurę - przygotowuje ją do ruchu, jeżeli nie ma aktualnie aktywnej innej figury. Jeżeli kliknięta figura jest już aktywna następuje jej deaktywacja.
	 * 
	 * @param clickedPiece Wskaźnik figury która ma zostać aktywowana.
	 */
	void setClickedPieceAsActive(Piece* clickedPiece);
	/**
	 * @brief Zwraca grafike pola na którym znajduje się aktywowana figura.
	 * 
	 * @return sf::RectangleShape Grafika pola na którym znajduje się aktywowana figura.
	 */
	sf::RectangleShape getActivePieceVisuals();
	/**
	 * @brief Zwraca wskaźnik na aktywną figurę.
	 * 
	 * @return Piece* wskaźnik na aktywną figurę.
	 */
	Piece* getActivePiece();
	/**
	 * @brief Zwraca zmienną opisującą aktualną turę gracza.
	 * 
	 * @return Color Zmienna opisująca aktualną turę gracza.
	 */
	Color getCurrentTurn();
	/**
	 * @brief Zwraca wskaźnik klikniętego pola szachownicy - może wynosić NULL.
	 * 
	 * @return Piece* Wskaźnik klikniętego pola szachownicy - może wynosić NULL.
	 */
	Piece* getClickedBoardSquare();
	/**
	 * @brief Zwraca wskaźnik na figurę szachową która znajduje się na koordynatach przekazanych w parametrach metody.
	 * 
	 * @param x Koordynat X szachownicy - szerokość.
	 * @param y Koordynat Y szachownicy - wysokość.
	 * @return Piece* Wskaźnik figury szachowej na podanych koordynatach.
	 */
	Piece* getPiecePointer(int x, int y);
	/**
	 * @brief Zwraca kliknięte koordynaty w postaci wektoru.
	 * 
	 * @return sf::Vector2i Kliknięte koordynaty w postaci wektoru.
	 */
	sf::Vector2i getClickedCoordinates();
	/**
	 * @brief Resetuje szachownicę do stanu początkowego: turę ma gracz biały, wszystkie figury na swoich początkowych koordynatach, brak gracza który wygrał, brak aktywnej figury.
	 * 
	 * @param p Wskaźnik na tablicę wszystkich figur. Ma 32 elementy.
	 */
	void startNewGame(Piece** p);
	/**
	 * @brief Przekazuje objektowi typu Board informację o tym które ze wskaźników na szachownicy są królami.
	 * 
	 * @param whiteKing Wskaźnik na króla białego.
	 * @param blackKing Wskaźnik na króla czarnego.
	 */
	void setKings(Piece* whiteKing, Piece* blackKing);
	/**
	 * @brief Zwraca typ wygranej.
	 * 
	 * @return int 0 - aktualnie nikt nie wygrał, 1 - wygrał gracz biały, 2 - wygrał gracz czarny.
	 */
	int getWinType();
};

class Piece
{
protected:
	Board* board = NULL; ///< Wskaźnik na szachownicę. Każda z figur wie na jakiej szachownicy się znajduje.
	int x = 0, y = 0; ///< Koordynaty na których znajduje się figura.
	int movesMade = 0; ///< Ilość wykonanych ruchów przez figurę.
	sf::RectangleShape visualOfPiece; ///< Grafika figury szachowej.
	std::string pieceName = "Abstract piece"; ///< Nazwa figury.
	PieceType pieceType = PieceType::Abstract; ///< Typ figury.
public:
	Color pieceColor = Color::White; ///< Kolor figury.
	/**
	 * @brief Tworzy nowy objekt typu Piece.
	 * 
	 */
	Piece()
	{
		board = NULL;
	}
	/**
	 * @brief Metoda wirtualna - każda z sześciu podklas klasy Piece zawiera swój polimorficzny odpowiednik tej metody. Określa czy ruch wykonany przez figurę jest możliwy.
	 * 
	 * @param clickedCoordinates Koordynaty do których poprawność przemieszczenia figury ma zostać sprawdzona.
	 * @return true - ruch prawidłowy.
	 * @return false - ruch nieprawidłowy.
	 */
	virtual bool isMoveCorrect(sf::Vector2i clickedCoordinates) = 0;
	/**
	 * @brief Umieszcza wskaźnik figury w odpowiednim miejscu tablicy boardArray klasy Board oraz przemieszcza grafikę figury w odpowiednie miejsce szachownicy.
	 * 
	 */
	void placePieceOnBoard();
	/**
	 * @brief Zwraca grafike figury szachowej.
	 * 
	 * @return sf::RectangleShape Grafika figury szachowej.
	 */
	sf::RectangleShape getVisualOfPiece();
	/**
	 * @brief Metoda realizuje przemieszczenie się figur, jest ograniczona przez metodę isMoveCorrect.
	 * Przemieszczanie się obejmuje:
	 * - ruch do miejsca pustego
	 * - ruch do miejsca już zajętego
	 * - roszada pomiędzy królem a wieżą
	 * 
	 */
	void moveActivePiece();
	/**
	 * @brief Usuwa figurę z boardArray klasy Board z koordynatów podanych w parametrach metody. Wykrywa czy usuniętą figurą jest któryś z królów i określa zwycięzce.
	 * 
	 * @param x Koordynat X szachownicy - szerokość.
	 * @param y Koordynat Y szachownicy - wysokość.
	 */
	void removePiece(int x, int y);
	/**
	 * @brief Zwraca nazwę figury.
	 * 
	 * @return std::string Nazwa figury.
	 */
	std::string getPieceName();
	/**
	 * @brief Zwraca ilość wykonanych ruchów przez figurę.
	 * 
	 * @return int Ilość wykonanych ruchów przez figurę.
	 */
	int getMovesMade();
	/**
	 * @brief Zmienia lokacje figury. Zmiana odbywa się w dwóch miejscach: na zmiennych x i y objektu na którym metoda jest wykonywana oraz w tablicy boardArray reprezentującej szachownicę w klasie Board.
	 * 
	 * @param x Koordynat X szachownicy - szerokość.
	 * @param y Koordynat Y szachownicy - wysokość.
	 */
	void changePieceLocation(int x, int y);

};

class King : public Piece
{
public:
	/**
 	 * @brief Tworzy nowy objekt typu King dziedziczący z klasy Piece.
 	 * 
 	 * @param board_ Wskaźnik na szachownicę. Każda z figur wie na jakiej szachownicy się znajduje.
 	 * @param x_ Koordynat X szachownicy na którym znajduje się figura - szerokość.
 	 * @param y_ Koordynat Y szachownicy na którym znajduje się figura - wysokość.
 	 * @param pieceColor_ Kolor figury.
 	 * @param pieceShape_ Grafika figury szachowej.
 	 */
	King(Board* board_, int x_, int y_, Color pieceColor_, sf::RectangleShape pieceShape_)
	{
		board = board_;
		x = x_;
		y = y_;
		movesMade = 0;
		pieceColor = pieceColor_;
		visualOfPiece = pieceShape_;
		if (pieceColor == Color::White)
			pieceName = "White king";
		else
			pieceName = "Black king";
		pieceType = PieceType::King;
		this->placePieceOnBoard();
	}
	bool isMoveCorrect(sf::Vector2i coordinatesToMoveTo);
};

class Queen : public Piece
{
public:
	/**
 	 * @brief Tworzy nowy objekt typu Queen dziedziczący z klasy Piece.
 	 * 
 	 * @param board_ Wskaźnik na szachownicę. Każda z figur wie na jakiej szachownicy się znajduje.
 	 * @param x_ Koordynat X szachownicy na którym znajduje się figura - szerokość.
 	 * @param y_ Koordynat Y szachownicy na którym znajduje się figura - wysokość.
 	 * @param pieceColor_ Kolor figury.
 	 * @param pieceShape_ Grafika figury szachowej.
 	 */
	Queen(Board* board_, int x_, int y_, Color pieceColor_, sf::RectangleShape pieceShape_)
	{
		board = board_;
		x = x_;
		y = y_;
		movesMade = 0;
		pieceColor = pieceColor_;
		visualOfPiece = pieceShape_;
		if (pieceColor == Color::White)
			pieceName = "White queen";
		else
			pieceName = "Black queen";
		pieceType = PieceType::Queen;
		this->placePieceOnBoard();
	}
	bool isMoveCorrect(sf::Vector2i coordinatesToMoveTo);
};

class Rook : public Piece
{
public:
	/**
 	 * @brief Tworzy nowy objekt typu Rook dziedziczący z klasy Piece.
 	 * 
 	 * @param board_ Wskaźnik na szachownicę. Każda z figur wie na jakiej szachownicy się znajduje.
 	 * @param x_ Koordynat X szachownicy na którym znajduje się figura - szerokość.
 	 * @param y_ Koordynat Y szachownicy na którym znajduje się figura - wysokość.
 	 * @param pieceColor_ Kolor figury.
 	 * @param pieceShape_ Grafika figury szachowej.
 	 */
	Rook(Board* board_, int x_, int y_, Color pieceColor_, sf::RectangleShape pieceShape_)
	{
		board = board_;
		x = x_;
		y = y_;
		movesMade = 0;
		pieceColor = pieceColor_;
		visualOfPiece = pieceShape_;
		if (pieceColor == Color::White)
			pieceName = "White rook";
		else
			pieceName = "Black rook";
		pieceType = PieceType::Rook;
		this->placePieceOnBoard();
	}
	bool isMoveCorrect(sf::Vector2i coordinatesToMoveTo);
};

class Knight : public Piece
{
public:
	/**
 	 * @brief Tworzy nowy objekt typu Knight dziedziczący z klasy Piece.
 	 * 
 	 * @param board_ Wskaźnik na szachownicę. Każda z figur wie na jakiej szachownicy się znajduje.
 	 * @param x_ Koordynat X szachownicy na którym znajduje się figura - szerokość.
 	 * @param y_ Koordynat Y szachownicy na którym znajduje się figura - wysokość.
 	 * @param pieceColor_ Kolor figury.
 	 * @param pieceShape_ Grafika figury szachowej.
 	 */
	Knight(Board* board_, int x_, int y_, Color pieceColor_, sf::RectangleShape pieceShape_)
	{
		board = board_;
		x = x_;
		y = y_;
		movesMade = 0;
		pieceColor = pieceColor_;
		visualOfPiece = pieceShape_;
		if (pieceColor == Color::White)
			pieceName = "White knight";
		else
			pieceName = "Black knight";
		pieceType = PieceType::Knight;
		this->placePieceOnBoard();
	}
	bool isMoveCorrect(sf::Vector2i coordinatesToMoveTo);
};

class Bishop : public Piece
{
public:
	/**
 	 * @brief Tworzy nowy objekt typu Bishop dziedziczący z klasy Piece.
 	 * 
 	 * @param board_ Wskaźnik na szachownicę. Każda z figur wie na jakiej szachownicy się znajduje.
 	 * @param x_ Koordynat X szachownicy na którym znajduje się figura - szerokość.
 	 * @param y_ Koordynat Y szachownicy na którym znajduje się figura - wysokość.
 	 * @param pieceColor_ Kolor figury.
 	 * @param pieceShape_ Grafika figury szachowej.
 	 */
	Bishop(Board* board_, int x_, int y_, Color pieceColor_, sf::RectangleShape pieceShape_)
	{
		board = board_;
		x = x_;
		y = y_;
		movesMade = 0;
		pieceColor = pieceColor_;
		visualOfPiece = pieceShape_;
		if (pieceColor == Color::White)
			pieceName = "White bishop";
		else
			pieceName = "Black bishop";
		pieceType = PieceType::Bishop;
		this->placePieceOnBoard();
	}
	bool isMoveCorrect(sf::Vector2i coordinatesToMoveTo);
};

class Pawn : public Piece
{
public:
	/**
 	 * @brief Tworzy nowy objekt typu Pawn dziedziczący z klasy Piece.
 	 * 
 	 * @param board_ Wskaźnik na szachownicę. Każda z figur wie na jakiej szachownicy się znajduje.
 	 * @param x_ Koordynat X szachownicy na którym znajduje się figura - szerokość.
 	 * @param y_ Koordynat Y szachownicy na którym znajduje się figura - wysokość.
 	 * @param pieceColor_ Kolor figury.
 	 * @param pieceShape_ Grafika figury szachowej.
 	 */
	Pawn(Board* board_, int x_, int y_, Color pieceColor_, sf::RectangleShape pieceShape_)
	{
		board = board_;
		x = x_;
		y = y_;
		movesMade = 0;
		pieceColor = pieceColor_;
		visualOfPiece = pieceShape_;
		if (pieceColor == Color::White)
			pieceName = "White pawn";
		else
			pieceName = "Black pawn";
		pieceType = PieceType::Pawn;
		this->placePieceOnBoard();
	}
	bool isMoveCorrect(sf::Vector2i coordinatesToMoveTo);
};

#endif