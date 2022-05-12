#include <stdlib.h>
#include <time.h>

#include "gameConstants.h"
#include "SDL_Utils.h"
#include "Deck.h"
#include "BaseObject.h"
#include "TextObject.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int pValue = 0;
int dValue = 0;

bool checkBet(const int& p_bet, const int& cash);
void dealerTurn(Deck& mDeck, Deck& dDeck, gameResult& res);
//gameState roundResult(Deck playerDeck, Deck dealerDeck);
void loadMedia();
void closeAll();
void gamePlay(gameScene& phase, gameResult& res);
void renderScene(Deck mDeck, Deck pDeck, Deck dDeck, const gameScene& phase, const gameResult& res);

int main(int argc, char* argv[])
{
    
    srand(time(0));
    if (!init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, "image/icon.png")) {
        std::cout << "SDL init has failed. Error: " << SDL_GetError() << std::endl;
        system("pause");
        exit(1);
    }
    loadMedia();
    gameScene phase = gameScene::PLAYER_PHASE;
    gameResult res = gameResult::BEGIN;
    gamePlay(phase, res);
    closeAll();
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

void dealerTurn(Deck& mDeck, Deck& dDeck, gameResult& res)
{
    if (dDeck.isBlackJack()) {
        res = gameResult::D_BLACK_JACK;
        return;
    }

    while (dValue < 17) {
        dDeck.draw(mDeck);
        dValue = dDeck.getTotalValue();
    }
    if (dDeck.isBusts()) {
        res = gameResult::D_BUSTS;
    }
    else
        res = gameResult::CONTINUE;
}

void loadMedia()
{
    //load pics
    table.loadTexture(renderer, "image/table.png");

    for (Value v = Value::BEGIN; v != Value::END; ++v) {
        if (v == Value::BEGIN) continue;
        for (Suit s = Suit::BEGIN; s != Suit::END; ++s) {
            if (s == Suit::BEGIN) continue;
            cardObj[toInt(v)][toInt(s)].loadTexture(renderer, "image/card/" + toStr(v) + "-" + toStr(s) + ".png");
        }
    }

    backCard.loadTexture(renderer, "image/card/back_of_card.png");
    cardIcon.loadTexture(renderer, "image/poker_cards.png");

    //load fonts
    textFont = TTF_OpenFont("font/Ubuntu-Title.ttf", 40);
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

void gamePlay(gameScene& phase, gameResult& res)
{
    pValue = 0;
    dValue = 0;

    Deck mainDeck, playerDeck, dealerDeck;
    mainDeck.createFullDeck();
    mainDeck.shuffle();

    playerDeck.draw(mainDeck);
    dealerDeck.draw(mainDeck);
    playerDeck.draw(mainDeck);
    dealerDeck.draw(mainDeck);

    pValue = playerDeck.getTotalValue();
    dValue = playerDeck.getTotalValue();

    if (playerDeck.isBlackJack()) {
        res = gameResult::P_BLACK_JACK;
        renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
        if (dealerDeck.isBlackJack()) {
            phase = gameScene::DEALER_PHASE;
            renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
            res = gameResult::PUSH;
            renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
            return;
        }
        else {
            res = gameResult::WIN;
            renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
            return;
        }
    }
    else {
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
                        pValue = playerDeck.getTotalValue();
                        if (pValue > BLACK_JACK) {
                            renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
                            SDL_Delay(500);
                            res = gameResult::P_BUSTS;
                            renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
                            return;
                        }
                        else if (pValue == BLACK_JACK) {
                            phase = gameScene::DEALER_PHASE;
                            dealerTurn(mainDeck, dealerDeck, res);
                            if (res == gameResult::D_BLACK_JACK)
                                res = gameResult::LOSE;
                            else if (res == gameResult::D_BUSTS)
                                res = gameResult::WIN;
                            else {
                                if (dValue == 21)
                                    res = gameResult::PUSH;
                                else res = gameResult::WIN;
                            }
                        }
                        break;
                    case SDLK_s:
                        phase = gameScene::DEALER_PHASE;
                        if (dealerDeck.isBlackJack())
                            res = gameResult::LOSE;
                        else {
                            dealerTurn(mainDeck, dealerDeck, res);
                            if (res == gameResult::D_BLACK_JACK)
                                res = gameResult::LOSE;
                            else if (res == gameResult::D_BUSTS)
                                res = gameResult::WIN;
                            else {
                                if (pValue > dValue)
                                    res = gameResult::WIN;
                                else if (pValue == dValue)
                                    res = gameResult::PUSH;
                                else res = gameResult::LOSE;
                            }
                            renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
                            return;
                        }
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
            }
            renderScene(mainDeck, playerDeck, dealerDeck, phase, res);
        }
        SDL_StopTextInput();
    }

}

void renderScene(Deck mDeck, Deck pDeck, Deck dDeck, const gameScene& phase, const gameResult& res)
{
    clear(renderer);

    table.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    switch (phase)
    {
    case gameScene::PLAYER_PHASE:
    {
        //render Dealer Hand
        int x_d = (SCREEN_WIDTH - (CARD_WIDTH + CARD_XSPACE)) / 2;
        int y_d = SCREEN_HEIGHT / 4 - CARD_HEIGHT / 2;
        Value v = dDeck.getCard(0).getValue();
        Suit s = dDeck.getCard(0).getSuit();
        cardObj[toInt(v)][toInt(s)].render(renderer, x_d, y_d, CARD_WIDTH, CARD_HEIGHT);
        backCard.render(renderer, x_d + CARD_XSPACE, y_d, CARD_WIDTH, CARD_HEIGHT);//hidden card

        //render player hand
        int psize = pDeck.deckSize();
        int x_p = (SCREEN_WIDTH - (CARD_WIDTH + (psize - 1) * CARD_XSPACE)) / 2;
        int y_p = SCREEN_HEIGHT / 2 + y_d;
        for (int i = 0; i < MAX_PLAYER_CARDS; ++i)
        {
            if (psize == 0) break;

            Value v = pDeck.getCard(i).getValue();
            Suit s = pDeck.getCard(i).getSuit();
            cardObj[toInt(v)][toInt(s)].render(renderer, x_p, y_p, CARD_WIDTH, CARD_HEIGHT);
            --psize;
            x_p += CARD_XSPACE;
        }

        //render player hand's value
        {
            int x = (SCREEN_WIDTH - t_pTotalVal.getWidth()) / 2;
            int y = y_p + CARD_HEIGHT + y_d / 2;
            t_pTotalVal.setContent("Player: " + std::to_string(pValue));
            t_pTotalVal.loadText(renderer, textFont);
            t_pTotalVal.render(renderer, x, y);
        }

        //render number of the main deck
        {
            int x = SCREEN_WIDTH * 7 / 8;
            int y = SCREEN_HEIGHT / 10;
            t_remainCards.setContent(std::to_string(mDeck.deckSize()));
            t_remainCards.loadText(renderer, textFont);
            t_remainCards.render(renderer, x, y);

            cardIcon.render(renderer, x + t_remainCards.getWidth() + 10, y,
                t_remainCards.getHeight(), t_remainCards.getHeight());
        }
    }
    break;
    case gameScene::DEALER_PHASE:
    {
        //render Dealer Hand
        int dsize = dDeck.deckSize();
        int x_d = (SCREEN_WIDTH - (CARD_WIDTH + CARD_XSPACE)) / 2;
        int y_d = SCREEN_HEIGHT / 4 - CARD_HEIGHT / 2;
        for (int i = 0; i < MAX_DEALER_CARDS; ++i)
        {
            if (dsize == 0) break;

            Value v = pDeck.getCard(i).getValue();
            Suit s = pDeck.getCard(i).getSuit();
            cardObj[toInt(v)][toInt(s)].render(renderer, x_d, y_d, CARD_WIDTH, CARD_HEIGHT);

            //render dealer's hand value
            int xVal = (SCREEN_WIDTH - t_dTotalVal.getWidth()) / 2;
            int yVal = (y_d - t_dTotalVal.getHeight()) / 2;
            t_dTotalVal.setContent("Dealer: " + std::to_string(dValue));
            t_dTotalVal.loadText(renderer, textFont);
            t_dTotalVal.render(renderer, xVal, yVal);
            
            --dsize;
            x_d += CARD_XSPACE;
            SDL_Delay(500);
        }

        //render player hand
        int psize = pDeck.deckSize();
        int x_p = (SCREEN_WIDTH - (CARD_WIDTH + (psize - 1) * CARD_XSPACE)) / 2;
        int y_p = SCREEN_HEIGHT / 2 + y_d;
        for (int i = 0; i < MAX_PLAYER_CARDS; ++i)
        {
            if (psize == 0) break;

            Value v = pDeck.getCard(i).getValue();
            Suit s = pDeck.getCard(i).getSuit();
            cardObj[toInt(v)][toInt(s)].render(renderer, x_p, y_p, CARD_WIDTH, CARD_HEIGHT);
            --psize;
            x_p += CARD_XSPACE;
        }

        //render player hand's value
        {
            int x = (SCREEN_WIDTH - t_pTotalVal.getWidth()) / 2;
            int y = y_p + CARD_HEIGHT + y_d / 2;
            t_pTotalVal.setContent("Player: " + std::to_string(pValue));
            t_pTotalVal.loadText(renderer, textFont);
            t_pTotalVal.render(renderer, x, y);
        }

        //render number of the main deck
        {
            int x = SCREEN_WIDTH * 7 / 8;
            int y = SCREEN_HEIGHT / 10;
            t_remainCards.setContent(std::to_string(mDeck.deckSize()));
            t_remainCards.loadText(renderer, textFont);
            t_remainCards.render(renderer, x, y);

            cardIcon.render(renderer, x + t_remainCards.getWidth() + 10, y,
                t_remainCards.getHeight(), t_remainCards.getHeight());
        }
    }
    break;
    default:
        break;
    }
    
    int xres = (SCREEN_WIDTH - RES_WIDTH) / 2;
    int yres = (SCREEN_HEIGHT - RES_HEIGHT) / 2;

    switch (res)
    {
    case gameResult::P_BLACK_JACK:
    {


        result.loadTexture(renderer, "image/blackjack.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
        SDL_Delay(DELAY_TIME);
        return;
    }
    case gameResult::P_BUSTS:
    {
        result.loadTexture(renderer, "image/busts_and_lose.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
        SDL_Delay(DELAY_TIME);
    }
    case gameResult::WIN:
    {
        result.loadTexture(renderer, "image/win.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
        SDL_Delay(DELAY_TIME);
        return;
    }
    case gameResult::PUSH:
    {
        result.loadTexture(renderer, "image/push.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
        SDL_Delay(DELAY_TIME);
        return;
    }
    case gameResult::LOSE:
    {
        result.loadTexture(renderer, "image/lose.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
        SDL_Delay(DELAY_TIME);
        return;
    }
    default:
        break;
    }

    display(renderer);
}
