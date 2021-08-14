#include <gui/clockscreen_screen/clockScreenView.hpp>

clockScreenView::clockScreenView()
{

}

void clockScreenView::setupScreen()
{
    clockScreenViewBase::setupScreen();
}

void clockScreenView::tearDownScreen()
{
    clockScreenViewBase::tearDownScreen();
}

void clockScreenView::handleTickEvent()
{
   tickCounter++;

    if (tickCounter % 60 == 0)
    {
        if (++analogSeconds >= 60)
        {
            analogSeconds = 0;
            if (++analogMinutes >= 60)
            {
                analogMinutes = 0;
                if (++analogHours >= 24)
                {
                    analogHours = 0;
                }
            }
        }

        // Update the clocks
        clock.setTime24Hour(analogHours, analogMinutes, analogSeconds);
    }
}