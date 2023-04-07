#pragma once

#include <osw_hal.h>
#include <OswAppV2.h>

class OswAppHugoTest : public OswAppV2 {
  public:
    OswAppHugoTest();

    const char* getAppId() override;
    const char* getAppName() override;

    void onStart() override;
    void onLoop() override;
    void onDraw() override;
    void onDrawOverlay() override;
    void onStop() override;
    void onButton(Button id, bool up, ButtonStateNames state) override;

  private:
    // define global scope variables
    float counter;
    OswImage image;
};
