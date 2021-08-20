/*
 * camera.cpp
 *
 *  Created on: 2021年8月20日
 *      Author: huang
 */

#include <camera/camera.hpp>

namespace MyDrivers {

camera::camera(I2C_HandleTypeDef *_touchPad_IIC_Handle, uint32_t Resolution) : 
ov2640(_touchPad_IIC_Handle),
current_resolution { Resolution } {
    // TODO Auto-generated constructor stub

}

uint8_t camera::init(void)
{
    uint8_t ret = static_cast<uint8_t>(Camera_Status::CAMERA_ERROR);

    /* DCMI Initialization */
    //BSP_CAMERA_MspInit();
    //HAL_DCMI_Init(phdcmi);
    resetChip();
    if(readID() == OV2640_ID)
    {        
        /* Camera Init */   
    	ov2640::init(current_resolution);
        
        /* Return CAMERA_OK status */
        ret = static_cast<uint8_t>(Camera_Status::CAMERA_OK);
    }
    return ret;
}

void camera::setOutputSize(uint16_t width,uint16_t height)
{
    set_output_size(width,height);
}

/**
  * @brief  Starts the Camera capture in continuous mode.
  * @param  buff: pointer to the Camera output buffer
  */
void camera::continuousStart(uint8_t *buff)
{
  /* Start the Camera capture */
  HAL_DCMI_Start_DMA(DCMI_Handle, DCMI_MODE_CONTINUOUS, (uint32_t)buff, getSize(current_resolution));
}

/**
  * @brief  Starts the Camera capture in snapshot mode.
  * @param  buff: pointer to the Camera output buffer
  */
void camera::snapshotStart(uint8_t *buff)
{
  /* Start the Camera capture */
  HAL_DCMI_Start_DMA(DCMI_Handle, DCMI_MODE_SNAPSHOT, (uint32_t)buff, getSize(current_resolution));
}

/**
  * @brief  Suspends the Camera capture.
  */
void camera::suspend(void)
{
  /* Suspend the Camera Capture */
  HAL_DCMI_Suspend(DCMI_Handle);
}

/**
  * @brief  Resumes the Camera capture.
  */
void camera::resume(void)
{
  /* Start the Camera Capture */
  HAL_DCMI_Resume(DCMI_Handle);
}

/**
  * @brief  Stops the Camera capture.
  * @retval Camera status
  */
uint8_t camera::stop(void)
{
  DCMI_HandleTypeDef *phdcmi;

  uint8_t ret = static_cast<uint8_t>(Camera_Status::CAMERA_ERROR);

  /* Get the DCMI handle structure */
  phdcmi = DCMI_Handle;

  if(HAL_DCMI_Stop(phdcmi) == HAL_OK)
  {
     ret = static_cast<uint8_t>(Camera_Status::CAMERA_OK);
  }

  return ret;
}

/**
  * @brief  Configures the Camera contrast and brightness.
  * @param  contrast_level: Contrast level
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_CONTRAST_LEVEL4: for contrast +2
  *            @arg  CAMERA_CONTRAST_LEVEL3: for contrast +1
  *            @arg  CAMERA_CONTRAST_LEVEL2: for contrast  0
  *            @arg  CAMERA_CONTRAST_LEVEL1: for contrast -1
  *            @arg  CAMERA_CONTRAST_LEVEL0: for contrast -2
  * @param  brightness_level: Brightness level
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_BRIGHTNESS_LEVEL4: for brightness +2
  *            @arg  CAMERA_BRIGHTNESS_LEVEL3: for brightness +1
  *            @arg  CAMERA_BRIGHTNESS_LEVEL2: for brightness  0
  *            @arg  CAMERA_BRIGHTNESS_LEVEL1: for brightness -1
  *            @arg  CAMERA_BRIGHTNESS_LEVEL0: for brightness -2
  */
/*void camera::contrastBrightnessConfig(uint32_t contrast_level, uint32_t brightness_level)
{
  if(camera_drv->Config != NULL)
  {
    camera_drv->Config(CAMERA_I2C_ADDRESS, CAMERA_CONTRAST_BRIGHTNESS, contrast_level, brightness_level);
  }
}*/

/**
  * @brief  Configures the Camera white balance.
  * @param  Mode: black_white mode
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_BLACK_WHITE_BW
  *            @arg  CAMERA_BLACK_WHITE_NEGATIVE
  *            @arg  CAMERA_BLACK_WHITE_BW_NEGATIVE
  *            @arg  CAMERA_BLACK_WHITE_NORMAL
  */
/*void camera::blackWhiteConfig(uint32_t Mode)
{
  if(camera_drv->Config != NULL)
  {
    camera_drv->Config(CAMERA_I2C_ADDRESS, CAMERA_BLACK_WHITE, Mode, 0);
  }
}*/

/**
  * @brief  Configures the Camera color effect.
  * @param  Effect: Color effect
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_COLOR_EFFECT_ANTIQUE
  *            @arg  CAMERA_COLOR_EFFECT_BLUE
  *            @arg  CAMERA_COLOR_EFFECT_GREEN
  *            @arg  CAMERA_COLOR_EFFECT_RED
  */
/*void camera::colorEffectConfig(uint32_t Effect)
{
  if(camera_drv->Config != NULL)
  {
    camera_drv->Config(CAMERA_I2C_ADDRESS, CAMERA_COLOR_EFFECT, Effect, 0);
  }
}*/

/**
  * @brief  Get the capture size.
  * @param  resolution: the current resolution.
  * @retval cpature size
  */
uint32_t camera::getSize(uint32_t resolution)
{
  uint32_t size = 0;

  /* Get capture size */
  switch (resolution)
  {
  case CAMERA_R160x120:
    {
      size =  0x2580;
    }
    break;
  case CAMERA_R320x240:
    {
      size =  0x9600;
    }
    break;
  case CAMERA_R400x240:
    {
      size =  0xBB80;
    }
    break;
  default:
    {
      break;
    }
  }

  return size;
}

camera::~camera() {
    // TODO Auto-generated destructor stub
}

} /* namespace MyDrivers */
