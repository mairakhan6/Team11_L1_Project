#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "game.hpp"


//laiba - board screen with the board grid playerinfo and time(not the pieces)
//maira whole logic - movement, move validation, gameStatus, turn checker, pieces set up/display
Game::Game(sf::RenderWindow& window, sf::Color c1, sf::Color c2, const std::string& player1, const std::string& player2, int timerLimit, const std::string& theme)
    : window(window),isOver(false), whiteTurn(true), 
        player1Name(player1), player2Name(player2), timerLimit(timerLimit), 
            player1Timer(timerLimit, sf::Vector2f(50.f, 20.f)),  player2Timer(timerLimit, sf::Vector2f(600.f, 20.f)), theme(theme)
{
    gameOverScreen = nullptr; //doesnt exist at this point



    font.loadFromFile("fonts/english.ttf");
    // buttons
    // turn.setFont(font);
    // turn.setCharacterSize(30);
    // turn.setStyle(sf::Text::Regular);
    // turn.setFillColor(sf::Color::White);
    // turn.setPosition(880.f, 70.f);


    //laiba
    chance.setFont(font);
    chance.setCharacterSize(30);
    chance.setStyle(sf::Text::Regular);
    chance.setFillColor(sf::Color(92, 59, 39));
    chance.setPosition(860, 400.f);

    setPlayerInfo(player1,player2);

    // situation.setFont(font);
    // situation.setCharacterSize(30);
    // situation.setStyle(sf::Text::Regular);
    // situation.setFillColor(sf::Color::White);
    // situation.setPosition(910, chance.getPosition().y + 50.f);
    //one each, initilaising
    w_king = new King(1);
    whitePieces.push_back(w_king);
    w_queen = new Queen(1);
    whitePieces.push_back(w_queen);
    b_king = new King(0);
    blackPieces.push_back(b_king);
    b_queen = new Queen(0);
    blackPieces.push_back(b_queen);
    //8 pawns up front row
    for (int i = 0; i < 8; i++)
    {
        b_pawn[i] = new Pawn(0);
        blackPieces.push_back(b_pawn[i]);
        w_pawn[i] = new Pawn(1);
        whitePieces.push_back(w_pawn[i]);
    }
    //2 each of bishop, rook, knight
    for (int i = 0; i < 2; i++)
    {
        w_bishop[i] = new Bishop(1);
        whitePieces.push_back(w_bishop[i]);
        w_rook[i] = new Rook(1);
        whitePieces.push_back(w_rook[i]);
        w_knight[i] = new Knight(1);
        whitePieces.push_back(w_knight[i]);
        b_bishop[i] = new Bishop(0);
        blackPieces.push_back(b_bishop[i]);
        b_rook[i] = new Rook(0);
        blackPieces.push_back(b_rook[i]);
        b_knight[i] = new Knight(0);
        blackPieces.push_back(b_knight[i]);
    }
    //setting up the board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cells[i][j].x = i;
            cells[i][j].y = j;
        }
    }

    Start(c1, c2);
}
//maira
void Game::display(sf::RenderWindow& window) {
// Label for restarting
    sf::Event e;
    while (window.isOpen()) {
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::MouseButtonPressed) {
                    if (e.mouseButton.x >= 0 && e.mouseButton.x <= 800 && e.mouseButton.y >= 0 && e.mouseButton.y <= 800) {
                        int x = e.mouseButton.y / 100, y = e.mouseButton.x / 100;
                        if (!getSelected() && !isOver) {
                            SelectPiece(cells, x, y);
                        } else {
                            moveSelected(cells, x, y);
                        }
                    }
                
            }
        }

        // Draw the game (Chess board, pieces, etc.)
        window.clear();
        window.draw(*this); // Assuming you're drawing the game from within the Game class
        handleEvents(window);
        window.display();
    }
}
//maira +laiba
void Game::Start(sf::Color c1, sf::Color c2)
{
    isOver = false;
    gameStatus = true;
    whiteTurn = 1;
    selected = false;
    selected_piece = NULL;

    for (int i = 0; i < 8; i++)
    {
        // setting up pawns
        b_pawn[i]->y = i;
        b_pawn[i]->piece.setPosition(b_pawn[i]->y * 100.f + 50.f, b_pawn[i]->x * 100.f + 50.f);
        b_pawn[i]->piece.setOrigin(sf::Vector2f(b_pawn[i]->piece.getTexture()->getSize().x / 2, b_pawn[i]->piece.getTexture()->getSize().y / 2));
        b_pawn[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
        w_pawn[i]->y = i;
        w_pawn[i]->piece.setPosition(w_pawn[i]->y * 100.f + 50.f, w_pawn[i]->x * 100.f + 50.f);
        w_pawn[i]->piece.setOrigin(sf::Vector2f(w_pawn[i]->piece.getTexture()->getSize().x / 2, w_pawn[i]->piece.getTexture()->getSize().y / 2));
        w_pawn[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
    }

    b_bishop[0]->y = 2;
    b_bishop[1]->y = 5;
    b_rook[0]->y = 0;
    b_rook[1]->y = 7;
    b_knight[0]->y = 1;
    b_knight[1]->y = 6;
    w_bishop[0]->y = 2;
    w_bishop[1]->y = 5;
    w_rook[0]->y = 0;
    w_rook[1]->y = 7;
    w_knight[0]->y = 1;
    w_knight[1]->y = 6;
    // setting up the pieces
    for (int i = 0; i < 2; i++)
    {
        b_bishop[i]->piece.setPosition(100.0f * b_bishop[i]->y + 50.f, 100.0f * b_bishop[i]->x + 50.f);
        b_knight[i]->piece.setPosition(100.0f * b_knight[i]->y + 50.f, 100.0f * b_knight[i]->x + 50.f);
        b_rook[i]->piece.setPosition(100.0f * b_rook[i]->y + 50.f, 100.0f * b_rook[i]->x + 50.f);
        b_bishop[i]->piece.setOrigin(100.0f * b_bishop[i]->x, 100.0f * b_bishop[i]->y);
        b_knight[i]->piece.setOrigin(100.0f * b_knight[i]->x, 100.0f * b_knight[i]->y);
        b_rook[i]->piece.setOrigin(100.0f * b_rook[i]->x, 100.0f * b_rook[i]->y);
        b_bishop[i]->piece.setOrigin(sf::Vector2f(b_bishop[i]->piece.getTexture()->getSize().x / 2, b_bishop[i]->piece.getTexture()->getSize().y / 2));
        b_bishop[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
        b_rook[i]->piece.setOrigin(sf::Vector2f(b_rook[i]->piece.getTexture()->getSize().x / 2, b_rook[i]->piece.getTexture()->getSize().y / 2));
        b_rook[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
        b_knight[i]->piece.setOrigin(sf::Vector2f(b_knight[i]->piece.getTexture()->getSize().x / 2, b_knight[i]->piece.getTexture()->getSize().y / 2));
        b_knight[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
        w_bishop[i]->piece.setPosition(100.0f * w_bishop[i]->y + 50.f, 100.0f * w_bishop[i]->x + 50.f);
        w_knight[i]->piece.setPosition(100.0f * w_knight[i]->y + 50.f, 100.0f * w_knight[i]->x + 50.f);
        w_rook[i]->piece.setPosition(100.0f * w_rook[i]->y + 50.f, 100.0f * w_rook[i]->x + 50.f);
        w_bishop[i]->piece.setOrigin(100.0f * w_bishop[i]->x, 100.0f * w_bishop[i]->y);
        w_knight[i]->piece.setOrigin(100.0f * w_knight[i]->x, 100.0f * w_knight[i]->y);
        w_rook[i]->piece.setOrigin(100.0f * w_rook[i]->x, 100.0f * w_rook[i]->y);
        w_bishop[i]->piece.setOrigin(sf::Vector2f(w_bishop[i]->piece.getTexture()->getSize().x / 2, w_bishop[i]->piece.getTexture()->getSize().y / 2));
        w_bishop[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
        w_rook[i]->piece.setOrigin(sf::Vector2f(w_rook[i]->piece.getTexture()->getSize().x / 2, w_rook[i]->piece.getTexture()->getSize().y / 2));
        w_rook[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
        w_knight[i]->piece.setOrigin(sf::Vector2f(w_knight[i]->piece.getTexture()->getSize().x / 2, w_knight[i]->piece.getTexture()->getSize().y / 2));
        w_knight[i]->piece.setScale(sf::Vector2f(0.375f, 0.375f));
    }
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cells[i][j].square.setPosition(sf::Vector2f(j * 100.0f, i * 100.0f));
            cells[i][j].square.setSize(sf::Vector2f(100.f, 100.f));
            cells[i][j].square.setFillColor((i + j) % 2 ? c2 : c1);
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cells[7 - i][j].occupied_color = 1;
            cells[i][j].occupied_color = -1;
        }
    }
    // loop to set up pawns on board
    for (int j = 0; j < 8; j++)
    {
        cells[1][j].occupied_value = -3;
        cells[6][j].occupied_value = -3;
    }



    cells[0][0].occupied_value = 1;
    cells[7][7].occupied_value = 1;
    cells[7][0].occupied_value = 1;
    cells[0][7].occupied_value = 1; // setting up rook
    cells[0][1].occupied_value = -1;
    cells[7][6].occupied_value = -1;
    cells[0][6].occupied_value = -1;
    cells[7][1].occupied_value = -1; // setting up knight
    cells[0][2].occupied_value = -2;
    cells[7][5].occupied_value = -2;
    cells[0][5].occupied_value = -2;
    cells[7][2].occupied_value = -2; // setting up bishop
    cells[7][3].occupied_value = 2;
    cells[0][3].occupied_value = 2; // setting up queen
    cells[7][4].occupied_value = 3;
    cells[0][4].occupied_value = 3; // setting up king
    SetRightSideofWindow();
}
//maira
void Game::SetRightSideofWindow()
{
    if(whiteTurn == 0 && !isOver)
        chance.setString("Black's Turn");
    else if(whiteTurn == 1 && !isOver)
        chance.setString("White's Turn");   
}
//maira
void Game::draw(sf::RenderTarget &window, sf::RenderStates states) const
{


    window.clear();

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/bkgd.jpg")) {
        std::cerr << "Error loading background image" << std::endl;
    }
    sf::Sprite background(backgroundTexture);
    window.draw(background);


    //buttons 
    if (gameStatus) {
        startButtonBg.setFillColor(sf::Color(0, 139, 0));  // Dark green when started
    } else {
        startButtonBg.setFillColor(sf::Color(139, 69, 19));  // Brown when not started
    }

    std::string p1TimeStr = formatTime(player1Timer.getTimeLeft());
    std::string p2TimeStr = formatTime(player2Timer.getTimeLeft());
    
    player1Info.setString(player1Name + "\nTime: " + p1TimeStr);
    player2Info.setString(player2Name + "\nTime: " + p2TimeStr);

    // Check for time up
    if (player1Timer.isTimeUp() || player2Timer.isTimeUp()) {
        gameStatus = false;
        std::string winner = player1Timer.isTimeUp() ? "Player 2" : "Player 1";
        std::cout << "Time's up! " << winner << " wins!\n";
    }


    //laiba-

    window.draw(player1Info);
    window.draw(player2Info);

    window.draw(startButtonBg);
    window.draw(startButton);

    window.draw(restartButtonBg);
    window.draw(restartButton);
    // window.draw(circle);
    // window.draw(arrow);
    
    // Draw Quit button with background
    window.draw(quitButtonBg);
    window.draw(quitButton);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            window.draw(cells[i][j].square);
        }
    }
    // target.draw(infoRestart);
    // target.draw(textRestart)
    // target.draw(turn);
    // target.draw(situation);
    if(isOver == false)
        window.draw(chance);
    for (int i = 0; i < moves.size(); i++)
    {
        window.draw(moves[i].square);
    }

    if ((selected_piece != NULL))
    {
        for (int i = 0; i < newmoves.size(); i++)
        {
            window.draw(newmoves[i]);
        }
    }
    for (int i = 0; i < whitePieces.size(); i++)
    {
        if (whitePieces[i]->isAlive)
        {
            window.draw(whitePieces[i]->piece);
        }
        // if(!whitePieces[i]->isAlive){
        //      if(!w_king->isAlive){
        //         sleep(3);
        //         exit(0);
        //      }
        // }
    }
    for (int i = 0; i < blackPieces.size(); i++)
    {
        if (blackPieces[i]->isAlive)
        {
            window.draw(blackPieces[i]->piece);
        }
        // if(!blackPieces[i]->isAlive){
        //      if(!b_king->isAlive){
        //         sleep(3);
        //         exit(0);
        //      }
        // }
    }
}
//maira
void Game::gameOver()
{
    isOver = true;
    bool whiteWon = (whiteTurn == 0);  // Check if white won based on the turn
    
    // Create GameOverScreen and display the winner message
    if(whiteWon){
        gameOverScreen = new GameOverScreen(window, player1Name);
        gameOverScreen->displayWinner();
    }
    else{
        gameOverScreen = new GameOverScreen(window, player2Name);
        gameOverScreen->displayWinner();
    }
    
    
    // Main loop to show the winner until the window is closed
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (gameOverScreen->isClosed(event)) {
                window.close();  // Close the game window when the event is closed
            }
        }
        
        gameOverScreen->draw();  // Draw the winner screen
    }
}
//maira
void Game::DrawPossibleMoves()
{
    if (selected_piece == NULL)
        return;
    newmoves.clear();
    moves.clear();
    moves = selected_piece->getMoves(cells, selected_piece->x, selected_piece->y);
    for (int i = 0; i < moves.size(); i++)
    {
        sf::RectangleShape tmp;
        tmp.setPosition(sf::Vector2f((moves[i].y) * 100.f, (moves[i].x) * 100.f));
        tmp.setSize(sf::Vector2f(100.f, 100.f));
        tmp.setFillColor(sf::Color(0xFFD70080));
        newmoves.push_back(tmp);
    }
    sf::RectangleShape tmp;
    tmp.setPosition(sf::Vector2f((selected_piece->y) * 100.f, (selected_piece->x) * 100.f));
    tmp.setSize(sf::Vector2f(100.f, 100.f));
    tmp.setFillColor(sf::Color(0x00000000));
    tmp.setOutlineColor(sf::Color::Red);
    tmp.setOutlineThickness(-3.f);
    newmoves.push_back(tmp);
}
//maira
bool Game::SelectPiece(Square Cells[][8], int x, int y)
{
    if (Cells[x][y].occupied_color == 0)
    {
        selected_piece = NULL;
        return false;
    }
    if (Cells[x][y].occupied_color == 1 && whiteTurn == 0 || Cells[x][y].occupied_color == -1 && whiteTurn == 1)
    {
        selected_piece = NULL;
        return false;
    }
    selected = true;
    if (Cells[x][y].occupied_color == 1)
    {
        if (Cells[x][y].occupied_value == 3)
            selected_piece = w_king;
        else if (Cells[x][y].occupied_value == 2)
            selected_piece = w_queen;
        else if (Cells[x][y].occupied_value == 1)
        {
            if (w_rook[0]->x == x && w_rook[0]->y == y)
                selected_piece = w_rook[0];
            else
                selected_piece = w_rook[1];
        }
        else if (Cells[x][y].occupied_value == -2)
        {
            if (w_bishop[0]->x == x && w_bishop[0]->y == y)
                selected_piece = w_bishop[0];
            else
                selected_piece = w_bishop[1];
        }
        else if (Cells[x][y].occupied_value == -1)
        {
            if (w_knight[0]->x == x && w_knight[0]->y == y)
                selected_piece = w_knight[0];
            else
                selected_piece = w_knight[1];
        }
        else if (Cells[x][y].occupied_value == -3)
        {
            for (int i = 0; i < 8; i++)
            {
                if (w_pawn[i]->x == x && w_pawn[i]->y == y)
                {
                    selected_piece = w_pawn[i];
                    break;
                }
            }
        }
    }
    else
    {
        if (Cells[x][y].occupied_value == 3)
            selected_piece = b_king;
        else if (Cells[x][y].occupied_value == 2)
            selected_piece = b_queen;
        else if (Cells[x][y].occupied_value == 1)
        {
            if (b_rook[0]->x == x && b_rook[0]->y == y)
                selected_piece = b_rook[0];
            else
                selected_piece = b_rook[1];
        }
        else if (Cells[x][y].occupied_value == -2)
        {
            if (b_bishop[0]->x == x && b_bishop[0]->y == y)
                selected_piece = b_bishop[0];
            else
                selected_piece = b_bishop[1];
        }
        else if (Cells[x][y].occupied_value == -1)
        {
            if (b_knight[0]->x == x && b_knight[0]->y == y)
                selected_piece = b_knight[0];
            else
                selected_piece = b_knight[1];
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                if (b_pawn[i]->x == x && b_pawn[i]->y == y)
                {
                    selected_piece = b_pawn[i];
                    break;
                }
            }
        }
    }
    DrawPossibleMoves();
    return true;
}
//maira
bool Game::getSelected()
{
    return selected;
}
//maira
void Game::moveSelected(Square Cells[][8], int x, int y)
{
    if (selected_piece == NULL)
        return;
    bool valid = false;
    vector<Square> a = selected_piece->getMoves(cells, selected_piece->x, selected_piece->y);
    for (int i = 0; i < a.size(); i++)
    {
        if (x == a[i].x && y == a[i].y)
        {
            valid = true;
            break;
        }
    }
    if (valid)
    {
        selected_piece->piece.setPosition(sf::Vector2f(100.f * y + 50.f, 100.f * x + 50.f));
        int a = selected_piece->x, b = selected_piece->y;
        if (Cells[x][y].occupied_color != 0 && Cells[x][y].occupied_color != Cells[a][b].occupied_color)
        {
            if (Cells[x][y].occupied_color == 1)
            {
                for (int i = 0; i < whitePieces.size(); i++)
                {
                    if (whitePieces[i]->x == x && whitePieces[i]->y == y)
                    {
                        whitePieces[i]->isAlive = false;
                    }
                }
            }
            else
            {
                for (int i = 0; i < blackPieces.size(); i++)
                {
                    if (blackPieces[i]->x == x && blackPieces[i]->y == y)
                    {
                        blackPieces[i]->isAlive = false;
                    }
                }
            }
        }
        Cells[x][y].occupied_color = (whiteTurn == 1) ? 1 : -1;
        Cells[x][y].occupied_value = selected_piece->occupied_value;
        Cells[a][b].occupied_value = 0;
        Cells[selected_piece->x][selected_piece->y].occupied_color = 0;
        if (whiteTurn)
        {
            if (w_king->x == a && w_king->y == b)
                w_king->x = x, w_king->y = y;
            else if (w_queen->x == a && w_queen->y == b)
                w_queen->x = x, w_queen->y = y;
            else if (w_bishop[0]->x == a && w_bishop[0]->y == b)
                w_bishop[0]->x = x, w_bishop[0]->y = y;
            else if (w_bishop[1]->x == a && w_bishop[1]->y == b)
                w_bishop[1]->x = x, w_bishop[1]->y = y;
            else if (w_knight[0]->x == a && w_knight[0]->y == b)
                w_knight[0]->x = x, w_knight[0]->y = y;
            else if (w_knight[1]->x == a && w_knight[1]->y == b)
                w_knight[1]->x = x, w_knight[1]->y = y;
            else if (w_rook[0]->x == a && w_rook[0]->y == b)
                w_rook[0]->x = x, w_rook[0]->y = y;
            else if (w_rook[1]->x == a && w_rook[1]->y == b)
                w_rook[1]->x = x, w_rook[1]->y = y;
            else
            {
                for (int i = 0; i < 8; i++)
                {
                    if (w_pawn[i]->x == a && w_pawn[i]->y == b)
                    {
                        w_pawn[i]->x = x;
                        w_pawn[i]->y = y;
                        break;
                    }
                }
            }
        }
        else
        {
            if (b_king->x == a && b_king->y == b)
                b_king->x = x, b_king->y = y;
            else if (b_queen->x == a && b_queen->y == b)
                b_queen->x = x, b_queen->y = y;
            else if (b_bishop[0]->x == a && b_bishop[0]->y == b)
                b_bishop[0]->x = x, b_bishop[0]->y = y;
            else if (b_bishop[1]->x == a && b_bishop[1]->y == b)
                b_bishop[1]->x = x, b_bishop[1]->y = y;
            else if (b_knight[0]->x == a && b_knight[0]->y == b)
                b_knight[0]->x = x, b_knight[0]->y = y;
            else if (b_knight[1]->x == a && b_knight[1]->y == b)
                b_knight[1]->x = x, b_knight[1]->y = y;
            else if (b_rook[0]->x == a && b_rook[0]->y == b)
                b_rook[0]->x = x, b_rook[0]->y = y;
            else if (b_rook[1]->x == a && b_rook[1]->y == b)
                b_rook[1]->x = x, b_rook[1]->y = y;
            else
            {
                for (int i = 0; i < 8; i++)
                {
                    if (b_pawn[i]->x == a && b_pawn[i]->y == b)
                    {
                        b_pawn[i]->x = x;
                        b_pawn[i]->y = y;
                    }
                }
            }
        }
        whiteTurn = !whiteTurn;
        SetRightSideofWindow();
    }
    if (!w_king->isAlive || !b_king->isAlive)
    {
        gameOver();
    }
    selected_piece = NULL;
    selected = false;
}
//maira + laiba
void Game::setPlayerInfo(const std::string& player1, const std::string& player2) {
    // Convert the timerLimit to hours, minutes, and seconds

    // maira - adjusting the time bcs its only mins and secs, no hours 
    /*int hours = timerLimit / 3600;
    int minutes = (timerLimit % 3600) / 60;
    int seconds = timerLimit % 60;

    // Format the time as hh:mm:ss
    std::string formattedTime = (hours < 10 ? "0" : "") + std::to_string(hours) + ":" +
                                (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                                (seconds < 10 ? "0" : "") + std::to_string(seconds);
    */


   //laiba-
    int minutes = timerLimit / 60;
    int seconds = timerLimit % 60;

    // Format the time as mm:ss
    std::string formattedTime = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                                (seconds < 10 ? "0" : "") + std::to_string(seconds);
    // Display player 1 info
    player1Info.setFont(font);
    player1Info.setString(player1 + "\nTime Limit:\n" + formattedTime);
    player1Info.setCharacterSize(30);
    player1Info.setFillColor(sf::Color(92, 59, 39));
    player1Info.setPosition(870.f, 100.f);

    // Display player 2 info
    player2Info.setFont(font);
    player2Info.setString(player2 + "\nTime Limit:\n" + formattedTime);
    player2Info.setCharacterSize(30);
    player2Info.setFillColor(sf::Color(92, 59, 39));
    player2Info.setPosition(870.f, 700.f);

    // Setup Start button background
    startButton.setFont(font);
    startButton.setString("Start");
    startButton.setCharacterSize(20);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(910.f, 447.f);

    // Setup Restart button
    restartButton.setFont(font);
    restartButton.setString("c>");
    restartButton.setCharacterSize(30);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(965.f, 25.f);

    // Position offset
    float offsetX = 800;
    float offsetY = 200;

   /* // //Create the circle
    // sf::CircleShape circle(300);
    // circle.setPointCount(300);
    // circle.setFillColor(sf::Color::White);
    // circle.setOutlineColor(sf::Color::Black);
    // circle.setOutlineThickness(5.f);
    // circle.setPosition(offsetX, offsetY);

    // // Create the arrowhead
    // sf::ConvexShape arrow;
    // arrow.setPointCount(3);
    // arrow.setPoint(0, sf::Vector2f(offsetX + 100, offsetY - 20)); // Tip of the arrow
    // arrow.setPoint(1, sf::Vector2f(offsetX + 120, offsetY + 30)); // Bottom-right
    // arrow.setPoint(2, sf::Vector2f(offsetX + 80, offsetY + 30));  // Bottom-left
    // arrow.setFillColor(sf::Color::White);
*/
    
    // Setup Quit button
    quitButton.setFont(font);
    quitButton.setString("X");
    quitButton.setCharacterSize(30);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(1055.f, 25.f);

    //start background
    startButtonBg.setSize(sf::Vector2f(120.f, 40.f)); // Width and height
    startButtonBg.setFillColor(sf::Color(92, 59, 39)); // Brown color
    startButtonBg.setPosition(880.f, 440.f); // Slightly offset from text

    // Setup Restart button background
    restartButtonBg.setSize(sf::Vector2f(50.f, 40.f)); // Width and height
    restartButtonBg.setFillColor(sf::Color(92, 59, 39)); // Brown color
    restartButtonBg.setPosition(950.f, 20.f); // Slightly offset from text

    // Setup Quit button background
    quitButtonBg.setSize(sf::Vector2f(50.f, 40.f)); // Width and height
    quitButtonBg.setFillColor(sf::Color(92, 59, 39)); // Brown color
    quitButtonBg.setPosition(1040.f, 20.f);
}
//laiba
std::string Game::formatTime(float seconds) const {
    int mins = static_cast<int>(seconds) / 60;
    int secs = static_cast<int>(seconds) % 60;
    return std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
}

void Game::handleEvents(sf::RenderWindow& window){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed ) {
            //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            //std::cout << "\nMouse clicked at: (" << mousePos.x << ", " << mousePos.y << ")\n";

            // Get button bounds for debugging
            sf::FloatRect startBounds = startButtonBg.getGlobalBounds();
            // std::cout << "Start button bounds: (" << startBounds.left << ", " << startBounds.top 
            //           << ", " << startBounds.width << ", " << startBounds.height << ")\n";
            sf::FloatRect restartBounds = restartButtonBg.getGlobalBounds();
            // std::cout << "Restart button bounds: (" << restartBounds.left << ", " << restartBounds.top 
            //           << ", " << restartBounds.width << ", " << restartBounds.height << ")\n";
            sf::FloatRect quitBounds = quitButtonBg.getGlobalBounds();
            
            if (startBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Start button area clicked. Game started: " << (gameStatus ? "true" : "false") << "\n";
                if (!gameStatus) {
                    std::cout << "Starting game...\n";
                    startGame();
                    std::cout << "Game started: " << (gameStatus ? "true" : "false") << "\n";
                }
            }
            else if (restartBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Restart button clicked\n";
                window.close();
                restartGame();
            }
            else if (quitBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Quit button clicked\n";
                window.close();
            }
            // else if (gameStatus) {
            //     std::cout << "Handling piece selection\n";
            //     handlePieceSelection(event.mouseButton.x, event.mouseButton.y);  
            // }
        }
        else if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::startGame() {
    std::cout << "startGame() called. Current state: " << (gameStatus ? "true" : "false") << "\n";
    if (!gameStatus) {
        gameStatus = true;
        whiteTurn = true;
        
        // Reset and initialize timers
        player1Timer.reset();
        player2Timer.reset();
        player1Timer.start();  // Start white's timer
        player2Timer.stop();   // Keep black's timer stopped initially
        
        std::cout << "Game started! White's turn\n";
        std::cout << "New game state: " << (gameStatus ? "true" : "false") << "\n";
    }
}

void Game::restartGame() {
    // gameStatus = false;
    // whiteTurn = true;
    // setPlayerInfo(player1Name, player2Name);

    // Reset timers
    player1Timer.reset();
    player2Timer.reset();
    
    //maira
    sf::RenderWindow gameWindow(sf::VideoMode(1100, 800), "Game");
    if (theme == "Classic"){
        Game chess(gameWindow, sf::Color(119,67,22), sf::Color(198,141,92), player1Name, player2Name, timerLimit,theme);
        chess.display(gameWindow);
    }
    else if(theme == "Pakistan"){
        Game chess(gameWindow, sf::Color(11, 175, 11), sf::Color(255, 255, 255), player1Name, player2Name, timerLimit, theme);
        chess.display(gameWindow);
    }
    else if(theme == "Habib University"){
        Game chess(gameWindow, sf::Color(98, 0, 128), sf::Color(252, 252, 152), player1Name, player2Name, timerLimit,theme);
        chess.display(gameWindow);
    }
    else if(theme == "Ocean"){
        Game chess(gameWindow, sf::Color(11, 136, 182), sf::Color(0, 0, 139), player1Name, player2Name, timerLimit, theme);
        chess.display(gameWindow);
    }
    
}

