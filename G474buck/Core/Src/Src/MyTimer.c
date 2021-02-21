#include "Src/MyTimer.h"


struct Timer timer1;
struct Timer timer2;

void timer1_callback()
{
	button_ticks();
//    printf("timer1 timeout!\r\n");
}

void timer2_callback()
{
//    printf("timer2 timeout!\r\n");
}

void MyTimerInit()
{
	timer_init(&timer1, timer1_callback, 5, 200*60*60*1); //5ms loop
	timer_start(&timer1);
}

void HAL_SYSTICK_Callback(void)
{
    timer_ticks(); //1ms ticks
}
