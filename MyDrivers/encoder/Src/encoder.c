#include "encoder/Inc/encoder.h"
//#include "motor_control.h"


encoder_info left_front_encoder;
encoder_info right_front_encoder;
encoder_info left_back_encoder;
encoder_info right_back_encoder;




void getEncoderInfo(Encoder_HandleTypeDef *Encoder_Handle,encoder_info *encoder)
{
    encoder->direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(Encoder_Handle);
    encoder->counter = __HAL_TIM_GET_COUNTER(Encoder_Handle);
}

