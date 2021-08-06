#ifndef __CAMERA_HPP
#define __CAMERA_HPP


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ov2640/Inc/ov2640.h"

/**
  * @brief Camera status structure definition
  */
typedef enum
{
  CAMERA_OK       = 0x00,
  CAMERA_ERROR    = 0x01,
  CAMERA_TIMEOUT  = 0x02
}Camera_StatusTypeDef;

class bsp_camera {
public:
	uint8_t init(uint32_t Resolution);
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
	uint32_t getSize(uint32_t resolution);
};


#define RESOLUTION_R160x120      CAMERA_R160x120  /* QQVGA Resolution */
#define RESOLUTION_R320x240      CAMERA_R320x240  /* QVGA Resolution */
#define CAMERA_I2C_ADDRESS 		 0x60


#endif
