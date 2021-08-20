/*
 * camera.hpp
 *
 *  Created on: 2021年8月20日
 *      Author: huang
 */

#ifndef CAMERA_CAMERA_HPP_
#define CAMERA_CAMERA_HPP_

#include "main.h"
#include "Components/ov2640/ov2640.hpp"

namespace MyDrivers {

enum class Camera_Status {
  CAMERA_OK       = 0x00,
  CAMERA_ERROR    = 0x01,
  CAMERA_TIMEOUT  = 0x02
};

class camera : public ov2640 {
public:
    camera(I2C_HandleTypeDef *_touchPad_IIC_Handle, uint32_t Resolution);
    virtual ~camera();
    uint8_t init(void);
    void setOutputSize(uint16_t width,uint16_t height);
    void    continuousStart(uint8_t *buff);
    void    snapshotStart(uint8_t *buff);
    void    suspend(void);
    void    resume(void);
    uint8_t stop(void);
    void    MspInit(void);

    /* Camera features functions prototype */
    void    contrastBrightnessConfig(uint32_t contrast_level, uint32_t brightness_level);
    void    blackWhiteConfig(uint32_t Mode);
    void    colorEffectConfig(uint32_t Effect);
private:
    uint32_t current_resolution;

    uint32_t getSize(uint32_t resolution);
};

} /* namespace MyDrivers */

#endif /* CAMERA_CAMERA_HPP_ */
