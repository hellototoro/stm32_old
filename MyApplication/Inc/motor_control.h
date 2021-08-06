/**
  ******************************************************************************
  * @file    motor_control.h
  * @brief   电机控制驱动
  * @data    2021-7-28
  * @author  jee
  ******************************************************************************
  */
#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H

typedef enum {
    Id_right = 0,
    Id_left
}Motor_IdTypeDef;

typedef enum {
    Dir_front = 0,
    Dir_back,
    Dir_right,
    Dir_left
}Motor_MoveDirTypeDef;

/* 全局函数声明 */
extern void Motor_init(void);
extern void Motor_move(Motor_MoveDirTypeDef MoveDir);
extern void Motor_lock(void);
extern void Motor_start(void);

#endif
