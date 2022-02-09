#include <stdint.h>

#define PLL_P	2
#define PLL_M	4
#define PLL_N	100

#define PERIPH_BASE		((uint32_t)0x40000000)

/* RCC Register */
#define RCC_BASE 		(PERIPH_BASE + 0x00023800)

/* RCC CR */
#define RCC_CR			(*(volatile uint32_t*)(RCC_BASE + 0x00000000))
#define RCC_CR_HSEON		(1 << 16)
#define RCC_CR_HSERDY		(1 << 17)
#define RCC_CR_PLLON		(1 << 24)
#define RCC_CR_PLLRDY		(1 << 25)

/* RCC APB1ENR */
#define RCC_APB1ENR		(*(volatile uint32_t*)(RCC_BASE + 0x00000040))
#define RCC_APB1ENR_PWREN	(1 << 28)

/* RCC AHB1ENR */
#define RCC_AHB1ENR		(*(volatile uint32_t*)(RCC_BASE + 0x00000030))
#define RCC_AHB1ENR_GPIOAEN	(1 << 0)

/* RCC PLLCFGR */
#define RCC_PLLCFGR		(*(volatile uint32_t*)(RCC_BASE + 0x000000040))
#define RCC_PLLCFGR_PLLP	16
#define RCC_PLLCFGR_PLLN	6
#define RCC_PLLCFGR_PLLM	0
#define RCC_PLLCFGR_PLLSRC_HSE  (1 << 22)

/* RCC CFGR */
#define RCC_CFGR		(*(volatile uint32_t*)(RCC_BASE + 0x00000008))
#define RCC_CFGR_PPRE2		13
#define RCC_CFGR_PPRE1		10
#define RCC_CFGR_HPRE		4
#define RCC_CFGR_SWS		2
#define RCC_CFGR_SW		0
#define RCC_CFGR_HPRE_DIV1 	(0 << RCC_CFGR_HPRE)	
#define RCC_CFGR_PPRE1_DIV2 	(4 << RCC_CFGR_PPRE1)
#define RCC_CFGR_PPRE2_DIV1	(0 << RCC_CFGR_PPRE2)
#define RCC_CFGR_SW_PLL		(2 << RCC_CFGR_SW)
#define RCC_CFGR_SWS_PLL	(2 << RCC_CFGR_SWS)
/* PWR Register */
#define PWR_BASE		(PERIPH_BASE + 0x00007000)

/* PWR CR */
#define PWR_CR			(*(volatile uint32_t*)(PWR_BASE + 0x00000000))
#define PWR_CR_VOS_0		(1 << 14)
#define PWR_CR_VOS_1		(1 << 15)

/* Flash Register */
#define FLASH_BASE		(PERIPH_BASE + 0x00023C00)

/* Flash ACR */
#define FLASH_ACR		(*(volatile uint32_t*)(FLASH_BASE + 0x00000000))
#define FLASH_ACR_LATENCY_0	(1 << 0)
#define FLASH_ACR_LATENCY_1	(1 << 1)
#define FLASH_ACR_LATENCY_2	(1 << 2)
#define FLASH_ACR_LATENCY_3	(1 << 3)
#define FLASH_ACR_LATENCY_3WS	(FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0)
#define FLASH_ACR_DCEN		(1 << 10)
#define FLASH_ACR_ICEN		(1 << 9)
#define FLASH_ACR_PRFTEN	(1 << 8)

/* GPIOA Register */
#define GPIOA_BASE		(PERIPH_BASE + 0x00020000)
#define GPIOA_MODER		(*(volatile uint32_t*)(GPIOA_BASE + 0x00000000))
#define GPIO_MODER_MODER5_0	(1 << 10)
#define GPIOA_ODR		(*(volatile uint32_t*)(GPIOA_BASE + 0x00000014))
#define GPIOA_BSRR		(*(volatile uint32_t*)(GPIOA_BASE + 0x00000018))

static void SystemClock_Config(void);
static void GPIO_Config(void);
static void Toggle_Led(void);
static void DelayMS(uint32_t period);

void Reset_Handler(void);
void _init_data(void);
void Default_Handler(void);
int main(void);
typedef void (* const intfunc)(void);

extern unsigned long _estack;
extern unsigned long _etext, _sdata, _edata, _sbss, _ebss;


__attribute__ ((section(".isr_vector"))) void (* const vector_table[])(void) = 
{
	(intfunc)((unsigned long)&_estack),
	Reset_Handler,                      /* 0x004 Reset         */
	Default_Handler,                    /* 0x008 NMI           */
	Default_Handler,                    /* 0x00C HardFaullt    */
	Default_Handler,                    /* 0x010 MemManage     */
	Default_Handler,                    /* 0x014 BusFault      */
	Default_Handler,                    /* 0x018 UsageFault    */
	0,                                  /* 0x01C Reserved      */
	0,                                  /* 0x020 Reserved      */
	0,                                  /* 0x024 Reserved      */
	0,                                  /* 0x028 Reserved      */
	Default_Handler,                    /* 0x02C SVCall        */
	Default_Handler,                    /* 0x030 Debug Monitor */
	0,                                  /* 0x034 Reserved      */
	Default_Handler,                    /* 0x038 PendSV        */
	Default_Handler                     /* 0x03C SysTick       */
};

void Reset_Handler(void)
{
	_init_data();
	main();
	while (1);
}

void _init_data(void)
{
	unsigned long *src = &_etext;
	unsigned long *dst = &_sdata;
	
	/* ROM has data at end of text. copy it */
	while (dst < &_edata) {
		*dst++ = *src++;
	}

	for(dst = &_sbss; dst < &_ebss; dst++) {
		*dst = 0;
	}
}

void Default_Handler(void)
{
	while (1);
}

int main(void)
{
	SystemClock_Config();
	GPIO_Config();
	while (1) {
		Toggle_Led();
		DelayMS(1000);
	}
	return 0;
}

static void SystemClock_Config(void)
{
	/* Turn on Clock Source */
	RCC_CR |= RCC_CR_HSEON;
	while (!(RCC_CR & RCC_CR_HSERDY));
	/* Setting Power */
	RCC_APB1ENR |= RCC_APB1ENR_PWREN;
	PWR_CR |= (PWR_CR_VOS_1 | PWR_CR_VOS_0);
	/* Setting Flash */
	FLASH_ACR |= FLASH_ACR_LATENCY_3WS | FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN;
	/* PLL Config and Stting source clock for PLL */
	RCC_PLLCFGR |= (PLL_N << RCC_PLLCFGR_PLLN) | (PLL_M << RCC_PLLCFGR_PLLM) | (PLL_P << RCC_PLLCFGR_PLLP);
	RCC_PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
	/* Config AHB, APB1 and APB2 */
	RCC_CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1;
	/* Turn on PLL */
	RCC_CR |= RCC_CR_PLLON;
	while (!(RCC_CR & RCC_CR_PLLRDY));
	/* Config System Clock */
	RCC_CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC_CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
}

static void GPIO_Config(void)
{
	/* Turn on GPIOA */
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	/* Config GPIOA Pin 5 as Output */
	GPIOA_MODER |= GPIO_MODER_MODER5_0;
}

static void Toggle_Led(void)
{
	uint32_t odr = GPIOA_ODR;
	GPIOA_BSRR |= ((odr & (1 << 5)) << 16u) | (~odr & (1 << 5));
}

static void DelayMS(uint32_t period)
{
	uint32_t time = 1000 * period;
	while (time--) {
		asm("nop");
	}
}
