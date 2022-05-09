#include <stdlib.h>
#include <time.h>

#include "gameConstants.h"
#include "SDL_Utils.h"
#include "RenderWindow.hpp"
#include "Deck.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool checkBet(const int& p_bet, const int& cash);
bool isBlackJack(Deck p_deck);
//gameState roundResult(Deck playerDeck, Deck dealerDeck);
void loadMedia();
void closeAll();
void gamePlay(gamePhase& phase);
void renderScene(Deck mDeck, Deck pDeck, Deck dDeck, const gamePhase& phase);

int main(int argc, char* argv[])
{
    
    srand(time(0));
    if (!init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, "image/icon.png")) {
        std::cout << "SDL init has failed. Error: " << SDL_GetError() << std::endl;
        system("pause");
        exit(1);
    }
    if (window == nullptr) {
        std::cout << "window null";
        exit(1);
    }
    loadMedia();
    gamePhase phase = gamePhase::PLAYER_PHASE;
    gamePlay(phase);
    closeAll();
    /*
    std::cout << "Welcome to BlackJack" << std::endl;
    
    //creating the playing deck
    Deck playingDeck;
    playingDeck.createFullDeck();    
    
    //create player and dealer deck
    Deck playerDeck;
    Deck dealerDeck;

    int playerCash = PLAYER_START_CASH;
    
    while (playerCash > 0)
    {
        playingDeck.shuffle();
        int bet = 0;
        do
        {
            std::cout << "\nHow much would you like to bet?(0 - " << playerCash << ") ";
            std::cin >> bet;
        } while (!checkBet(bet, playerCash));

        playerDeck.draw(playingDeck);
        dealerDeck.draw(playingDeck);
        playerDeck.draw(playingDeck);
        dealerDeck.draw(playingDeck);

    bool endRound = false;
    bool quit = false;
        while (!quit) {
            std::cout << "\nYour hand: " << playerDeck.toString() << std::endl;
            std::cout << "\Your hand is valued at: " << playerDeck.getTotalValue() << std::endl;

            std::cout << "\nDealer hand: " << dealerDeck.getCard(0).toString() << " and [Hidden]" << std::endl;

            char playerChoice;

                std::cout << "\nWould you like to (h)Hit or (s)Stand? ";
                std::cin >> playerChoice;
                switch (playerChoice)
                {
                case 'h':
                case 'H':
                    playerDeck.draw(playingDeck);
                    std::cout << "You draw a: " << playerDeck.getCard(playerDeck.deckSize() - 1).toString() << std::endl;
                    if (playerDeck.getTotalValue() > 21) {
                        std::cout << "Bust. Currently value: " << playerDeck.getTotalValue() << std::endl;
                        playerCash -= bet;
                        endRound = true;
                        quit = true;
                    }
                    break;
                case 's':
                case 'S':
                    quit = true;
                    break;
                default:
                    break;
                }
            
        }
        //reveal dealer card
        std::cout << "\nDealer hand: " << dealerDeck.toString() << std::endl;
        if (dealerDeck.getTotalValue() > playerDeck.getTotalValue() && !endRound) {
            std::cout << "Dealer's hand is valued at: " << dealerDeck.getTotalValue() << std::endl;
            std::cout << "Dealer beats you!\n";
            playerCash -= bet;
            endRound = true;
        }
        //dealer draw to 17
        else {
            while (dealerDeck.getTotalValue() < 17) {
                dealerDeck.draw(playingDeck);
                std::cout << "Dealer draws: " << dealerDeck.getCard(dealerDeck.deckSize()-1).toString() << std::endl;
            }
            //print dealer's hand total value
            std::cout << "Dealer's hand is valued at: " << dealerDeck.getTotalValue() << std::endl;
        }
        if (dealerDeck.getTotalValue() > 21  && !endRound) {
            std::cout << "\nDealer busts! You win this round!\n";
            playerCash += bet;
            endRound = true;
        }
        else if (dealerDeck.getTotalValue() == playerDeck.getTotalValue() && !endRound) {
            std::cout << "\nPush!\n";
            endRound = true;
        }
        else if (dealerDeck.getTotalValue() > playerDeck.getTotalValue() && !endRound) {
            std::cout << "Dealer beats you!";
            playerCash -= bet;
            endRound = true;
        }
        else if(!endRound) {
            std::cout << "\nYou Win!\n";
            playerCash += bet;
            endRound = true;
        }

        playerDeck.moveAllToDeck(playingDeck);
        dealerDeck.moveAllToDeck(playingDeck);

    }

    std::cout << "Game over! You're out of money.\n"; */
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

bool isBlackJack(Deck p_deck)
{
    return (p_deck.getTotalValue() == 21 && p_deck.deckSize() == 2);
}

//gameState roundResult(Deck playerDeck, Deck dealerDeck)
//{
//    bool endRound = false;
//    if (dealerDeck.getTotalValue() > playerDeck.getTotalValue() && !endRound) {
//        std::cout << "Dealer's hand is valued at: " << dealerDeck.getTotalValue() << std::endl;
//        std::cout << "Dealer beats you!\n";
//        endRound = true;
//    }
//    //dealer draw to 17
//    else {
//        while (dealerDeck.getTotalValue() < 17) {
//            dealerDeck.draw(playingDeck);
//            std::cout << "Dealer draws: " << dealerDeck.getCard(dealerDeck.deckSize() - 1).toString() << std::endl;
//        }
//        //print dealer's hand total value
//        std::cout << "Dealer's hand is valued at: " << dealerDeck.getTotalValue() << std::endl;
//    }
//    if (dealerDeck.getTotalValue() > 21 && !endRound) {
//        std::cout << "\nDealer busts! You win this round!\n";
//        playerCash += bet;
//        endRound = true;
//    }
//    else if (dealerDeck.getTotalValue() == playerDeck.getTotalValue() && !endRound) {
//        std::cout << "\nPush!\n";
//        endRound = true;
//    }
//    else if (dealerDeck.getTotalValue() > playerDeck.getTotalValue() && !endRound) {
//        std::cout << "Dealer beats you!";
//        playerCash -= bet;
//        endRound = true;
//    }
//    else if (!endRound) {
//        std::cout << "\nYou Win!\n";
//        playerCash += bet;
//        endRound = true;
//    }
//}

void loadMedia()
{
    table.loadTexture(renderer, "image/table.png");

    for (Value v = Value::BEGIN; v != Value::END; ++v) {
        if (v == Value::BEGIN) continue;
        for (Suit s = Suit::BEGIN; s != Suit::END; ++s) {
            if (s == Suit::BEGIN) continue;
            cardObj[toInt(v)][toInt(s)].loadTexture(renderer, "image/card/" + toStr(v) + "-" + toStr(s) + ".png");
        }
    }

    backCard.loadTexture(renderer, "image/card/back of card.png");
}

void closeAll()
{
    kill(window, renderer);
    table.~BaseObject();
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cardObj[i][j].~BaseObject();
        }
    }
    backCard.~BaseObject();
}

void gamePlay(gamePhase& phase)
{
    Deck mainDeck, playerDeck, dealerDeck;
    mainDeck.createFullDeck();
    mainDeck.shuffle();

    playerDeck.draw(mainDeck);
    dealerDeck.draw(mainDeck);
    playerDeck.draw(mainDeck);
    dealerDeck.draw(mainDeck);

    bool quit = false;
    SDL_Event e;
    SDL_StartTextInput();
    while (!quit) {
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                kill(window, renderer);
                exit(0);
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    kill(window, renderer);
                    exit(0);
                case SDLK_h:
                    playerDeck.draw(mainDeck);

                    break;
                case SDLK_s:
                    phase = gamePhase::DEALER_PHASE;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        //playerDeck.print();
        renderScene(mainDeck, playerDeck, dealerDeck, phase);
        //SDL_Delay(1000);
    }
}

void renderScene(Deck mDeck, Deck pDeck, Deck dDeck, const gamePhase& phase)
{
    clear(renderer);
    //SDL_SetRenderDrawColor(renderer, 0, 240, 0, 180);
    table.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //render player hand and dealer hand
    if (phase == gamePhase::PLAYER_PHASE) {
        //render Dealer Hand
            int x_d = (SCREEN_WIDTH - (CARD_WIDTH +  CARD_XSPACE)) / 2;
            int y_d = SCREEN_HEIGHT/4 - CARD_HEIGHT/2;
            Value v = dDeck.getCard(0).getValue();
            Suit s = dDeck.getCard(0).getSuit();
            cardObj[toInt(v)][toInt(s)].render(renderer, x_d, y_d, CARD_WIDTH, CARD_HEIGHT);
            backCard.render(renderer, x_d + CARD_XSPACE, y_d, CARD_WIDTH, CARD_HEIGHT);//hidden card
        
        //render player hand
        int psize = pDeck.deckSize();
        //int x = 360 - (psize - 2) * CARD_XSPACE / 2;
        int x_p = (SCREEN_WIDTH - (CARD_WIDTH + (psize - 1) * CARD_XSPACE)) / 2;
        int y_p = SCREEN_HEIGHT/2 + y_d;
        for (int i = 0; i < MAX_PLAYER_CARDS; ++i)
        {
            if (psize == 0) goto theEnd;

            Value v = pDeck.getCard(i).getValue();
            Suit s = pDeck.getCard(i).getSuit();
            cardObj[toInt(v)][toInt(s)].render(renderer, x_p, y_p, CARD_WIDTH, CARD_HEIGHT);
            --psize;
            x_p += CARD_XSPACE;
        }

    theEnd:;
    }



    display(renderer);
}
