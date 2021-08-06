/**
  ******************************************************************************
  * @file    motor_control.c
  * @brief   �����������
  * @data    2021-7-28
  * @author  jee
  ******************************************************************************
  */
#include <Inc/motor_control.h>
#include "main.h"


/* �궨�� */
#define MOTOR_PORT(dir,type)    dir##_motor_##type##_GPIO_Port  //left_front_motor_A_GPIO_Port
#define MOTOR_PIN(dir,type)     dir##_motor_##type##_Pin  //left_front_motor_A_Pin

#define PWM_HANDLE(dir)         dir##_motor_pwm
#define STR1(R)  #R
#define STR2(R)  STR1(R)  
#define PWM_Start(dir) \
  (((&(PWM_HANDLE(dir))) == &(PWM_HANDLE(left_front))) ? (HAL_TIM_PWM_Start(PWM_HANDLE(dir), TIM_CHANNEL_1)) :\
  (((&(PWM_HANDLE(dir))) == &(PWM_HANDLE(right_front))) ? (HAL_TIM_PWM_Start(PWM_HANDLE(dir), TIM_CHANNEL_2)) :\
  (((&(PWM_HANDLE(dir))) == &(PWM_HANDLE(left_back))) ? (HAL_TIM_PWM_Start(PWM_HANDLE(dir), TIM_CHANNEL_1)) :\
   (HAL_TIM_PWM_Start(PWM_HANDLE(dir), TIM_CHANNEL_2)))))

#define SET_DutyCycle(dir,d) \
  (((&(PWM_HANDLE(dir))) == &(PWM_HANDLE(left_front))) ? (Configure_DutyCycle(PWM_HANDLE(dir), TIM_CHANNEL_1, d)) :\
  (((&(PWM_HANDLE(dir))) == &(PWM_HANDLE(right_front))) ? (Configure_DutyCycle(PWM_HANDLE(dir), TIM_CHANNEL_2, d)) :\
  (((&(PWM_HANDLE(dir))) == &(PWM_HANDLE(left_back))) ? (Configure_DutyCycle(PWM_HANDLE(dir), TIM_CHANNEL_1, d)) :\
   (Configure_DutyCycle(PWM_HANDLE(dir), TIM_CHANNEL_2, d)))))

static uint8_t pwmStart_flag = 0;

void Motor_moveFront(void);
void Motor_moveRight(void);
void Motor_moveBack(void);
void Motor_moveLeft(void);
void Motor_moveStop(void);


/**
  * @brief  Changes the duty cycle of the PWM signal.
  *         D = (T/P)*100
  *           where T is the pulse duration and P is the PWM signal period
  * @param  D Duty cycle
  *         Id ���id�������ҵ��
  * @retval None
  */
static void Configure_DutyCycle(PWM_HandleTypeDef*PWM_Handle, uint32_t Channel, uint32_t D)
{
    uint32_t P;    /* Pulse duration */
    uint32_t T;    /* PWM signal period */

    /* PWM signal period is determined by the value of the auto-reload register */
    T = __HAL_TIM_GET_AUTORELOAD(PWM_Handle) + 1;

    /* Pulse duration is determined by the value of the compare register.       */
    /* Its value is calculated in order to match the requested duty cycle.      */
    P = (D*T)/100;
    __HAL_TIM_SET_COMPARE(PWM_Handle, Channel, P);
}

void Motor_init(void)
{
    Motor_start();
    SET_DutyCycle(left_front,70);
    SET_DutyCycle(right_front,70);
    SET_DutyCycle(left_back,70);
    SET_DutyCycle(right_back,70);
    //Motor_moveFront();
//    Motor_moveRight();
//    Motor_moveBack();
//    Motor_moveLeft();
//    Motor_lock();
//    HAL_Delay(1000);
//    Motor_moveStop();
}

void Motor_start(void)
{
    PWM_Start(left_front);
    PWM_Start(right_front);
    PWM_Start(left_back);
    PWM_Start(right_back);
//    setIO_PWMOut();
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
//    pwmStart_flag = 1;
}

void Motor_moveFront(void)
{
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,A), MOTOR_PIN(left_front,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,B), MOTOR_PIN(left_front,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,A), MOTOR_PIN(right_front,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,B), MOTOR_PIN(right_front,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,A), MOTOR_PIN(left_back,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,B), MOTOR_PIN(left_back,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,A), MOTOR_PIN(right_back,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,B), MOTOR_PIN(right_back,B), GPIO_PIN_RESET);
}

void Motor_moveRight(void)
{
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,A), MOTOR_PIN(left_front,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,B), MOTOR_PIN(left_front,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,A), MOTOR_PIN(right_front,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,B), MOTOR_PIN(right_front,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,A), MOTOR_PIN(left_back,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,B), MOTOR_PIN(left_back,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,A), MOTOR_PIN(right_back,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,B), MOTOR_PIN(right_back,B), GPIO_PIN_SET);
}

void Motor_moveBack(void)
{
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,A), MOTOR_PIN(left_front,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,B), MOTOR_PIN(left_front,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,A), MOTOR_PIN(right_front,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,B), MOTOR_PIN(right_front,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,A), MOTOR_PIN(left_back,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,B), MOTOR_PIN(left_back,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,A), MOTOR_PIN(right_back,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,B), MOTOR_PIN(right_back,B), GPIO_PIN_SET);
}

void Motor_moveLeft(void)
{
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,A), MOTOR_PIN(left_front,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,B), MOTOR_PIN(left_front,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,A), MOTOR_PIN(right_front,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,B), MOTOR_PIN(right_front,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,A), MOTOR_PIN(left_back,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,B), MOTOR_PIN(left_back,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,A), MOTOR_PIN(right_back,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,B), MOTOR_PIN(right_back,B), GPIO_PIN_RESET);
}

void Motor_moveStop(void)
{
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,A), MOTOR_PIN(left_front,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,B), MOTOR_PIN(left_front,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,A), MOTOR_PIN(right_front,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,B), MOTOR_PIN(right_front,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,A), MOTOR_PIN(left_back,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,B), MOTOR_PIN(left_back,B), GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,A), MOTOR_PIN(right_back,A), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,B), MOTOR_PIN(right_back,B), GPIO_PIN_RESET);
}

void Motor_move(Motor_MoveDirTypeDef MoveDir)
{
    if (!pwmStart_flag) {
        Motor_start();
    }
    switch ((uint8_t)MoveDir)
    {
        case Dir_front:
        {
            Motor_moveFront();
            break;
        }
        case Dir_back:
        {
            Motor_moveBack();
            break;
        }
        case Dir_right:
        {
            Motor_moveRight();
            break;
        }
        case Dir_left:
        {
            Motor_moveLeft();
            break;
        }
        default :
            break;
    }
}

void Motor_lock(void)
{
//    SET_DutyCycle(left_front,100);
//    SET_DutyCycle(right_front,100);
//    SET_DutyCycle(left_back,100);
//    SET_DutyCycle(right_back,100);
    
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,A), MOTOR_PIN(left_front,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_front,B), MOTOR_PIN(left_front,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,A), MOTOR_PIN(right_front,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_front,B), MOTOR_PIN(right_front,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,A), MOTOR_PIN(left_back,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(left_back,B), MOTOR_PIN(left_back,B), GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,A), MOTOR_PIN(right_back,A), GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT(right_back,B), MOTOR_PIN(right_back,B), GPIO_PIN_SET);
//    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
//    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
//    pwmStart_flag = 0;
//    
//    setIO_generalOut();
//    HAL_GPIO_WritePin(RightMotor_PWM_GPIO_Port, RightMotor_PWM_Pin, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LeftMotor_PWM_GPIO_Port, LeftMotor_PWM_Pin, GPIO_PIN_RESET);
//    Motor_moveStop();
}

void Motor_Stop(void)
{
    Motor_moveStop();
//    Motor_lock();
//    HAL_GPIO_WritePin(RightMotor_PWM_GPIO_Port, RightMotor_PWM_Pin, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LeftMotor_PWM_GPIO_Port, LeftMotor_PWM_Pin, GPIO_PIN_RESET);
//    
//    HAL_GPIO_WritePin(RightMotor_COM_GPIO_Port, RightMotor_COM_Pin, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LeftMotor_COM_GPIO_Port, LeftMotor_COM_Pin, GPIO_PIN_RESET);
}
