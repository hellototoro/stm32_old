#ifndef INFOSCREENPRESENTER_HPP
#define INFOSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class infoScreenView;

class infoScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    infoScreenPresenter(infoScreenView& v);

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

    virtual ~infoScreenPresenter() {};

private:
    infoScreenPresenter();

    infoScreenView& view;
};

#endif // INFOSCREENPRESENTER_HPP
