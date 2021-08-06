/**
  ******************************************************************************
  * @file    car_control.c
  * @brief   С������Ӧ�ó���
  * @data    2021-7-28
  * @author  jee
  ******************************************************************************
  */
#include <Inc/car_control.h>
#include <Inc/motor_control.h>


Car_control Car;

void Car_init(void)
{
    Car.v_dir = 0;
    Car.h_dir = 0;
    Car.speed = 0;
    Motor_init();
}

uint8_t Car_isLastData(Car_control *data)
{
    if ( data->h_dir == Car.h_dir && 
         data->v_dir == Car.v_dir && 
         data->speed == Car.speed )
        return 1;
    else
        return 0;
}

void Car_monitor(void)
{
    static Car_control last_dir = {0};
    if (!Car_isLastData(&last_dir)) {
        last_dir = Car;
        if (Car.v_dir*Car.h_dir == 0)
        {
            if (Car.v_dir == 1) {
                Motor_move(Dir_front);
            } else if (Car.v_dir == -1) {
                Motor_move(Dir_back);
            } else if (Car.h_dir == 1) {
                Motor_move(Dir_right);
            } else if (Car.h_dir == -1) {
                Motor_move(Dir_left);
            } else {
                Motor_lock();
            }
        } else {
            Motor_lock();
        }
    }
}
