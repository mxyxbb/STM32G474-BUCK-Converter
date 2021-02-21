#include "Src/MyButton.h"

struct Button btn1;
void BTN1_SINGLE_Click_Handler(void* btn);
void BTN1_DOUBLE_Click_Handler(void* btn);

uint8_t read_button1_GPIO()
{
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}

void MyButtonInit()
{
	button_init(&btn1, read_button1_GPIO, 1);	
	button_attach(&btn1, SINGLE_CLICK, BTN1_SINGLE_Click_Handler);
	button_attach(&btn1, DOUBLE_CLICK, BTN1_DOUBLE_Click_Handler);
	button_start(&btn1);

}

void BTN1_SINGLE_Click_Handler(void* btn)//按一次PWM输出加0.33V
{
	static int32_t dt=0;
	dt+=5440;
	constrain(dt,0,54400-1);
	hhrtim1.Instance->sTimerxRegs[0].CMP1xR = dt;
}

void BTN1_DOUBLE_Click_Handler(void* btn)//按一次PWM输出减0.33V
{
	static int32_t dt=0;
	dt-=5440;
	constrain(dt,0,54400-1);
	hhrtim1.Instance->sTimerxRegs[0].CMP1xR = dt;
}
