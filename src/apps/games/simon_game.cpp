#include "./apps/games/simon_game.h"

#include <gfx_util.h>
#include <osw_app.h>
#include <osw_config.h>
#include <osw_config_keys.h>
#include <osw_hal.h>

void OswAppSimonGame::setup() {
    std::srand((unsigned) time(NULL));
    colors.push_back(rand() % 3 + 1);
}

void OswAppSimonGame::loop() {
    simonGame();
}

void OswAppSimonGame::stop() {

}

void OswAppSimonGame::buttonController(){
    OswHal* hal = OswHal::getInstance();
     if(hal->btnHasGoneDown(BUTTON_1)){
            pOrder.push_back(1);
         }

          if(hal->btnHasGoneDown(BUTTON_2)){
            pOrder.push_back(2);
         }

          if(hal->btnHasGoneDown(BUTTON_3)){
            pOrder.push_back(3);
         }
}

void OswAppSimonGame::waitingRoom(){
    OswHal* hal = OswHal::getInstance();

    hal->gfx()->fill(0);
    hal->gfx()->setTextSize(2);
    hal->gfx()->setTextColor(rgb565(255, 255, 255));
    hal->gfx()->setTextCursor(50, 120);
    hal->gfx()->print("Welcome to Simon!");

    if (hal->btnHasGoneDown(BUTTON_3)){
        gameRunning = true;
    }
}

void OswAppSimonGame::simonGame(){
    OSW_LOG_D("simonGame");

    if(gameRunning){
        buttonController();
        displayColors();

        int playerOrder[colors.size()];

        //playerTurn(playerOrder);
        if(pOrder.size() == colors.size()){
            checker(playerOrder);
            colors.push_back(rand() % 3 + 1);
        }
    }
    else{
        waitingRoom();
    }
}

void OswAppSimonGame::displayColors(){
    OSW_LOG_D("displayColors");
    OswHal* hal = OswHal::getInstance();

    hal->gfx()->fill(0);
    hal->gfx()->setTextSize(2);
    hal->gfx()->setTextColor(rgb565(255, 255, 255));
    hal->gfx()->setTextCursor(50, 120);

    for(int i = 0; i < colors.size(); i++){
        hal->gfx()->print(colors[i]);
    }
}

void OswAppSimonGame::playerTurn(int *order){
    OSW_LOG_D("PlayerTurn");
     OswHal* hal = OswHal::getInstance();

    int i = 0;

    while(i < colors.size()){
        
         if(hal->btnHasGoneDown(BUTTON_1)){
            order[i] = 1;
            i++;
         }

          if(hal->btnHasGoneDown(BUTTON_2)){
            order[i] = 2;
            i++;
         }

          if(hal->btnHasGoneDown(BUTTON_3)){
            order[i] = 3;
            i++;
         }
    }
}

void OswAppSimonGame::checker(int *order){
    for(int i = 0; i < colors.size(); i++){
        if(pOrder[i] != colors[i]){
            gameRunning = false;
        }
    }
}
