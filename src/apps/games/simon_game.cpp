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

    hal->gfx()->fillFrame(0, 120, 120, 120, dimColor(ui->getWarningColor(), 60));
    hal->gfx()->fillFrame(120, 120, 120, 120, dimColor(ui->getDangerColor(), 60));
    hal->gfx()->fillFrame(120, 0, 120, 120, dimColor(ui->getSuccessColor(), 60));

    hal->gfx()->setTextSize(2);
    hal->gfx()->setTextColor(rgb565(255, 255, 255));
    hal->gfx()->setTextCursor(25, 120);
    hal->gfx()->print("Welcome to Simon!");

    hal->gfx()->setTextSize(2);
    hal->gfx()->setTextCursor(150, 48);
    hal->gfx()->print("Start");

    if (hal->btnHasGoneDown(BUTTON_3)){
        gameRunning = true;
    }
}

void OswAppSimonGame::simonGame(){
    //OSW_LOG_D("simonGame");

    if(gameRunning){
        buttonController();
        displayColors();

        if(playerOrder.size() == colors.size()){
            checker();
            colors.push_back(random(1, 4));
        }
    }
    else{
        colors.clear();
        score = 0;
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

    hal->gfx()->fillFrame(0, 120, 120, 120, dimColor(ui->getWarningColor(), 60));
    hal->gfx()->fillFrame(120, 120, 120, 120, dimColor(ui->getDangerColor(), 60));
    hal->gfx()->fillFrame(120, 0, 120, 120, dimColor(ui->getSuccessColor(), 60));

    hal->gfx()->print("Score");
    hal->gfx()->setTextCursor(74, 70);
    hal->gfx()->print(score);

    uint32_t currentMillis = millis();
     if(currentMillis - prevTime >= 1000){
        prevTime = currentMillis;
        if(printIdx < colors.size()){
            printIdx++;
        }
     }
     else{
        if(printIdx < colors.size()){
            //DEBUG colorID
            //hal->gfx()->print(colors[printIdx]);

            switch (colors[printIdx])
            {
            case 1:
                hal->gfx()->fillFrame(0, 120, 120, 120, ui->getWarningColor());
                break;
            
            case 2:
                hal->gfx()->fillFrame(120, 120, 120, 120, ui->getDangerColor());
                break;
            
            case 3:
                hal->gfx()->fillFrame(120, 0, 120, 120, ui->getSuccessColor());
                break;
            
            default:
                break;
            }

            
        }
     }
}

void OswAppSimonGame::checker(){
    for(int i = 0; i < colors.size(); i++){
        if(playerOrder[i] != colors[i]){
            gameRunning = false;
        }
    }
    if(gameRunning) score++;
    playerOrder.clear();
    printIdx = 0;
}

/* TODO LIST:
    
    Difficulty levels
    Accelerates colors frequency with time
    Fix first color appear too quickly
     */
