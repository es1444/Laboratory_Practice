#ifndef INIT_H
#define INIT_H

#include "stm32f4xx.h"
#include "stm32f429xx.h"
#include <stdint.h>

// ====== Макросы для светодиода PA3 ======
#define RCC_AHB1ENR                     *(uint32_t *)(0x40023800UL + 0x30UL)
#define RCC_GPIOA_EN                    0x01UL
#define RCC_GPIOB_EN                    0x02UL
#define RCC_GPIOC_EN                    0x04UL
#define RCC_GPIOD_EN                    0x08UL

#define GPIOA_MODER                     *(uint32_t *)(0x40020000UL + 0x00UL)
#define GPIOA_OSPEEDR                   *(uint32_t *)(0x40020000UL + 0x08UL)
#define GPIOA_PUPDR                     *(uint32_t *)(0x40020000UL + 0x0CUL)
#define GPIOA_BSRR                      *(uint32_t *)(0x40020000UL + 0x18UL)

#define GPIO_OUTPUT_MODE_PIN_3          0x00000040UL  // PA3 output mode
#define GPIO_SPEED_MED_PIN_3            0x00000040UL  // PA3 medium speed
#define GPIO_PIN_SET_3                  0x00000008UL  // PA3 set
#define GPIO_PIN_RESET_3                0x00080000UL  // PA3 reset

#define BIT_SET(REG, BIT) ((REG) |= (BIT))
#define BIT_CLEAR(REG, BIT) ((REG) &= ~(BIT))
#define BIT_READ(REG, BIT) ((REG) & (BIT))

void GPIO_Init_Memory(void);             // PB7 (синий встроенный) — прямое обращение
void GPIO_Init_Wish_Myself_Macros(void); // PA3 — макросы
void GPIO_Init_CMSIS(void);              // PC0, PC3 — CMSIS, PC6 — кнопка

#endif
