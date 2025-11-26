#include "init.h"
    
uint8_t prev_button = 1;
uint8_t led_state = 0; 
uint8_t button_pressed = 0;
uint8_t led_1 = 0;
uint8_t led_2 = 0;
uint8_t led_3 = 0;
uint8_t led_4 = 0;

int main(void)
{
    GPIO_Init_Memory();             // Инициализация PB7 (синий светодиод) - прямой доступ к памяти
    GPIO_Init_Wish_Myself_Macros(); // Инициализация PA3 (светодиод) - макросы
    GPIO_Init_CMSIS();              // Инициализация PC0, PC3 (светодиоды), PC6 (кнопка) - CMSIS


    while (1)
    {
        uint8_t current_button = (GPIOC->IDR & GPIO_IDR_ID6) ? 1 : 0;

        // Обнаружение нажатия кнопки (передний фронт)
        if (current_button && !prev_button)
        {
            for (volatile uint32_t i = 0; i < 200000; i++);
            if (GPIOC->IDR & GPIO_IDR_ID6)
            {
                button_pressed = 1;
            }
        }

        // Обработка зафиксированного нажатия кнопки
        if (button_pressed)
        {
            button_pressed = 0;
            led_state = (led_state + 1) % 7;

            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x00800000UL; // PB7 выключен (прямой доступ)
            BIT_SET(GPIOA_BSRR, GPIO_PIN_RESET_3);                // PA3 выключен (макросы)
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR0);                  // PC0 выключен (CMSIS)
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3);                  // PC3 выключен (CMSIS)
            led_1 = 0;
            led_2 = 0;
            led_3 = 0;
            led_4 = 0;
            
            switch (led_state)
            {
                case 0:
                    // Все светодиоды выключены - начальное состояние
                    led_1 = 0;
                    led_2 = 0;
                    led_3 = 0;
                    led_4 = 0;
                    break;
                    
                case 1:
                    // Первый светодиод - PB7 (прямой доступ)
                    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x00000080UL; // PB7 включен
                    led_1 = 1;
                    break;
                    
                case 2:
                    // Второй светодиод - PA3 (макросы)
                    BIT_SET(GPIOA_BSRR, GPIO_PIN_SET_3); // PA3 включен
                    led_2 = 1;
                    break;
                    
                case 3:
                    // Третий светодиод - PC0 (CMSIS)
                    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS0); // PC0 включен
                    led_3 = 1;
                    break;
                    
                case 4:
                    // Четвертый светодиод - PC3 (CMSIS)
                    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS3); // PC3 включен
                    led_4 = 1;
                    break;
                    
                case 5:
                    // Пятое нажатие - все светодиоды выключены
                    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x00800000UL; // PB7 выключен
                    BIT_SET(GPIOA_BSRR, GPIO_PIN_RESET_3);                // PA3 выключен
                    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR0);                  // PC0 выключен
                    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3);                  // PC3 выключен
                    led_1 = 0;
                    led_2 = 0;
                    led_3 = 0;
                    led_4 = 0;
                    break;
                case 6:
                    // Шестое нажатие - все светодиоды включены
                    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x00000080UL; // PB7 включен
                    BIT_SET(GPIOA_BSRR, GPIO_PIN_SET_3);                  // PA3 включен
                    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS0);                  // PC0 включен
                    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS3);                  // PC3 включен
                    led_1 = 1;
                    led_2 = 1;
                    led_3 = 1;
                    led_4 = 1;
                    break;
            }
        }

        prev_button = current_button;
    }
}