#include "./apps/games/simon_game.h"

#include <gfx_util.h>
#include <osw_app.h>
#include <osw_config.h>
#include <osw_config_keys.h>
#include <osw_hal.h>

void OswAppSimonGame::setup() {
    colors.push_back(random(1, 4));
}

void OswAppSimonGame::loop() {
    simonGame();
}

void OswAppSimonGame::stop() {

}

void OswAppSimonGame::buttonController(){
    OswHal* hal = OswHal::getInstance();
     if(hal->btnHasGoneDown(BUTTON_1)){
            playerOrder.push_back(1);
         }

          if(hal->btnHasGoneDown(BUTTON_2)){
            playerOrder.push_back(2);
         }

          if(hal->btnHasGoneDown(BUTTON_3)){
            playerOrder.push_back(3);
         }
}

void OswAppSimonGame::waitingRoom(){
    OswHal* hal = OswHal::getInstance();

    hal->gfx()->fill(0);
    hal->gfx()->setTextSize(2);
    hal->gfx()->setTextColor(rgb565(255, 255, 255));
    hal->gfx()->setTextCursor(30, 120);
    hal->gfx()->print("Welcome to Simon!");

    if (hal->btnHasGoneDown(BUTTON_3)){
        gameRunning = true;
    }
}

void OswAppSimonGame::simonGame(){
    //OSW_LOG_D("simonGame");

    if(gameRunning){
        buttonController();
        displayColors();

        //playerTurn();
        if(playerOrder.size() == colors.size()){
            checker();
            colors.push_back(random(1, 4));
        }
    }
    else{
        colors.clear();
        waitingRoom();
    }
}

void OswAppSimonGame::displayColors(){
    //OSW_LOG_D("displayColors");
    OswHal* hal = OswHal::getInstance();

    hal->gfx()->fill(0);
    hal->gfx()->setTextSize(2);
    hal->gfx()->setTextColor(rgb565(255, 255, 255));
    hal->gfx()->setTextCursor(50, 50);

    uint32_t currentMillis = millis();
     if(currentMillis - prevTime >= 1000){
        prevTime = currentMillis;
        if(printIdx < colors.size()){
            printIdx++;
        }
     }
     else{
        if(printIdx < colors.size()){
            hal->gfx()->print(colors[printIdx]);
            uint16_t frameColor = rgb565(255, 255, 255);

            switch (colors[printIdx])
            {
            case 1:
                frameColor = rgb565(255, 0, 0);
                break;
            
            case 2:
                frameColor = rgb565(0, 255, 0);
                break;
            
            case 3:
                frameColor = rgb565(0, 0, 255);
                break;
            
            default:
                break;
            }

            hal->gfx()->fillFrame(120, 120, 50, 50, frameColor);
        }
     }
}

void OswAppSimonGame::playerTurn(){
    OSW_LOG_D("PlayerTurn");
     OswHal* hal = OswHal::getInstance();

    int i = 0;

    while(i < colors.size()){
        
         if(hal->btnHasGoneDown(BUTTON_1)){
            //order[i] = 1;
            i++;
         }

          if(hal->btnHasGoneDown(BUTTON_2)){
            //order[i] = 2;
            i++;
         }

          if(hal->btnHasGoneDown(BUTTON_3)){
            //order[i] = 3;
            i++;
         }
    }
}

void OswAppSimonGame::checker(){
    for(int i = 0; i < colors.size(); i++){
        if(playerOrder[i] != colors[i]){
            gameRunning = false;
        }
    }
    playerOrder.clear();
    printIdx = 0;
}
