#ifndef PICTURESCREENPRESENTER_HPP
#define PICTURESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class pictureScreenView;

class pictureScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    pictureScreenPresenter(pictureScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~pictureScreenPresenter() {};

private:
    pictureScreenPresenter();

    pictureScreenView& view;
};

#endif // PICTURESCREENPRESENTER_HPP
