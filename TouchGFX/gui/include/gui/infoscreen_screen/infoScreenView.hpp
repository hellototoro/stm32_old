#ifndef INFOSCREENVIEW_HPP
#define INFOSCREENVIEW_HPP

#include <gui_generated/infoscreen_screen/infoScreenViewBase.hpp>
#include <gui/infoscreen_screen/infoScreenPresenter.hpp>

class infoScreenView : public infoScreenViewBase
{
public:
    infoScreenView();
    virtual ~infoScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // INFOSCREENVIEW_HPP
