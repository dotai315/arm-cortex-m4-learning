#include "stm32f4xx.h"

#define PLL_P	2
#define PLL_M	4
#define PLL_N	100

static void SystemClock_Config(void);
static void GPIO_Config(void);
static void Toggle_Led(void);
static void DelayMS(uint32_t period);

int main(void)
{
	SystemClock_Config();
	GPIO_Config();
	while (1) {
 		Toggle_Led();	
		DelayMS(2000);
    	}
   	return 0;
}

static void SystemClock_Config(void)
{
	/* Turn on Clock Source */
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	/* Setting Power and Flash */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS_0 | PWR_CR_VOS_1;

	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_3WS;
	
	/* PLL Config and setting source clock for PLL */
	RCC->PLLCFGR |= (PLL_N << RCC_PLLCFGR_PLLN_Pos) | (PLL_M << RCC_PLLCFGR_PLLM_Pos) | (PLL_P << RCC_PLLCFGR_PLLP_Pos);
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;

	/* Config AHB, APB1 and APB2 */
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1;

	/* Turn on PLL */
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));

	/* Config System Clock  */
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
}

static void GPIO_Config(void)
{
	/* GPIOA Clock Enable */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	/* Config GPIOA Pin 5 as ouput */
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
}

static void Toggle_Led(void)
{
	uint32_t odr = GPIOA->ODR;
	GPIOA->BSRR |= ((odr & (1 << 5)) << 16u) | (~odr & (1 << 5));
}

static void DelayMS(uint32_t period)
{
	uint32_t time = 1000 * period;
	while(time--);
}
