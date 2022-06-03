#include "Game.h"

Game::Game(const int& p_w, const int& p_h, const char p_title[], const char iconFile[])
	:window(nullptr), renderer(nullptr), textFont(nullptr), dVal(0),
    pVal(0), bank(PLAYER_START_CASH), input(""), quit(false), bet(0)
{
    if (!init(p_w, p_h, p_title, iconFile)) {
        std::cout << "Init has failed!" << std::endl;
        exit(1);
    }
}

Game::~Game()
{
    kill();
}

bool Game::init(const int& p_w, const int& p_h, const char p_title[], const char iconFile[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL Init has failed. Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cout << "IMG Init has failed. Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() < 0) {
        std::cout << "TTF Init has failed. Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Unable to create window. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Unable to open audio. Error: " << Mix_GetError() << std::endl;
        return false;
    }

    SDL_Surface* iconSur = IMG_Load(iconFile);
    SDL_SetWindowIcon(window, iconSur);
    SDL_FreeSurface(iconSur);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Unable to create renderer. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Game::kill()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

void Game::clear()
{
    SDL_RenderClear(renderer);
}

void Game::display()
{
    SDL_RenderPresent(renderer);
}

int Game::showMenu()
{
    loadMedia();
    /*
    SDL_Point m_pos = { 0,0 };
    SDL_Rect buttonPos[menuItem];
    bool focus[menuItem] = { 0 };

    t_menuButton[0].setContent("Play Game");
    t_menuButton[0].loadText(renderer, textFont);
    t_menuButton[1].setContent("Exit");
    t_menuButton[1].loadText(renderer, textFont);

    buttonPos[0].x = (SCREEN_WIDTH - t_menuButton[0].getWidth()) / 2;
    buttonPos[0].y = (SCREEN_HEIGHT - t_menuButton[0].getHeight()) / 2;
    buttonPos[0].w = t_menuButton[0].getWidth();
    buttonPos[0].h = t_menuButton[0].getHeight();
    buttonPos[1] = { buttonPos[0].x, buttonPos[0].y + t_menuButton[0].getHeight() + 10,
                    t_menuButton[1].getWidth(), t_menuButton[1].getHeight()};

    SDL_Event e;
    while (!quit)
    {
        clear();
        SDL_GetMouseState(&cursor.x, &cursor.y);
        background.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                return EXIT;
                break;
                /*
            case SDL_MOUSEMOTION:
            {
                m_pos = { e.motion.x, e.motion.y };
                for (int i = 0; i < menuItem; i++)
                {
                    if (t_menuButton[i].checkFocus(m_pos, buttonPos[i])) {
                        if (!focus[i]) {
                            focus[i] = true;
                            t_menuButton[i].setColor(RED);
                        }
                    }
                    else {
                        if (focus[i]) {
                            focus[i] = false;
                            t_menuButton[i].setColor(WHITE);
                        }
                    }
                }
            }
                break;
                
            case SDL_MOUSEBUTTONDOWN:
            {
                for (int i = 0; i < menuItem; i++)
                {
                    if (focus[i]) {
                        switch (i)
                        {
                        case 0:
                            return PLAY;
                        case 1:
                            return EXIT;
                        default:
                            break;
                        }
                    }
                }
            }
            break;                                 
            default:
                break;
            }
            
            
            for (int i = 0; i < menuItem; i++)
            {   
                if (SDL_HasIntersection(&cursor, &buttonPos[i])) t_menuButton[i].setColor(RED);
                t_menuButton[i].render(renderer, buttonPos[i].x, buttonPos[i].y);
            }
            
            display();
        }
    }
    */
    scene = gameScene::START_MENU;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                kill();
                exit(0);
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    return EXIT;
                return PLAY;
                break;
            default:
                break;
            }
        }
        renderScene();
    }
}
void Game::startNewGame()
{
    loadMedia();

    pVal = 0;
    dVal = 0;
    bank = PLAYER_START_CASH;
    mainDeck.createFullDeck();
    mainDeck.shuffle();
    scene = gameScene::BET;
    res = gameResult::BEGIN;
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(music, -1);
    }
    while (gameOver() == false) {
        playOneRound();
    }
    scene = gameScene::PLAY_AGAIN;
    res = gameResult::CONTINUE;
    int choice = endGame();
    if (choice == PLAY_AGAIN)
        startNewGame();
}

void Game::betting()
{
    quit = false;
    SDL_Event e;
    SDL_StartTextInput();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                kill();
                exit(0);
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_a:
                    input = std::to_string(bank);
                    break;
                case SDLK_0:
                    if (input != "") {
                        input += "0";
                    }
                    break;
                case SDLK_1:
                    input += "1";
                    break;
                case SDLK_2:
                    input += "2";
                    break;
                case SDLK_3:
                    input += "3";
                    break;
                case SDLK_4:
                    input += "4";
                    break;
                case SDLK_5:
                    input += "5";
                    break;
                case SDLK_6:
                    input += "6";
                    break;
                case SDLK_7:
                    input += "7";
                    break;
                case SDLK_8:
                    input += "8";
                    break;
                case SDLK_9:
                    input += "9";
                    break;
                case SDLK_BACKSPACE:
                    if (input.size())
                        input.pop_back();
                    break;
                case SDLK_RETURN:
                    {
                        if (input != "") {
                            int tmp = std::stoi(input);
                            if (tmp <= bank) {
                                bet = tmp;
                                input = "";
                                scene = gameScene::PLAYER_PHASE;
                                return;
                            }
                        }
                    }
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    kill();
                    exit(0);
                default:
                    break;
                }
            default:
                break;
            }

        }
        renderScene();
    }
}

void Game::playOneRound()
{
    scene = gameScene::BET;
    res = gameResult::BEGIN;
    input = "";
    bet = 0;
    betting();
    bank -= bet;
    bool endRound = false;
    bool blackJack = false;

    if (blackJack == true) {
        playerDeck.addCard(Value::ACE, Suit::SPADE);
        playerDeck.addCard(Value::KING, Suit::SPADE);
        mainDeck.removeCard(Value::ACE, Suit::SPADE);
        mainDeck.removeCard(Value::KING, Suit::SPADE);
        dealerDeck.draw(mainDeck);
        dealerDeck.draw(mainDeck);
    }
    else {
        playerDeck.draw(mainDeck);
        dealerDeck.draw(mainDeck);
        playerDeck.draw(mainDeck);
        dealerDeck.draw(mainDeck);
    }

    pVal = playerDeck.getTotalValue();
    dVal = dealerDeck.getTotalValue();

    if (playerDeck.isBlackJack()) {
        res = gameResult::P_BLACK_JACK;
        t_pTotalVal.setColor(YELLOW);
        renderScene();
        SDL_Delay(DELAY_TIME);
        scene = gameScene::DEALER_PHASE;
        res = gameResult::CONTINUE;
        renderScene();
        if (dealerDeck.isBlackJack()) {
            scene = gameScene::DEALER_PHASE;
            renderScene();
            res = gameResult::PUSH;
            renderScene();
            endRound = true;
        }
        else {
            res = gameResult::WIN;
            renderScene();
            endRound = true;
        }
        SDL_Delay(DELAY_TIME);
    }
    else {
        quit = false;
        SDL_Event e;
        SDL_StartTextInput();
        while (!quit && !endRound) {
            while (SDL_PollEvent(&e) != 0)
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    quit = true;
                    kill();
                    exit(0);
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        kill();
                        exit(0);
                    case SDLK_h:
                        playerDeck.draw(mainDeck);
                        pVal = playerDeck.getTotalValue();
                        if (pVal > BLACK_JACK) {
                            res = gameResult::P_BUSTS;
                            t_pTotalVal.setColor(RED);
                            endRound = true;
                        }
                        else if (pVal == BLACK_JACK) {
                            scene = gameScene::DEALER_PHASE;
                            dealerTurn();
                            if (res == gameResult::D_BLACK_JACK) {
                                t_dTotalVal.setColor(YELLOW);
                                res = gameResult::LOSE;
                                endRound = true;
                            }

                            else if (res == gameResult::D_BUSTS) {
                                t_dTotalVal.setColor(RED);
                                res = gameResult::WIN;
                                endRound = true;
                            }

                            else {
                                if (dVal == 21) {
                                    res = gameResult::PUSH;
                                    endRound = true;
                                }
                                else {
                                    res = gameResult::WIN;
                                    endRound = true;
                                }
                            }
                        }
                        break;
                    case SDLK_s:
                        scene = gameScene::DEALER_PHASE;
                        if (dealerDeck.isBlackJack()) {
                            t_dTotalVal.setColor(YELLOW);
                            res = gameResult::LOSE;
                            endRound = true;
                        }
                        else {
                            dealerTurn();
                            if (res == gameResult::D_BLACK_JACK) {
                                res = gameResult::LOSE;
                                endRound = true;
                            }
                            else if (res == gameResult::D_BUSTS) {
                                t_dTotalVal.setColor(RED);
                                res = gameResult::WIN;
                                endRound = true;
                            }
                            else {
                                if (pVal > dVal) {
                                    res = gameResult::WIN;
                                    endRound = true;
                                }
                                else if (pVal == dVal) {
                                    res = gameResult::PUSH;
                                    endRound = true;
                                }
                                else {
                                    res = gameResult::LOSE;
                                    endRound = true;
                                }
                            }
                        }
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
            }
            renderScene();
            if (endRound == true)
                SDL_Delay(DELAY_TIME);

        }
        SDL_StopTextInput();
    }
    if (endRound) {
        playerDeck.moveAllToDeck(mainDeck);
        dealerDeck.moveAllToDeck(mainDeck);

        if (res == gameResult::WIN)
            bank = bank + bet * 2;
        else if (res == gameResult::PUSH)
            bank += bet;
    }
}

void Game::dealerTurn()
{
    dVal = dealerDeck.getTotalValue();
    if (dealerDeck.isBlackJack()) {
        res = gameResult::D_BLACK_JACK;
        return;
    }

    while (dVal < 17) {
        dealerDeck.draw(mainDeck);
        dVal = dealerDeck.getTotalValue();
    }
    if (dealerDeck.isBusts()) {
        res = gameResult::D_BUSTS;
    }
    else
        res = gameResult::CONTINUE;
}

int Game::endGame()
{
    for (int i = 0; i < mainDeck.deckSize(); ++i)
    {
        mainDeck.removeCard(i);
    }
    for (int i = 0; i < playerDeck.deckSize(); ++i)
    {
        playerDeck.removeCard(i);
    }
    for (int i = 0; i < dealerDeck.deckSize(); ++i)
    {
        dealerDeck.removeCard(i);
    }
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                kill();
                exit(0);
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_SPACE:
                    return PLAY_AGAIN;
                    break;
                case SDLK_ESCAPE:
                    return EXIT;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        renderScene();
    }
}

bool Game::gameOver()
{
    return (quit || bank == 0);
}


void Game::loadMedia()
{
    //load pics
    background.loadTexture(renderer, "image/background.png");
    table.loadTexture(renderer, "image/table.png");
    menuTitle.loadTexture(renderer, "image/menu title.png");

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

    //load sound
    music = Mix_LoadMUS("music/xo so kien thiet remix.mp3");
}

void Game::renderScene()
{
    clear();
    if (res == gameResult::BEGIN) {
        t_dTotalVal.setColor(WHITE);
        t_pTotalVal.setColor(WHITE);
    }

    if (scene == gameScene::PLAYER_PHASE || scene == gameScene::DEALER_PHASE)
        table.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    else
        background.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(scene == gameScene::BET || scene == gameScene::PLAYER_PHASE || scene == gameScene::DEALER_PHASE)
    {
        TextObject t_bank;
        t_bank.setContent("Bank: " + std::to_string(bank));
        t_bank.loadText(renderer, textFont);
        int x = 20;
        int y = SCREEN_HEIGHT - t_bank.getHeight() - x;
        t_bank.render(renderer, x, y);
    }
    switch (scene)
    {
    case gameScene::START_MENU:
    {
        {
            int w = menuTitle.getFrame().w;
            int h = menuTitle.getFrame().h;
            int x = (SCREEN_WIDTH - w) / 2;
            int y = (SCREEN_HEIGHT - h) / 2;
            SDL_Rect src = { 0,0,w * 2 / 3,h * 3 / 5 };
            menuTitle.render(renderer, x, y, w, h , src);
        }
        {
            TextObject dialog;
            dialog.setContent("Press any key to start");
            dialog.loadText(renderer, textFont);
            int x = (SCREEN_WIDTH - dialog.getWidth()) / 2;
            int y = (SCREEN_HEIGHT - dialog.getHeight()) * 3 / 4;
            dialog.render(renderer, x, y);
        }
    }
    break;
    case gameScene::PLAY_AGAIN:
    {
        {
            
            TextObject gameOver;
            gameOver.setContent("bankrupt!!!");
            gameOver.loadText(renderer, textFont);
            int x = (SCREEN_WIDTH - gameOver.getWidth()) / 2;
            int y = (SCREEN_HEIGHT - gameOver.getHeight()) / 2;
            gameOver.render(renderer, x, y);

            TextObject dialog;
            dialog.setContent("Press space to play again");
            dialog.loadText(renderer, textFont);
            dialog.render(renderer, (SCREEN_WIDTH - dialog.getWidth()) / 2, y + gameOver.getHeight() + 200);

            
        }
    }
    break;
    case gameScene::BET:
    {
        TextObject dialog;
        dialog.setContent("How much you want to bet (1 - " + std::to_string(bank) + ")? ");
        dialog.loadText(renderer, textFont);
        int x = (SCREEN_WIDTH - dialog.getWidth()) / 2;
        int y = (SCREEN_HEIGHT - dialog.getHeight()) / 3;
        dialog.render(renderer, x, y);

        TextObject betNum;
        if (input != "")
            betNum.setContent(input);
        else betNum.setContent(" ");
        betNum.loadText(renderer, textFont);
        betNum.render(renderer, x + dialog.getWidth() + 10, y);

        TextObject instruction;
        instruction.setContent("press a to all in");
        instruction.loadText(renderer, textFont);
        instruction.render(renderer, x, y + dialog.getHeight() + 100);
    }
    break;
    case gameScene::PLAYER_PHASE:
    {
        //instruction
        {
            SDL_Point pos[2];
            TextObject instruction[2];
            instruction[0].setContent("h: hit");
            instruction[0].loadText(renderer, textFont);
            pos[0].x = (SCREEN_WIDTH - instruction[0].getWidth()) * 3 / 4;
            pos[0].y = (SCREEN_HEIGHT - instruction[0].getHeight()) / 2;

            instruction[1].setContent("s: stand");
            instruction[1].loadText(renderer, textFont);
            pos[1].x = pos[0].x;
            pos[1].y = pos[0].y + instruction[0].getHeight() + 10;

            for (int i = 0; i < 2; i++)
            {
                instruction[i].render(renderer, pos[i].x, pos[i].y);
            }
        }

        //render Dealer Hand
        int x_d = (SCREEN_WIDTH - (CARD_WIDTH + CARD_XSPACE)) / 2;
        int y_d = SCREEN_HEIGHT / 4 - CARD_HEIGHT / 2;
        Value v = dealerDeck.getCard(0).getValue();
        Suit s = dealerDeck.getCard(0).getSuit();
        cardObj[toInt(v)][toInt(s)].render(renderer, x_d, y_d, CARD_WIDTH, CARD_HEIGHT);
        backCard.render(renderer, x_d + CARD_XSPACE, y_d, CARD_WIDTH, CARD_HEIGHT);//hidden card

        //render player hand
        int psize = playerDeck.deckSize();
        int x_p = (SCREEN_WIDTH - (CARD_WIDTH + (psize - 1) * CARD_XSPACE)) / 2;
        int y_p = SCREEN_HEIGHT / 2 + y_d;

        for (int i = 0; i < MAX_PLAYER_CARDS; ++i)
        {
            if (psize == 0) break;

            Value v = playerDeck.getCard(i).getValue();
            Suit s = playerDeck.getCard(i).getSuit();
            cardObj[toInt(v)][toInt(s)].render(renderer, x_p, y_p, CARD_WIDTH, CARD_HEIGHT);
            --psize;
            x_p += CARD_XSPACE;
        }

        //render player hand's value
        {
            t_pTotalVal.setContent("Player: " + std::to_string(pVal));
            t_pTotalVal.loadText(renderer, textFont);
            int x = (SCREEN_WIDTH - t_pTotalVal.getWidth()) / 2;
            int y = y_p + CARD_HEIGHT + y_d / 2;
            t_pTotalVal.render(renderer, x, y);
        }

        //render number of the main deck
        /*
        {
            int x = SCREEN_WIDTH * 7 / 8;
            int y = SCREEN_HEIGHT / 10;
            t_remainCards.setContent(std::to_string(mDeck.deckSize()));
            t_remainCards.loadText(renderer, textFont);
            t_remainCards.render(renderer, x, y);

            cardIcon.render(renderer, x + t_remainCards.getWidth() + 10, y,
                t_remainCards.getHeight(), t_remainCards.getHeight());
        }
        */
    }
    break;
    case gameScene::DEALER_PHASE:
    {
        int dsize = dealerDeck.deckSize();
        int psize = playerDeck.deckSize();
        int x_d = (SCREEN_WIDTH - (CARD_WIDTH + (dsize - 1) * CARD_XSPACE)) / 2;;
        int y_d = SCREEN_HEIGHT / 4 - CARD_HEIGHT / 2;

        int x_p = (SCREEN_WIDTH - (CARD_WIDTH + (psize - 1) * CARD_XSPACE)) / 2;
        int y_p = SCREEN_HEIGHT / 2 + y_d;

        //instruction
        {
            SDL_Point pos[2];
            TextObject instruction[2];
            instruction[0].setContent("h: hit");
            instruction[0].loadText(renderer, textFont);
            pos[0].x = (SCREEN_WIDTH - instruction[0].getWidth()) * 2 / 3;
            pos[0].y = (SCREEN_HEIGHT - instruction[0].getHeight()) / 2;

            instruction[1].setContent("s: stand");
            instruction[1].loadText(renderer, textFont);
            pos[1].x = pos[0].x;
            pos[1].y = pos[0].y + instruction[0].getHeight() + 10;

            for (int i = 0; i < 2; i++)
            {
                instruction[i].render(renderer, pos[i].x, pos[i].y);
            }
        }

        //render player hand
        {


            for (int i = 0; i < MAX_PLAYER_CARDS; ++i)
            {
                if (psize == 0) break;

                Value v = playerDeck.getCard(i).getValue();
                Suit s = playerDeck.getCard(i).getSuit();
                cardObj[toInt(v)][toInt(s)].render(renderer, x_p, y_p, CARD_WIDTH, CARD_HEIGHT);
                --psize;
                x_p += CARD_XSPACE;
            }

            //render player hand's value
            {

                t_pTotalVal.setContent("Player: " + std::to_string(pVal));
                t_pTotalVal.loadText(renderer, textFont);
                int xpVal = (SCREEN_WIDTH - t_pTotalVal.getWidth()) / 2;
                int ypVal = y_p + CARD_HEIGHT + y_d / 2;
                t_pTotalVal.render(renderer, xpVal, ypVal);
            }
            //render Dealer Hand
            {
                //std::cout << dsize;


                for (int i = 0; i < MAX_DEALER_CARDS; ++i)
                {
                    if (dsize == 0) break;

                    Value v = dealerDeck.getCard(i).getValue();
                    Suit s = dealerDeck.getCard(i).getSuit();
                    cardObj[toInt(v)][toInt(s)].render(renderer, x_d, y_d, CARD_WIDTH, CARD_HEIGHT);

                    //render dealer's hand value
                    if (dsize == 1)
                    {
                        t_dTotalVal.setContent("Dealer: " + std::to_string(dVal));
                        t_dTotalVal.loadText(renderer, textFont);
                        int xdVal = (SCREEN_WIDTH - t_dTotalVal.getWidth()) / 2;
                        int ydVal = (y_d - t_dTotalVal.getHeight()) / 2;
                        t_dTotalVal.render(renderer, xdVal, ydVal);
                    }
                    --dsize;
                    x_d += CARD_XSPACE;
                    if (i != 0) {
                        SDL_Delay(800);
                        display();
                    }
                }
            }



            //render number of the main deck
            /*
            {
                int x = SCREEN_WIDTH * 7 / 8;
                int y = SCREEN_HEIGHT / 10;
                t_remainCards.setContent(std::to_string(mDeck.deckSize()));
                t_remainCards.loadText(renderer, textFont);
                t_remainCards.render(renderer, x, y);

                cardIcon.render(renderer, x + t_remainCards.getWidth() + 10, y,
                    t_remainCards.getHeight(), t_remainCards.getHeight());
            }
            */
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
    }
    break;
    case gameResult::P_BUSTS:
    {
        result.loadTexture(renderer, "image/busts_and_lose.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
    }
    break;
    case gameResult::WIN:
    {
        result.loadTexture(renderer, "image/win.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
    }
    break;
    case gameResult::PUSH:
    {
        result.loadTexture(renderer, "image/push.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
    }
    break;
    case gameResult::LOSE:
    {
        result.loadTexture(renderer, "image/lose.png");
        result.render(renderer, xres, yres, RES_WIDTH, RES_HEIGHT);
    }
    break;
    default:
        break;
    }

    display();
}
