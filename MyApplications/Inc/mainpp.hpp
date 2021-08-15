#ifndef __MAIN_HPP
#define __MAIN_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define CT_MAX_TOUCH 1    //电容屏支持的点数,固定为5点
typedef struct  {
    uint16_t x[CT_MAX_TOUCH]; 		//当前坐标
    uint16_t y[CT_MAX_TOUCH];		//电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
}touchDataDef;

extern void setup(void);
extern void loop(void);
extern void led2_toggle(void);

    
#ifdef __cplusplus
}
#endif


#endif
