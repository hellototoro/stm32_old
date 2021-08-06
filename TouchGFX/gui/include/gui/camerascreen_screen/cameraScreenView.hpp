#ifndef CAMERASCREENVIEW_HPP
#define CAMERASCREENVIEW_HPP

#include <gui_generated/camerascreen_screen/cameraScreenViewBase.hpp>
#include <gui/camerascreen_screen/cameraScreenPresenter.hpp>

class cameraScreenView : public cameraScreenViewBase
{
public:
    cameraScreenView();
    virtual ~cameraScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CAMERASCREENVIEW_HPP
