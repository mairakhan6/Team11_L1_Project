#include "board.hpp"
#include <iostream>

//LAIBA - board
// HOORAIN - pieces
// MAIRA - game logic and timer


Board::Board(const std::string& theme, const std::string& player1, const std::string& player2, int timerLimit) 
    : boardTheme(theme), timerLimit(timerLimit), lightColor(sf::Color::White), darkColor(sf::Color::Black),
      isPieceSelected(false), gameStarted(false), isWhiteTurn(true), selectedPiece(nullptr), 
      player1Name(player1), player2Name(player2),
      player1Timer(timerLimit, sf::Vector2f(50.f, 20.f)),  // Position timer for player 1
      player2Timer(timerLimit, sf::Vector2f(600.f, 20.f))  // Position timer for player 2
{
    // Initialize selected square
    selectedSquare.setSize(sf::Vector2f(75.f, 75.f));  // Size of a board square
    selectedSquare.setFillColor(sf::Color(255, 255, 0, 128));  
    
    setTheme(theme);
    loadResources();
    loadPieceTextures();
    setPlayerInfo(player1, player2);
    setupBoardPosition();
    initializePieces();
}

Board::Board() 
    : boardTheme("Classic"), timerLimit(60), lightColor(sf::Color::White), darkColor(sf::Color::Black),
      isPieceSelected(false), gameStarted(false), isWhiteTurn(true), selectedPiece(nullptr),
      player1Name("Player 1"), player2Name("Player 2"),
      player1Timer(60, sf::Vector2f(50.f, 20.f)),  // Default 60 seconds timer
      player2Timer(60, sf::Vector2f(600.f, 20.f))  // Default 60 seconds timer
{
    // Initialize selected square
    selectedSquare.setSize(sf::Vector2f(75.f, 75.f));  // Size of a board square
    selectedSquare.setFillColor(sf::Color(255, 255, 0, 128));  
    
    loadResources();
    loadPieceTextures();
    setPlayerInfo("Player 1", "Player 2");
    setupBoardPosition();
    initializePieces();
}

void Board::loadResources() {
    if (!font.loadFromFile("fonts/english.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("images/bkgd.jpg")) {
        std::cerr << "Error loading background image" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
}

void Board::setupBoardPosition() {
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float boardSize = 600.f;
    boardShape.setSize(sf::Vector2f(boardSize, boardSize));
    boardShape.setPosition(0.f, (textureSize.y - boardSize) / 2.f);
    
    // Set the board properties for pieces
    Piece::setBoardProperties(boardShape.getPosition(), boardSize / 8);

    
    selectedSquare.setSize(sf::Vector2f(boardSize / 8, boardSize / 8));
    selectedSquare.setFillColor(sf::Color(255, 255, 0, 128));  
    selectedSquare.setOutlineColor(sf::Color::Yellow);
    selectedSquare.setOutlineThickness(2.f);
}

void Board::setTheme(const std::string& theme) {
    if (theme == "Classic") {
        lightColor = sf::Color(119,67,22);
        darkColor = sf::Color(198,141,92);
    }
    else if (theme == "Pakistan") {
        lightColor = sf::Color(11, 175, 11); 
        darkColor = sf::Color(255, 255, 255); 
    }
    else if (theme == "Habib University") {
        lightColor = sf::Color(98, 0, 128); // maira - a few color changes
        darkColor = sf::Color(252, 252, 152);
    }
    else if (theme == "Ocean") {
        lightColor = sf::Color(11, 136, 182); 
        darkColor = sf::Color(0, 0, 139);
    }
    else {
        std::cerr << "Unknown theme: " << theme << std::endl;
    }
}

void Board::setPlayerInfo(const std::string& player1, const std::string& player2) {
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
    int minutes = timerLimit / 60;
    int seconds = timerLimit % 60;

    // Format the time as mm:ss
    std::string formattedTime = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                                (seconds < 10 ? "0" : "") + std::to_string(seconds);
    // Display player 1 info
    player1Info.setFont(font);
    player1Info.setString(player1 + "\nTime Limit:\n" + formattedTime);
    player1Info.setCharacterSize(20);
    player1Info.setFillColor(sf::Color(139, 69, 19));
    player1Info.setPosition(640.f, 20.f);

    // Display player 2 info
    player2Info.setFont(font);
    player2Info.setString(player2 + "\nTime Limit:\n" + formattedTime);
    player2Info.setCharacterSize(20);
    player2Info.setFillColor(sf::Color(139, 69, 19));
    player2Info.setPosition(640.f, 500.f);

    // Setup Start button background
    startButton.setFont(font);
    startButton.setString("Start");
    startButton.setCharacterSize(20);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(680.f, 210.f);

    // Setup Restart button
    restartButton.setFont(font);
    restartButton.setString("Restart");
    restartButton.setCharacterSize(20);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(670.f, 260.f);

    // Setup Quit button
    quitButton.setFont(font);
    quitButton.setString("Quit");
    quitButton.setCharacterSize(20);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(685.f, 310.f);

    //start background
    startButtonBg.setSize(sf::Vector2f(120.f, 40.f)); // Width and height
    startButtonBg.setFillColor(sf::Color(139, 69, 19)); // Brown color
    startButtonBg.setPosition(645.f, 205.f); // Slightly offset from text

    // Setup Restart button background
    restartButtonBg.setSize(sf::Vector2f(120.f, 40.f)); // Width and height
    restartButtonBg.setFillColor(sf::Color(139, 69, 19)); // Brown color
    restartButtonBg.setPosition(645.f, 255.f); // Slightly offset from text

    // Setup Quit button background
    quitButtonBg.setSize(sf::Vector2f(120.f, 40.f)); // Width and height
    quitButtonBg.setFillColor(sf::Color(139, 69, 19)); // Brown color
    quitButtonBg.setPosition(645.f, 305.f);
}


void Board::drawGrid(sf::RenderWindow& window) {
    float squareSize = boardShape.getSize().x / 8;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(boardShape.getPosition().x + i * squareSize, boardShape.getPosition().y + j * squareSize);

            if ((i + j) % 2 == 0)
                square.setFillColor(lightColor);
            else
                square.setFillColor(darkColor);

            window.draw(square);
        }
    }
}

void Board::drawBoard(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    drawGrid(window);

    // Draw pieces
    for (std::vector<Piece>::const_iterator it = pieces.begin(); it != pieces.end(); ++it) {
        it->draw(window);
    }

    // Draw selection highlight if a piece is selected
    if (isPieceSelected && selectedPiece != nullptr) {
        sf::Vector2f screenPos = boardToScreenPosition(selectedPiece->getPosition().x, selectedPiece->getPosition().y);
        selectedSquare.setPosition(screenPos);
        window.draw(selectedSquare);
    }
    
    // Update start button color based on game state
    if (gameStarted) {
        startButtonBg.setFillColor(sf::Color(0, 139, 0));  // Dark green when started
    } else {
        startButtonBg.setFillColor(sf::Color(139, 69, 19));  // Brown when not started
    }
    
    // Update and draw timers if game is started
    // if (gameStarted || !gameStarted) {
        // Set color based on whose turn it is
        // if (!isWhiteTurn) {
        //     player1Info.setFillColor(sf::Color::Green);  // Active player
        //     player2Info.setFillColor(sf::Color(139, 69, 19));  // Inactive player
        // } else {
        //     player1Info.setFillColor(sf::Color(139, 69, 19));  // Inactive player
        //     player2Info.setFillColor(sf::Color::Green);  // Active player
        // }
        
        // Update player info text with time
        std::string p1TimeStr = formatTime(player1Timer.getTimeLeft());
        std::string p2TimeStr = formatTime(player2Timer.getTimeLeft());
        
        player1Info.setString(player1Name + "\nTime: " + p1TimeStr);
        player2Info.setString(player2Name + "\nTime: " + p2TimeStr);

        // Check for time up
        if (player1Timer.isTimeUp() || player2Timer.isTimeUp()) {
            gameStarted = false;
            std::string winner = player1Timer.isTimeUp() ? "Player 2" : "Player 1";
            std::cout << "Time's up! " << winner << " wins!\n";
        }
    // } 

    window.draw(player1Info);
    window.draw(player2Info);

    window.draw(startButtonBg);
    window.draw(startButton);

    window.draw(restartButtonBg);
    window.draw(restartButton);

    // Draw Quit button with background
    window.draw(quitButtonBg);
    window.draw(quitButton);
}

sf::Texture& Board::getBackgroundTexture() {
    return backgroundTexture;
}


void Board::eventHandle(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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
                std::cout << "Start button area clicked. Game started: " << (gameStarted ? "true" : "false") << "\n";
                if (!gameStarted) {
                    std::cout << "Starting game...\n";
                    startGame();
                    std::cout << "Game started: " << (gameStarted ? "true" : "false") << "\n";
                }
            }
            else if (restartBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Restart button clicked\n";
                restartGame();
            }
            else if (quitBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Quit button clicked\n";
                window.close();
            }
            else if (gameStarted) {
                std::cout << "Handling piece selection\n";
                handlePieceSelection(event.mouseButton.x, event.mouseButton.y);  
            }
        }
        else if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Board::startGame() {
    std::cout << "startGame() called. Current state: " << (gameStarted ? "true" : "false") << "\n";
    if (!gameStarted) {
        gameStarted = true;
        isWhiteTurn = true;
        
        // Reset and initialize timers
        player1Timer.reset();
        player2Timer.reset();
        player1Timer.start();  // Start white's timer
        player2Timer.stop();   // Keep black's timer stopped initially
        
        std::cout << "Game started! White's turn\n";
        std::cout << "New game state: " << (gameStarted ? "true" : "false") << "\n";
    }
}

void Board::restartGame() {
    gameStarted = false;
    isWhiteTurn = true;
    isPieceSelected = false;
    selectedPiece = nullptr;
    setPlayerInfo(player1Name, player2Name);
    initializePieces();
    // Reset timers
    player1Timer.reset();
    player2Timer.reset();
}


void Board::updateTheme(const std::string& theme) {
    setTheme(theme); // Update theme colors
}

void Board::setTimerLimit(int newTimerLimit) {
    timerLimit = newTimerLimit;
}

void Board::loadPieceTextures() {
    // Declare and initialize the piece and color vectors
    std::vector<std::string> pieces;
    pieces.push_back("pawn");
    pieces.push_back("rook");
    pieces.push_back("knight");
    pieces.push_back("bishop");
    pieces.push_back("queen");
    pieces.push_back("king");

    std::vector<std::string> colors;
    colors.push_back("white");
    colors.push_back("black");

    // Iterate through pieces and colors
    for (std::vector<std::string>::iterator pieceIt = pieces.begin(); pieceIt != pieces.end(); ++pieceIt) {
        for (std::vector<std::string>::iterator colorIt = colors.begin(); colorIt != colors.end(); ++colorIt) {
            sf::Texture texture;
            std::string path = "pieces/" + *colorIt + "_" + *pieceIt + ".png";

            if (!texture.loadFromFile(path)) {
                std::cerr << "Failed to load texture: " << path << std::endl;
                continue;
            }

            texture.setSmooth(true); // Enable smooth scaling

            // Use insert instead of emplace
            pieceTextures.insert(std::make_pair(*colorIt + "_" + *pieceIt, texture));
        }
    }
}

void Board::initializePieces() {
    pieces.clear();  // Clear any existing pieces
    
    // Initialize pawns
    for (int i = 0; i < 8; i++) {
        pieces.emplace_back("pawn", true, i, 6);  // White pawns
        pieces.back().setTexture(pieceTextures["white_pawn"]);
        pieces.back().setPosition(i, 6);
        
        pieces.emplace_back("pawn", false, i, 1); // Black pawns
        pieces.back().setTexture(pieceTextures["black_pawn"]);
        pieces.back().setPosition(i, 1);
    }

    // Initialize other pieces
    std::vector<std::string> pieceOrder;
    pieceOrder.push_back("rook");
    pieceOrder.push_back("knight");
    pieceOrder.push_back("bishop");
    pieceOrder.push_back("queen");
    pieceOrder.push_back("king");
    pieceOrder.push_back("bishop");
    pieceOrder.push_back("knight");
    pieceOrder.push_back("rook");
    
    for (int i = 0; i < 8; i++) {
        // White pieces
        pieces.emplace_back(pieceOrder[i], true, i, 7);
        pieces.back().setTexture(pieceTextures["white_" + pieceOrder[i]]);
        pieces.back().setPosition(i, 7);
        
        // Black pieces
        pieces.emplace_back(pieceOrder[i], false, i, 0);
        pieces.back().setTexture(pieceTextures["black_" + pieceOrder[i]]);
        pieces.back().setPosition(i, 0);
    }
}

sf::Vector2f Board::boardToScreenPosition(int x, int y) const {
    float squareSize = boardShape.getSize().x / 8;
    return sf::Vector2f(
        boardShape.getPosition().x + (x * squareSize),
        boardShape.getPosition().y + (y * squareSize)
    );
}

sf::Vector2i Board::screenToBoardPosition(float x, float y) const {
    float squareSize = boardShape.getSize().x / 8;
    return sf::Vector2i(
        static_cast<int>((x - boardShape.getPosition().x) / squareSize),
        static_cast<int>((y - boardShape.getPosition().y) / squareSize)
    );
}

bool Board::isValidBoardPosition(int x, int y) const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

void Board::handlePieceSelection(int mouseX, int mouseY) {
    if (!gameStarted) return;  // Don't handle moves if game hasn't started

    // Convert screen coordinates to board coordinates
    sf::Vector2i boardPos = screenToBoardPosition(mouseX, mouseY);
    
    // Check if the board position is valid
    if (!isValidBoardPosition(boardPos.x, boardPos.y)) {
        return;
    }

    // Handle piece selection and movement
    if (!isPieceSelected) {
        // Try to select a piece
        for (std::vector<Piece>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
            if (it->getPosition().x == boardPos.x && 
                it->getPosition().y == boardPos.y &&
                it->getIsWhite() == isWhiteTurn) {  // Only select pieces of current player's color
                selectedPiece = &(*it);
                isPieceSelected = true;
                break;
            }
        }
    } else {
        // Try to move the selected piece
        if (isValidMove(selectedPiece, boardPos.x, boardPos.y)) {
            selectedPiece->setPosition(boardPos.x, boardPos.y);
            
            // Switch turns and timers
            isWhiteTurn = !isWhiteTurn;
            if (isWhiteTurn) {
                player2Timer.stop();  // Stop black's timer
                player1Timer.start(); // Start white's timer
            } else {
                player1Timer.stop();  // Stop white's timer
                player2Timer.start(); // Start black's timer
            }
            std::cout << (isWhiteTurn ? "White's turn" : "Black's turn") << std::endl;
        }
        isPieceSelected = false;
        selectedPiece = nullptr;
    }
}

bool Board::isValidMove(Piece* piece, int x, int y) const {
    if (!piece || !isValidBoardPosition(x, y)) {
        return false;
    }
    
    // Add your chess piece movement validation logic here
    // For now, we'll allow any move to a valid position
    return true;
}

std::string Board::formatTime(float seconds) {
    int mins = static_cast<int>(seconds) / 60;
    int secs = static_cast<int>(seconds) % 60;
    return std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
}