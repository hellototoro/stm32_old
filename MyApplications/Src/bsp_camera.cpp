#include "../../MyApplications/Inc/bsp_camera.hpp"


/** @defgroup STM324xG_EVAL_CAMERA_Private_Variables STM324xG EVAL CAMERA Private Variables
  * @{
  */
//static DCMI_HandleTypeDef hdcmi_eval;
extern DCMI_HandleTypeDef *DCMI_Handle;
CAMERA_DrvTypeDef  *camera_drv;
uint32_t current_resolution;


/**
  * @brief  Initializes the Camera.
  * @param  Resolution: Camera resolution
  * @retval Camera status
  */
uint8_t bsp_camera::init(uint32_t Resolution)
{
	uint8_t ret = CAMERA_ERROR;

	/* DCMI Initialization */
	//BSP_CAMERA_MspInit();
	//HAL_DCMI_Init(phdcmi);
	ov2640_IO_Init();
	if(ov2640_drv.ReadID(CAMERA_I2C_ADDRESS) == OV2640_ID)
	{
		/* Initialize the Camera driver structure */
		camera_drv = &ov2640_drv;

		/* Camera Init */
		camera_drv->Init(CAMERA_I2C_ADDRESS, Resolution);

		/* Return CAMERA_OK status */
		ret = CAMERA_OK;
	}

	current_resolution = Resolution;

  return ret;
}

/**
  * @brief  Starts the Camera capture in continuous mode.
  * @param  buff: pointer to the Camera output buffer
  */
void bsp_camera::continuousStart(uint8_t *buff)
{
  /* Start the Camera capture */
  HAL_DCMI_Start_DMA(DCMI_Handle, DCMI_MODE_CONTINUOUS, (uint32_t)buff, getSize(current_resolution));
}

/**
  * @brief  Starts the Camera capture in snapshot mode.
  * @param  buff: pointer to the Camera output buffer
  */
void bsp_camera::snapshotStart(uint8_t *buff)
{
  /* Start the Camera capture */
  HAL_DCMI_Start_DMA(DCMI_Handle, DCMI_MODE_SNAPSHOT, (uint32_t)buff, getSize(current_resolution));
}

/**
  * @brief  Suspends the Camera capture.
  */
void bsp_camera::suspend(void)
{
  /* Suspend the Camera Capture */
  HAL_DCMI_Suspend(DCMI_Handle);
}

/**
  * @brief  Resumes the Camera capture.
  */
void bsp_camera::resume(void)
{
  /* Start the Camera Capture */
  HAL_DCMI_Resume(DCMI_Handle);
}

/**
  * @brief  Stops the Camera capture.
  * @retval Camera status
  */
uint8_t bsp_camera::stop(void)
{
  DCMI_HandleTypeDef *phdcmi;

  uint8_t ret = CAMERA_ERROR;

  /* Get the DCMI handle structure */
  phdcmi = DCMI_Handle;

  if(HAL_DCMI_Stop(phdcmi) == HAL_OK)
  {
     ret = CAMERA_OK;
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
void bsp_camera::contrastBrightnessConfig(uint32_t contrast_level, uint32_t brightness_level)
{
  if(camera_drv->Config != NULL)
  {
    camera_drv->Config(CAMERA_I2C_ADDRESS, CAMERA_CONTRAST_BRIGHTNESS, contrast_level, brightness_level);
  }
}

/**
  * @brief  Configures the Camera white balance.
  * @param  Mode: black_white mode
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_BLACK_WHITE_BW
  *            @arg  CAMERA_BLACK_WHITE_NEGATIVE
  *            @arg  CAMERA_BLACK_WHITE_BW_NEGATIVE
  *            @arg  CAMERA_BLACK_WHITE_NORMAL
  */
void bsp_camera::blackWhiteConfig(uint32_t Mode)
{
  if(camera_drv->Config != NULL)
  {
    camera_drv->Config(CAMERA_I2C_ADDRESS, CAMERA_BLACK_WHITE, Mode, 0);
  }
}

/**
  * @brief  Configures the Camera color effect.
  * @param  Effect: Color effect
  *          This parameter can be one of the following values:
  *            @arg  CAMERA_COLOR_EFFECT_ANTIQUE
  *            @arg  CAMERA_COLOR_EFFECT_BLUE
  *            @arg  CAMERA_COLOR_EFFECT_GREEN
  *            @arg  CAMERA_COLOR_EFFECT_RED
  */
void bsp_camera::colorEffectConfig(uint32_t Effect)
{
  if(camera_drv->Config != NULL)
  {
    camera_drv->Config(CAMERA_I2C_ADDRESS, CAMERA_COLOR_EFFECT, Effect, 0);
  }
}

/**
  * @brief  Get the capture size.
  * @param  resolution: the current resolution.
  * @retval cpature size
  */
uint32_t bsp_camera::getSize(uint32_t resolution)
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

/**
  * @brief  Initializes the DCMI MSP.
  */
void bsp_camera::MspInit(void)
{
  static DMA_HandleTypeDef hdma;
  GPIO_InitTypeDef GPIO_Init_Structure;
  DCMI_HandleTypeDef *hdcmi = DCMI_Handle;

  /*** Enable peripherals and GPIO clocks ***/
  /* Enable DCMI clock */
  __HAL_RCC_DCMI_CLK_ENABLE();

  /* Enable DMA2 clock */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* Enable GPIO clocks */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

  /*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */
    GPIO_Init_Structure.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
    GPIO_Init_Structure.Pull = GPIO_NOPULL;
    GPIO_Init_Structure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_Init_Structure.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);

    GPIO_Init_Structure.Pin = GPIO_PIN_4|GPIO_PIN_6;
    GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
    GPIO_Init_Structure.Pull = GPIO_NOPULL;
    GPIO_Init_Structure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_Init_Structure.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOA, &GPIO_Init_Structure);

    GPIO_Init_Structure.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_11;
    GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
    GPIO_Init_Structure.Pull = GPIO_NOPULL;
    GPIO_Init_Structure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_Init_Structure.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOC, &GPIO_Init_Structure);

    GPIO_Init_Structure.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
    GPIO_Init_Structure.Pull = GPIO_NOPULL;
    GPIO_Init_Structure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_Init_Structure.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOB, &GPIO_Init_Structure);

  /*** Configure the DMA streams ***/
  /* Configure the DMA handler for Transmission process */
  hdma.Init.Channel             = DMA_CHANNEL_1;
  hdma.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma.Init.MemInc              = DMA_MINC_ENABLE;
  hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  hdma.Init.Mode                = DMA_CIRCULAR;
  hdma.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  hdma.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma.Init.MemBurst            = DMA_MBURST_SINGLE;
  hdma.Init.PeriphBurst         = DMA_PBURST_SINGLE;

  hdma.Instance = DMA2_Stream1;

  /* Associate the initialized DMA handle to the DCMI handle */
  __HAL_LINKDMA(hdcmi, DMA_Handle, hdma);

  /*** Configure the NVIC for DCMI and DMA ***/
  /* NVIC configuration for DCMI transfer complete interrupt */
  HAL_NVIC_SetPriority(DCMI_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DCMI_IRQn);

  /* NVIC configuration for DMA2 transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

  /* Configure the DMA stream */
  HAL_DMA_Init(hdcmi->DMA_Handle);
}
