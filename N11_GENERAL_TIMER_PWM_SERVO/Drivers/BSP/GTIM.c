#include "./BSP/GTIM.h"

TIM_HandleTypeDef g_timx_pwm_chy_handle;

/**
 *@brief     ͨ�ö�ʱ��PWM�����ʼ������
 *@note      ��
 *@param     arr:�Զ���װֵ
 *@param     psc:ʱ��Ԥ��Ƶ��
 *@retval    �� 
 */
void g_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
	TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};
	
	g_timx_pwm_chy_handle.Instance = TIM3;
	g_timx_pwm_chy_handle.Init.Prescaler = psc;                      /*Ԥ��Ƶϵ��*/
	g_timx_pwm_chy_handle.Init.Period = arr;                         /*�Զ�װ��ֵ*/
	g_timx_pwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;     /*��������ģʽ*/
	HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);                        /* ��ʼ��PWM */
	
	timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                        /* ģʽѡ��PWM1 */
	timx_oc_pwm_chy.Pulse = arr/2;                                   /* ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ� */
	timx_oc_pwm_chy.OCNPolarity = TIM_OCPOLARITY_HIGH;
	HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle,&timx_oc_pwm_chy,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle,TIM_CHANNEL_2);
}

/*��ʱ�����PWM MSP��ʼ������,��ʼGPIO��*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		GPIO_InitTypeDef gpio_init_struct;
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_TIM3_CLK_ENABLE();
		
		gpio_init_struct.Pin = GPIO_PIN_5;
		gpio_init_struct.Mode = GPIO_MODE_AF_PP;
		gpio_init_struct.Pull = GPIO_PULLUP;
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB,&gpio_init_struct);
		
		/*�ض��幦�ܲ���Ҫд�����Ĭ�ϸ��ù��ܲ���*/
		__HAL_RCC_AFIO_CLK_ENABLE();
		__HAL_AFIO_REMAP_TIM3_PARTIAL();
	}
}