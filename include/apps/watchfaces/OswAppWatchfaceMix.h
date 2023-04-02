#pragma once

#include <osw_hal.h>
#include <osw_ui.h>

#include <OswAppV1.h>

class OswAppWatchfaceMix : public OswApp {
  public:
    OswAppWatchfaceMix(void) {
        ui = OswUI::getInstance();
    };
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OswAppWatchfaceMix() {};

    void dateDisplay();
    void digitalWatchDisplay();

  private:
    void analogWatchDisplay(); //thin
    OswUI* ui;
};
