#include  "SR05.h"

uint32_t IC_Val1=0;
uint32_t IC_Val2=0;
uint32_t Difference=0;
uint8_t Is_First_Captured=0;
uint8_t Distance=0;
extern TIM_HandleTypeDef htim1;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  
	{
		
		input_capture();
	}
}


void delay(uint16_t time){
__HAL_TIM_SetCounter(&htim1,0);
	while(__HAL_TIM_GetCounter (&htim1)<time);

}

//HCSR05_Read
uint8_t SR05_Read (void){

HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10); 
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low

	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
	
	return Distance;
}

//SR05_Read
void input_capture(void)
	{
		if (Is_First_Captured==0) 
		{
			IC_Val1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1); 
			Is_First_Captured = 1;  
		
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (Is_First_Captured==1)   
		{
			IC_Val2 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);  
			__HAL_TIM_SET_COUNTER(&htim1, 0);  

			if (IC_Val2 > IC_Val1)
			{
				Difference = IC_Val2-IC_Val1;
			}
			else if (IC_Val1 > IC_Val2)
			{
				Difference = (0xffff - IC_Val1) + IC_Val2;
			}

			Distance = Difference * .034/2;
			Is_First_Captured = 0; 

			
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
			}
}

uint8_t srf05_data(void)
{
	uint8_t value=0;
	value=Distance;
	return value;
}

