#ifndef __STATIC_QUEUE_H
#define __STATIC_QUEUE_H

#include "bluetooth.h"

#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#define LOOP_FRONT_COUNTER(src,max_num)     (++(src) % (max_num))
#define LOOP_REAR_COUNTER(src,max_num)      ((src)++ % (max_num))

#define QUEUE_MAX_SIZE  5

typedef struct {
    Bluetooth_data buff[QUEUE_MAX_SIZE];    // 包含元素的数组
    uint8_t front;
    uint8_t rear;
}static_queue;

extern void QueueInit(static_queue* queue);
extern uint8_t QueueEn(static_queue* queue, const Bluetooth_data* e);
extern uint8_t QueueDe(static_queue* queue, Bluetooth_data* e);
extern uint8_t QueueIsEmpty(static_queue* queue);

#endif
