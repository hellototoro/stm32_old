#ifndef CLOCKSCREENVIEW_HPP
#define CLOCKSCREENVIEW_HPP

#include <gui_generated/clockscreen_screen/clockScreenViewBase.hpp>
#include <gui/clockscreen_screen/clockScreenPresenter.hpp>

class clockScreenView : public clockScreenViewBase
{
public:
    clockScreenView();
    virtual ~clockScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void handleTickEvent();

protected:
    uint8_t analogSeconds;
    uint8_t analogMinutes;
    uint8_t analogHours;
    uint32_t tickCounter;
 };

#endif // CLOCKSCREENVIEW_HPP
