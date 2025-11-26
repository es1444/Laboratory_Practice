#include "init.h"

//PB7 (синий встроенный светодиод, прямое обращение)
void GPIO_Init_Memory(void)
{
    // Включение тактирования порта GPIOB (синий светодиод PB7)
    *(uint32_t *)(0x40023800UL + 0x30UL) |= 0x02UL;
    
    // Настройка пина PB7 на выход
    *(uint32_t *)(0x40020400UL + 0x00UL) |= 0x4000UL; 
    
    // Средняя скорость
    *(uint32_t *)(0x40020400UL + 0x08UL) |= 0x4000UL; 
    
    // Без подтяжки
    *(uint32_t *)(0x40020400UL + 0x0CUL) &= ~0xC000UL; 
    
    // Выключение светодиода
    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x00800000UL;
}

// PA3 (макросы)
void GPIO_Init_Wish_Myself_Macros(void)
{
    BIT_SET(RCC_AHB1ENR, RCC_GPIOA_EN);

    BIT_SET(GPIOA_MODER, GPIO_OUTPUT_MODE_PIN_3);
    BIT_SET(GPIOA_OSPEEDR, GPIO_SPEED_MED_PIN_3);
    BIT_CLEAR(GPIOA_PUPDR, 0x000000C0UL);

    BIT_SET(GPIOA_BSRR, GPIO_PIN_RESET_3); 
}

//PC0, PC3 (светодиоды, CMSIS) + кнопка PC6
void GPIO_Init_CMSIS(void)
{
    // Включаем тактирование портов A, B, C
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

    // PC0 — выход
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE0_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPD0);

    // PC3 — выход  
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE3_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPD3);

    // PC6 — кнопка (вход, pull-down)
    CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODE6); 
    SET_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPD6_1);
}

