#include <gfx_util.h>
#include <osw_hal.h>
#include <osw_ui.h>

#include "apps/examples/HugoTest.h"
#include "assets/img/static/hugo.png.h"

OswAppHugoTest::OswAppHugoTest(): image(hugo_png, hugo_png_length, hugo_png_width, hugo_png_height)  {

}


const char* OswAppHugoTest::getAppId() {
    return "osw.example.v2"; // use less than 15 characters to avoid issues with some api calls (e.g. Preferences)
}

const char* OswAppHugoTest::getAppName() {
    return LANG_EXAMPLE " " LANG_APP " v2";
}

void OswAppHugoTest::onStart() {
    OswAppV2::onStart(); // always make sure to call the base class method!
    // This is where you initialise code, gets called before this app is shown

    // Report that we support short presses on all buttons
    this->knownButtonStates[Button::BUTTON_SELECT] = ButtonStateNames::SHORT_PRESS;
    this->knownButtonStates[Button::BUTTON_UP] = ButtonStateNames::SHORT_PRESS;
    this->knownButtonStates[Button::BUTTON_DOWN] = ButtonStateNames::SHORT_PRESS;

    // Here is a snippet to also "support" double presses (on BUTTON_SELECT) - note that this WILL DELAY the reporting of any short press events on that button (as it may needs to wait for the second press)
    this->knownButtonStates[Button::BUTTON_SELECT] = (OswAppV2::ButtonStateNames) (this->knownButtonStates[Button::BUTTON_SELECT] | OswAppV2::ButtonStateNames::DOUBLE_PRESS); // OR to set the bit
    // ...so we will disable it again ;)
    this->knownButtonStates[Button::BUTTON_SELECT] = (OswAppV2::ButtonStateNames) (this->knownButtonStates[Button::BUTTON_SELECT] ^ OswAppV2::ButtonStateNames::DOUBLE_PRESS); // XOR to toggle the bit

    this->viewFlags = (OswAppV2::ViewFlags) (this->viewFlags | OswAppV2::ViewFlags::KEEP_DISPLAY_ON); // by default we want to keep the display on

    counter = 0;
}

void OswAppHugoTest::onLoop() {
    OswAppV2::onLoop(); // always make sure to call the base class method!
    // This section of the code is where you can write the main logic
     counter++;
      this->needsRedraw = this->needsRedraw or counter != counter - 1;
}

void OswAppHugoTest::onDraw() {
    OswAppV2::onDraw(); // always make sure to call the base class method!

    //hal->gfx()->setTextCenterAligned();
    //hal->gfx()->setTextColor(rgb565(0,0,255));
    //hal->gfx()->setTextSize(2);
    //hal->gfx()->setTextCursor(DISP_W / 2, DISP_H / 2);
    //hal->gfx()->print("Holaaa :)");

    //hal->gfx()->drawCircle(DISP_W / 1.25, DISP_H / 4, abs(sin(counter / 100)) * 25, rgb565(0,255,0));
    //hal->gfx()->drawHourTicks(DISP_W / 2, DISP_H / 2, 100, 80, rgb565(0,255,0));

    //hal->gfx()->fillCircle(DISP_W / 4, DISP_H / 4, abs(sin(counter / 100)) * 25, rgb565(0,255,0));

    //this->image.draw(hal->gfx(), abs(sin(counter / 100) + 1.75) * 50, abs(sin(counter / 100) + 1.75) * 50, 1.0, OswImage::Alignment::CENTER, OswImage::Alignment::CENTER);

    //hal->gfx()->drawThickTick(DISP_W * 0.5, DISP_H * 0.5, 0, 16, 180 + ( 360.0 / 60.0 * second ), 1, ui->getForegroundColor());
    //hal->gfx()->drawThickTick(DISP_W * 0.5, DISP_H * 0.5, 50, 60, counter, 4, ui->getForegroundColor());

    this->image.draw(hal->gfx(), DISP_W * 0.5, DISP_H * 0.5, counter, 1.0, OswImage::Alignment::CENTER, OswImage::Alignment::CENTER);

    uint32_t second = 0;
    uint32_t minute = 0;
    uint32_t hour = 0;
    hal->getLocalTime(&hour, &minute, &second);

    hal->gfx()->fillCircle(rpx(DISP_W * 0.5, 100, 360.0 / 60.0 * second), rpy(DISP_W * 0.5, 100, 360.0 / 60.0 * second), 5, ui->getForegroundColor());
    hal->gfx()->fillCircle(rpx(DISP_W * 0.5, 80, 360.0 / 60.0 * (1.0 * minute + second / 60.0)), rpy(DISP_W * 0.5, 80, 360.0 / 60.0 * (1.0 * minute + second / 60.0)), 5, ui->getForegroundColor());
    hal->gfx()->fillCircle(rpx(DISP_W * 0.5, 60, 360.0 / 12.0 * (1.0 * hour + minute / 60.0)), rpy(DISP_W * 0.5, 60, 360.0 / 12.0 * (1.0 * hour + minute / 60.0)), 5, ui->getForegroundColor());

    //hal->gfx()->fillFrame(rpx(DISP_W * 0.5, 100, 360.0 / 60.0 * second), rpy(DISP_W * 0.5, 100, 360.0 / 60.0 * second), rpx((DISP_W * 0.5) + 10, 100, 360.0 / 60.0 * second), rpy((DISP_W * 0.5) + 10, 100, 360.0 / 60.0 * second), ui->getDangerColor());
}

void OswAppHugoTest::onDrawOverlay() {
    /*
        In this function we do nothing, but here you could draw stuff like an indicator of some kind.
        But... Why are we calling the parents method at last here? Because the parent method may want
        to draw something on top of what we are drawing here. So we need to make sure that we draw our
        stuff first and then call the parent method. This is due to the implicit convention, that this
        method will draw always on TOP of the previous content - hence called "overlay".
    */

    OswAppV2::onDrawOverlay(); // here at last!!! (and always make sure to call the base class method)
}

void OswAppHugoTest::onButton(Button id, bool up, ButtonStateNames state) {
    OswAppV2::onButton(id, up, state); // always make sure to call the base class method!
}

void OswAppHugoTest::onStop() {
    OswAppV2::onStop(); // always make sure to call the base class method!

    // This is where you de-initialize stuff, gets called when another app is shown
}
