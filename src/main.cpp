#include <iostream>
#include "chess.h"
#include "SFML/Graphics.hpp"
#include <chrono>
#include <thread>

int main()
{
    float boardSize = 800;    // Board size in pixels
    // Loading textures
    sf::Texture boardTexture, wrookTexture, wknightTexture, wbishopTexture, wqueenTexture, wkingTexture, wpawnTexture, brookTexture, bknightTexture, bbishopTexture, bqueenTexture, bkingTexture, bpawnTexture;
    boardTexture.loadFromFile("./img/Chessboard800x800px.png");
    wrookTexture.loadFromFile("./img/wrook.png");
    wknightTexture.loadFromFile("./img/wknight.png");
    wbishopTexture.loadFromFile("./img/wbishop.png");
    wqueenTexture.loadFromFile("./img/wqueen.png");
    wkingTexture.loadFromFile("./img/wking.png");
    wpawnTexture.loadFromFile("./img/wpawn.png");
    brookTexture.loadFromFile("./img/brook.png");
    bknightTexture.loadFromFile("./img/bknight.png");
    bbishopTexture.loadFromFile("./img/bbishop.png");
    bqueenTexture.loadFromFile("./img/bqueen.png");
    bkingTexture.loadFromFile("./img/bking.png");
    bpawnTexture.loadFromFile("./img/bpawn.png");
    // Creating visuals of board and pieces
    sf::RectangleShape boardBackground(sf::Vector2f(boardSize, boardSize));
    sf::RectangleShape scoreBackground(sf::Vector2f(boardSize, boardSize + boardSize / 12));
    sf::RectangleShape pieceActiveVisual(sf::Vector2f(boardSize / 8, boardSize / 8));
    sf::RectangleShape pieceVisual[32];
    sf::CircleShape possibleMovementVisual[8][8];
    for (int i = 0; i < 32; i++)
    {
        pieceVisual[i].setSize(sf::Vector2f(boardSize / 8, boardSize / 8));
    }
    sf::Font font;
    font.loadFromFile("external/arial.ttf");
    sf::Text turnText, winText, newGameInformation;
    turnText.setFont(font);
    turnText.setPosition(10, boardSize);
    turnText.setCharacterSize(50);
    winText.setFont(font);
    winText.setPosition(10, boardSize);
    winText.setCharacterSize(50);
    newGameInformation.setFont(font);
    newGameInformation.setString("Press \"Enter\" to start a new game");
    newGameInformation.setPosition(boardSize - newGameInformation.getGlobalBounds().width - 15, boardSize + 15);
    newGameInformation.setCharacterSize(30);
    // Assigning textures
    boardBackground.setTexture(&boardTexture);
    scoreBackground.setFillColor(sf::Color(232, 173, 115, 255));
    pieceActiveVisual.setFillColor(sf::Color(153, 255, 153, 80));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            possibleMovementVisual[i][j].setOrigin(boardSize / 64, boardSize / 64);
            possibleMovementVisual[i][j].setRadius(boardSize / 64);
            possibleMovementVisual[i][j].setFillColor(sf::Color(100, 170, 100, 200));
            possibleMovementVisual[i][j].setPosition((boardSize / 8) * i + boardSize / 16, (boardSize / 8) * j + boardSize / 16);
        }
    }
    for (int i = 8; i < 16; i++)
    {
        pieceVisual[i].setTexture(&bpawnTexture);
    }
    for (int i = 16; i < 24; i++)
    {
        pieceVisual[i].setTexture(&wpawnTexture);
    }
    pieceVisual[0].setTexture(&brookTexture);
    pieceVisual[7].setTexture(&brookTexture);
    pieceVisual[1].setTexture(&bknightTexture);
    pieceVisual[6].setTexture(&bknightTexture);
    pieceVisual[2].setTexture(&bbishopTexture);
    pieceVisual[5].setTexture(&bbishopTexture);
    pieceVisual[4].setTexture(&bkingTexture);
    pieceVisual[3].setTexture(&bqueenTexture);
    pieceVisual[24].setTexture(&wrookTexture);
    pieceVisual[31].setTexture(&wrookTexture);
    pieceVisual[25].setTexture(&wknightTexture);
    pieceVisual[30].setTexture(&wknightTexture);
    pieceVisual[26].setTexture(&wbishopTexture);
    pieceVisual[29].setTexture(&wbishopTexture);
    pieceVisual[28].setTexture(&wkingTexture);
    pieceVisual[27].setTexture(&wqueenTexture);
    // Creating board and pieces objects
    Board board(boardSize, pieceActiveVisual);
    Piece* p[32];
    for (int i = 0; i < 8; i++)
    {
        p[i + 8] = new Pawn(&board, i, 1, Color::Black, pieceVisual[i + 8]);
    }
    for (int i = 0; i < 8; i++)
    {
        p[i + 16] = new Pawn(&board, i, 6, Color::White, pieceVisual[i + 16]);
    }
    p[0] = new Rook(&board, 0, 0, Color::Black, pieceVisual[0]);
    p[7] = new Rook(&board, 7, 0, Color::Black, pieceVisual[7]);
    p[1] = new Knight(&board, 1, 0, Color::Black, pieceVisual[1]);
    p[6] = new Knight(&board, 6, 0, Color::Black, pieceVisual[6]);
    p[2] = new Bishop(&board, 2, 0, Color::Black, pieceVisual[2]);
    p[5] = new Bishop(&board, 5, 0, Color::Black, pieceVisual[5]);
    p[4] = new King(&board, 4, 0, Color::Black, pieceVisual[4]);
    p[3] = new Queen(&board, 3, 0, Color::Black, pieceVisual[3]);
    p[24] = new Rook(&board, 0, 7, Color::White, pieceVisual[24]);
    p[31] = new Rook(&board, 7, 7, Color::White, pieceVisual[31]);
    p[25] = new Knight(&board, 1, 7, Color::White, pieceVisual[25]);
    p[30] = new Knight(&board, 6, 7, Color::White, pieceVisual[30]);
    p[26] = new Bishop(&board, 2, 7, Color::White, pieceVisual[26]);
    p[29] = new Bishop(&board, 5, 7, Color::White, pieceVisual[29]);
    p[28] = new King(&board, 4, 7, Color::White, pieceVisual[28]);
    p[27] = new Queen(&board, 3, 7, Color::White, pieceVisual[27]);
    board.setKings(p[4], p[28]);
    // Displaying window
    sf::RenderWindow window(sf::VideoMode(boardSize, boardSize + boardSize / 12), "Chess", sf::Style::Close | sf::Style::Titlebar);
    sf::Vector2i mousePosition;
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mousePosition = sf::Mouse::getPosition(window);
            if (board.isMouseClickInsideWindow(mousePosition) && board.getWinType() == 0)
            {
                board.setClickedBoardSquare(mousePosition);
                if (board.getClickedBoardSquare()) //First mouse click - activating/deactivating piece
                {
                    if (board.getCurrentTurn() == board.getClickedBoardSquare()->pieceColor)
                    {
                        board.setClickedPieceAsActive(board.getClickedBoardSquare());
                    }
                }
                if (board.getActivePiece()) //Second mouse click, when piece is active - moving piece
                {
                    if (board.getActivePiece()->isMoveCorrect(board.getClickedCoordinates()))
                    {
                        board.getActivePiece()->moveActivePiece();
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            board.startNewGame(p);
        }
        window.clear();
        window.draw(scoreBackground);
        window.draw(boardBackground);
        if (board.getActivePiece())
        {
            window.draw(board.getActivePieceVisuals());
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board.getPiecePointer(i, j) != NULL)
                {
                    window.draw(board.getPiecePointer(i, j)->getVisualOfPiece());
                }
            }
        }
        if (board.getActivePiece())
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    sf::Vector2i coordinatesToCheckMovement(i, j);
                    if (board.getActivePiece()->isMoveCorrect(coordinatesToCheckMovement))
                    {
                        window.draw(possibleMovementVisual[i][j]);
                    }
                }
            }
        }
        if (board.getWinType())
        {
            if (board.getWinType() == 1)
            {
                winText.setString("White Wins");
                winText.setFillColor(sf::Color::White);
                newGameInformation.setFillColor(sf::Color::White);
                window.draw(winText);
                window.draw(newGameInformation);
            }
            else if (board.getWinType() == 2)
            {
                winText.setString("Black Wins");
                winText.setFillColor(sf::Color::Black);
                newGameInformation.setFillColor(sf::Color::Black);
                window.draw(winText);
                window.draw(newGameInformation);
            }
        }
        else
        {
            if (board.getCurrentTurn() == Color::White)
            {
                turnText.setString("Turn:  White");
                turnText.setFillColor(sf::Color::White);
                window.draw(turnText);
            }  
            else
            {
                turnText.setString("Turn:  Black");
                turnText.setFillColor(sf::Color::Black);
                window.draw(turnText);
            }
        }
        window.display();
    }
}