#ifndef OSW_APP_GIF_PLAYER_H
#define OSW_APP_GIF_PLAYER_H

#include <osw_hal.h>

#include <OswAppV1.h>

class OswAppGifPlayer : public OswApp {
  public:
    OswAppGifPlayer(void) {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OswAppGifPlayer() {};

  private:
};

#endif
