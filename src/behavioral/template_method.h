#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace design_patterns::behavioral::template_method {

class Game {
public:
    virtual ~Game() = default;

    void play() const {
        std::cout << "[Game] Starting game process..." << std::endl;
        
        initialize();
        
        if (wantToPlay()) {
            startPlay();
            playGame();
            endPlay();
        } else {
            std::cout << "[Game] Player doesn't want to play" << std::endl;
        }
        
        std::cout << "[Game] Game process completed" << std::endl;
    }

protected:
    virtual void initialize() const = 0;
    virtual void startPlay() const = 0;
    virtual void playGame() const = 0;
    virtual void endPlay() const = 0;

    virtual bool wantToPlay() const {
        return true;
    }

    virtual std::string getName() const = 0;
};

class FootballGame : public Game {
protected:
    void initialize() const override {
        std::cout << "[Football] Initializing football game..." << std::endl;
        std::cout << "[Football] Setting up field..." << std::endl;
        std::cout << "[Football] Teams ready!" << std::endl;
    }

    void startPlay() const override {
        std::cout << "[Football] Kickoff!" << std::endl;
        std::cout << "[Football] Game started!" << std::endl;
    }

    void playGame() const override {
        std::cout << "[Football] Playing football..." << std::endl;
        std::cout << "[Football] Team A scores a goal!" << std::endl;
        std::cout << "[Football] Team B scores a goal!" << std::endl;
        std::cout << "[Football] Game continues..." << std::endl;
    }

    void endPlay() const override {
        std::cout << "[Football] Final whistle!" << std::endl;
        std::cout << "[Football] Game ended with 1-1 draw" << std::endl;
    }

    std::string getName() const override {
        return "Football";
    }
};

class ChessGame : public Game {
protected:
    void initialize() const override {
        std::cout << "[Chess] Initializing chess game..." << std::endl;
        std::cout << "[Chess] Setting up board..." << std::endl;
        std::cout << "[Chess] Pieces placed!" << std::endl;
    }

    void startPlay() const override {
        std::cout << "[Chess] White moves first!" << std::endl;
        std::cout << "[Chess] Game started!" << std::endl;
    }

    void playGame() const override {
        std::cout << "[Chess] Playing chess..." << std::endl;
        std::cout << "[Chess] White moves: e2-e4" << std::endl;
        std::cout << "[Chess] Black moves: e7-e5" << std::endl;
        std::cout << "[Chess] Game continues..." << std::endl;
    }

    void endPlay() const override {
        std::cout << "[Chess] Checkmate!" << std::endl;
        std::cout << "[Chess] White wins!" << std::endl;
    }

    std::string getName() const override {
        return "Chess";
    }
};

class GameWithHook : public Game {
protected:
    void initialize() const override {
        std::cout << "[GameWithHook] Initializing..." << std::endl;
    }

    void startPlay() const override {
        std::cout << "[GameWithHook] Starting..." << std::endl;
    }

    void playGame() const override {
        std::cout << "[GameWithHook] Playing..." << std::endl;
    }

    void endPlay() const override {
        std::cout << "[GameWithHook] Ending..." << std::endl;
    }

    bool wantToPlay() const override {
        std::cout << "[GameWithHook] Hook: Player doesn't want to play today" << std::endl;
        return false;
    }

    std::string getName() const override {
        return "GameWithHook";
    }
};

}

namespace design_patterns::behavioral {
void template_method_demo();

}
