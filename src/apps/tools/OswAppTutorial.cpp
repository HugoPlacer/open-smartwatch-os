#include <gfx_util.h>
#include <OswAppV1.h>
#include <osw_hal.h>
#include <osw_ui.h>
#include <Preferences.h>

#include "apps/tools/OswAppTutorial.h"
#include "assets/img/icons/osw.png.h"
#include "assets/img/icons/wait.png.h"
#include "assets/img/icons/check.png.h"
#include "assets/img/icons/warning.png.h"

OswAppTutorial::OswAppTutorial(): oswIcon(osw_png, osw_png_dimensions, rgb565(200, 0, 50)) {
    bool res = nvs.begin(this->getAppId(), false);
    assert(res);
}

OswAppTutorial::~OswAppTutorial() {
    nvs.end();
}

const char* OswAppTutorial::getAppId() {
    return "osw.tutorial";
}

const char* OswAppTutorial::getAppName() {
    return "OSW Tutorial";
}

void OswAppTutorial::onStart() {
    OswAppV2::onStart(); // always make sure to call the base class method!
    this->viewFlags = (OswAppV2::ViewFlags) (this->viewFlags | OswAppV2::ViewFlags::KEEP_DISPLAY_ON);
    for(int i = 0; i < BTN_NUMBER; i++)
        this->knownButtonStates[i] = ButtonStateNames::SHORT_PRESS;

    this->screen = 0;
    this->timeout = time(nullptr);
}

void OswAppTutorial::onLoop() {
    OswAppV2::onLoop(); // always make sure to call the base class method!
    if(this->screen == 0)
        this->hsv = (millis() / 100) % 255;

    // Advance to next screen if scheduled
    if(this->nextScreenOn != 0 and this->nextScreenOn < time(nullptr)) {
        ++this->screen;
        this->nextScreenOn = 0;
    }
    
    this->needsRedraw = this->needsRedraw or this->screen == 0 or this->nextScreenOn != 0 or this->currentScreen != this->screen; // screen 0 has an animation
    this->currentScreen = this->screen;
}

void OswAppTutorial::onDraw() {
    OswAppV2::onDraw(); // always make sure to call the base class method!

    if(this->screen == 0) {
        const unsigned char maxVal = 255;
        unsigned char r, g, b;
        hsvToRgb(this->hsv, maxVal, maxVal, r, g, b);
        this->oswIcon.color = rgb565(r, g, b);
        this->oswIcon.draw(hal->gfx(), DISP_W / 2, 28, 3, OswImage::Alignment::CENTER, OswImage::Alignment::START);
        hal->gfx()->setTextSize(2);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 100);
        hal->gfx()->print(LANG_TUT_SCR0_TITLE);
        hal->gfx()->setTextSize(1);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 120);
        hal->gfx()->print(LANG_TUT_SCR0_TEXT);
        hal->gfx()->setTextCursor(DISP_W / 2, 180);
        hal->gfx()->print(LANG_TUT_ANYKEY "\n\n\n");
        hal->gfx()->setTextColor(rgb565(80, 80, 80), OswUI::getInstance()->getBackgroundColor());
        hal->gfx()->print(GIT_COMMIT_HASH);
    } else if(this->screen == 1) {
        OswIcon waiting = OswIcon(wait_png, wait_png_dimensions, rgb565(200, 0, 50));
        OswIcon checked = OswIcon(check_png, check_png_dimensions, rgb565(0, 200, 50));
        hal->gfx()->setTextSize(2);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 80);
        hal->gfx()->print(LANG_TUT_SCR1_TITLE);
        hal->gfx()->setTextSize(1);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 100);
        hal->gfx()->print(LANG_TUT_SCR1_TEXT);

        hal->gfx()->setTextSize(1);
        hal->gfx()->setTextLeftAligned();

        short y = 160;
        hal->gfx()->setTextCursor(80, y);
        hal->gfx()->print(LANG_TUT_SCR1_SHORT_PRESS);
        if(this->gotButtonShort.has_value()) {
            checked.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);
            hal->gfx()->print(" -> ");
            hal->gfx()->print(ButtonNames[this->gotButtonShort.value()]);
        } else
            waiting.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);
        y += 15;
        hal->gfx()->setTextCursor(80, y);
        hal->gfx()->print(LANG_TUT_SCR1_DOUBLE_PRESS);
        if(this->gotButtonDouble.has_value()) {
            checked.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);
            hal->gfx()->print(" -> ");
            hal->gfx()->print(ButtonNames[this->gotButtonDouble.value()]);
        } else
            waiting.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);
        y += 15;
        hal->gfx()->setTextCursor(80, y);
        hal->gfx()->print(LANG_TUT_SCR1_LONG_PRESS);
        if(this->gotButtonLong.has_value()) {
            checked.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);
            hal->gfx()->print(" -> ");
            hal->gfx()->print(ButtonNames[this->gotButtonLong.value()]);
        } else
            waiting.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);
        y += 15;
        hal->gfx()->setTextCursor(80, y);
        hal->gfx()->print(LANG_TUT_SCR1_VERY_LONG_PRESS);
        if(this->gotButtonVeryLong.has_value()) {
            checked.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);
            hal->gfx()->print(" -> ");
            hal->gfx()->print(ButtonNames[this->gotButtonVeryLong.value()]);
        } else
            waiting.draw(hal->gfx(), 80 - 5, y - 3, 1, OswImage::Alignment::END, OswImage::Alignment::CENTER);

        if(this->nextScreenOn != 0) {
            hal->gfx()->setTextCenterAligned();
            hal->gfx()->setTextCursor(DISP_W / 2, 225);
            hal->gfx()->print(this->nextScreenOn - time(nullptr));
        }
    } else if(this->screen == 2) {
        hal->gfx()->setTextSize(2);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 60);
        hal->gfx()->print(LANG_TUT_SCR2_TITLE);
        hal->gfx()->setTextSize(1);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 100);
        hal->gfx()->print(LANG_TUT_SCR2_TEXT);
        hal->gfx()->setTextColor(OswUI::getInstance()->getInfoColor(), OswUI::getInstance()->getBackgroundColor());
        hal->gfx()->print(LANG_TUT_SCR2_TEXT_COLORED);
        OswUI::getInstance()->resetTextColors();
        hal->gfx()->setTextCursor(DISP_W / 2, 180);
        hal->gfx()->print(LANG_TUT_ANYKEY);
    } else if(this->screen == 3) {
        OswIcon warning = OswIcon(warning_png, warning_png_dimensions, OswUI::getInstance()->getWarningColor());
        warning.draw(hal->gfx(), DISP_W / 2, 28, 3, OswImage::Alignment::CENTER, OswImage::Alignment::START);
        hal->gfx()->setTextSize(2);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 100);
        hal->gfx()->print(LANG_TUT_SCR3_TITLE);
        hal->gfx()->setTextSize(1);
        hal->gfx()->setTextCenterAligned();
        hal->gfx()->setTextCursor(DISP_W / 2, 120);
        hal->gfx()->print(LANG_TUT_SCR3_TEXT);
    
        short y = 160;
        bool anyProblems = false;
#ifdef OSW_FEATURE_WIFI
        hal->gfx()->setTextCursor(DISP_W / 2, y);
        hal->gfx()->print(LANG_TUT_SCR3_NOBATWIFI);
        anyProblems = true;
#if OSW_DEVICE_ESP32_WIFI_LOWPWR == 1
        y += 10;
        hal->gfx()->setTextCursor(DISP_W / 2, y);
        hal->gfx()->print(LANG_TUT_SCR3_WIFILOWPW);
        anyProblems = true;
#endif
#endif
#if defined(GPS_EDITION) || defined(GPS_EDITION_ROTATED)
        y += 10;
        hal->gfx()->setTextCursor(DISP_W / 2, y);
        hal->gfx()->print(LANG_TUT_SCR3_CRAPGPS);
        anyProblems = true;
#endif
        hal->gfx()->setTextCursor(DISP_W / 2, 205);
        hal->gfx()->print(LANG_TUT_ANYKEY);

        if(!anyProblems)
            ++this->screen; // skip this screen
    } else {
        // Okay, we are done! Restore the original root app.
        OswUI::getInstance()->setRootApplication(this->previousRootApp);
        nvs.putString("v", GIT_COMMIT_HASH);
    }

    // Auto-hide the tutorial after one minute - in case something gets stuck
    if(time(nullptr) - this->timeout > 60)
        OswUI::getInstance()->setRootApplication(this->previousRootApp);
}

void OswAppTutorial::onButton(int id, bool up, OswAppV2::ButtonStateNames state) {
    OswAppV2::onButton(id, up, state); // always make sure to call the base class method!
    if(!up) return;
    this->timeout = time(nullptr); // reset the timeout, as the user interacted with the device
    if(this->screen == 0) {
        ++this->screen;
        // Also enable double press detection
        for(int i = 0; i < BTN_NUMBER; i++)
            this->knownButtonStates[i] = (OswAppV2::ButtonStateNames) (this->knownButtonStates[i] | OswAppV2::ButtonStateNames::DOUBLE_PRESS | OswAppV2::ButtonStateNames::LONG_PRESS | OswAppV2::ButtonStateNames::VERY_LONG_PRESS | OswAppV2::ButtonStateNames::DOUBLE_PRESS);
    } else if(this->screen == 1) {
        if(state == OswAppV2::ButtonStateNames::SHORT_PRESS)
            this->gotButtonShort = (Button) id;
        else if(state == OswAppV2::ButtonStateNames::LONG_PRESS)
            this->gotButtonLong = (Button) id;
        else if(state == OswAppV2::ButtonStateNames::VERY_LONG_PRESS)
            this->gotButtonVeryLong = (Button) id;
        else if(state == OswAppV2::ButtonStateNames::DOUBLE_PRESS)
            this->gotButtonDouble = (Button) id;
        this->needsRedraw = true;
        if(this->gotButtonShort.has_value() and this->gotButtonLong.has_value() and this->gotButtonVeryLong.has_value() and this->gotButtonDouble.has_value()) {
            this->nextScreenOn = time(nullptr) + 5; // Wait some seconds before continuing, so user can read labels
            // Disable double press detection again (speeds up short press detection again)
            for(int i = 0; i < BTN_NUMBER; i++)
                this->knownButtonStates[i] = (OswAppV2::ButtonStateNames) (this->knownButtonStates[i] ^ OswAppV2::ButtonStateNames::DOUBLE_PRESS); // Using XOR, as we know it was enabled before
        }
    } else if(this->screen == 2) {
        ++this->screen;
    } else if(this->screen == 3) {
        ++this->screen;
    }
}

#ifdef OSW_EMULATOR
#include "imgui.h"

void OswAppTutorial::onLoopDebug() {
    ImGui::Begin("Debug: OswAppTutorial");
    ImGui::InputScalar("screen", ImGuiDataType_U8, &this->screen);
    ImGui::InputScalar("timeout", ImGuiDataType_U32, &this->timeout);
    ImGui::InputScalar("nextScreenOn", ImGuiDataType_U32, &this->nextScreenOn);
    ImGui::End();
}
#endif

void OswAppTutorial::onStop() {
    OswAppV2::onStop(); // always make sure to call the base class method!
}

bool OswAppTutorial::changeRootAppIfNecessary() {
    if(nvs.getString("v", "") != String(GIT_COMMIT_HASH)) {
        this->previousRootApp = OswUI::getInstance()->getRootApplication();
        OswUI::getInstance()->setRootApplication(this);
        return true;
    }
    return false;
}