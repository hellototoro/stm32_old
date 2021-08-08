/*
 * display.hpp
 *
 *  Created on: Aug 6, 2021
 *      Author: huang
 */

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

namespace MyApplications {

#include "main.h"

class display {
public:
    class display_info {
    public:
        uint16_t id;
        char type[20];
        class resolution {
        public:
            uint16_t weight;
            uint16_t height;
        };
    };

public:
    display();
    virtual void showChar(uint16_t x,uint16_t y,char ch) = 0;
    virtual void showString(uint16_t x,uint16_t y,char* str) = 0;
    virtual void showPicture(uint16_t x,uint16_t y,char* pic) = 0;
    virtual void displayOn(void) = 0;
    virtual void displayOff(void) = 0;
    virtual display_info getInfo(void) = 0;
    virtual ~display();
};

} /* namespace MyApplications */

#endif /* DISPLAY_HPP_ */
