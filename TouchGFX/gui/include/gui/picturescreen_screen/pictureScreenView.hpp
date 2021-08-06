#ifndef PICTURESCREENVIEW_HPP
#define PICTURESCREENVIEW_HPP

#include <gui_generated/picturescreen_screen/pictureScreenViewBase.hpp>
#include <gui/picturescreen_screen/pictureScreenPresenter.hpp>

class pictureScreenView : public pictureScreenViewBase
{
public:
    pictureScreenView();
    virtual ~pictureScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // PICTURESCREENVIEW_HPP
