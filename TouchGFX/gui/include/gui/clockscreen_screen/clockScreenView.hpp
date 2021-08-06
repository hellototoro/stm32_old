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
protected:
};

#endif // CLOCKSCREENVIEW_HPP
