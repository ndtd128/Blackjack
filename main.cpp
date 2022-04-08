#include <stdlib.h>
#include <time.h>

#include "gameConstants.h"
#include "RenderWindow.hpp"
#include "Deck.h"

bool checkBet(const int& p_bet, const int& cash);

int main(int argc, char* argv[])
{
    /*RenderWindow window(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        window.renderClear();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        SDL_Texture* table = window.loadTexture("image/table.png");
        window.render(0, 0, table);
        SDL_DestroyTexture(table);
        window.display();
    }
    window.quit();*/
    srand(time(0));
    std::cout << "Welcome to BlackJack" << std::endl;
    
    //creating the playing deck
    Deck playingDeck;
    playingDeck.createFullDeck();
    //playingDeck.print();
    playingDeck.shuffle();
    
    //create player and dealer deck
    Deck playerDeck;
    Deck dealerDeck;

    int playerCash = PLAYER_START_CASH;
    
    while (playerCash > 0) {
        int bet = -1;
        while (bet <= 0 || bet > playerCash) {
            std::cout << "How much would you like to bet? ";
            std::cin >> bet;
        }

        //Star dealing
        //player and dealer draw 2 cards
        playerDeck.draw(playingDeck);
        dealerDeck.draw(playingDeck);
        playerDeck.draw(playingDeck);
        dealerDeck.draw(playingDeck);

        while (true) {
            std::cout << "\nYour hand: ";
            playerDeck.print();
            break;
        }

    }

    return 0;
}
bool checkBet(const int& p_bet, const int& cash)
{
    if (p_bet <= 0 || p_bet > cash) {
        std::cout << "Please bet in the range from 0 to " << cash << ".\n";
        return false;
    }
    else return true;
}