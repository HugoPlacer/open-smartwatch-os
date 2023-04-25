#ifndef OSW_APP_SIMON_GAME_H
#define OSW_APP_SIMON_GAME_H

#include <osw_hal.h>
#include <osw_ui.h>

#include "osw_app.h"

#include <iostream>
#include <vector>

class OswAppSimonGame  : public OswApp {
  public:
    OswAppSimonGame (void) {
        ui = OswUI::getInstance();
    };
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OswAppSimonGame () {};

  private:
    OswUI* ui;

    std::vector<int> colors;
    std::vector<int> pOrder;

    int score = 1;
    int prevTime = 0;

    bool gameRunning = false;

    // Game logics
    void simonGame();
    void waitingRoom();
    void displayColors();
    void playerTurn(int *order);
    void checker(int *order);
    void buttonController();
    // Controls
};

#endif
