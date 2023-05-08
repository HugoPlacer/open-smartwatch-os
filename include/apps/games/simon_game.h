#ifndef OSW_APP_SIMON_GAME_H
#define OSW_APP_SIMON_GAME_H

#include <osw_hal.h>
#include <osw_ui.h>

#include "osw_app.h"

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

    std::vector<uint8_t> colors;
    std::vector<uint8_t> playerOrder;

    uint8_t score = 1;
    uint32_t prevTime = 0;
    uint8_t printIdx = 0;

    bool gameRunning = false;

    // Game logics
    void simonGame();
    void waitingRoom();
    void displayColors();
    void checker();
    void buttonController();
    // Controls
};

#endif
