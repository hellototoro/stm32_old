#ifndef STARTSCREENVIEW_HPP
#define STARTSCREENVIEW_HPP

#include <gui_generated/startscreen_screen/startScreenViewBase.hpp>
#include <gui/startscreen_screen/startScreenPresenter.hpp>

class startScreenView : public startScreenViewBase
{
public:
    startScreenView();
    virtual ~startScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // STARTSCREENVIEW_HPP
