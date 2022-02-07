#include "stm32f411xe.h"

#define PLL_M 	4
#define PLL_N 	84
#define PLL_P 	2

static void RCC_Config(void);
static void GPIO_Config (void);
static void Delay (uint32_t period);

int main(void)
{
    RCC_Config();
    GPIO_Config();
    while(1)
    {
        GPIOA->BSRR |= GPIO_BSRR_BS5;
        Delay (1000000);
        GPIOA->BSRR |= GPIO_BSRR_BR5; 
        Delay (1000000);
    }
    return 0;
}

static void RCC_Config(void)
{
    RCC->CR |= RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY));

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS_1;

    FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_2WS;

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

    RCC->PLLCFGR = (PLL_M << RCC_PLLCFGR_PLLM_Pos) | (PLL_N << RCC_PLLCFGR_PLLN_Pos) | (PLL_P << RCC_PLLCFGR_PLLP_Pos) | (RCC_PLLCFGR_PLLSRC_HSE);

    RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

static void GPIO_Config (void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD5_0;
}

static void Delay (uint32_t period)
{
    while(period--);
}
