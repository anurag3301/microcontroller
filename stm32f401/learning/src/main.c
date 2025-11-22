#include <stm32f4xx_hal.h>
#include "main.h"
#include <stdio.h>

uint8_t c;
UART_HandleTypeDef huart;
volatile uint32_t last_press = 0;

void setup_gpio();
void setup_uart();


int main(){
    HAL_Init();
    SystemClock_Config();
    enable_gpio();
    setup_gpio();
    setup_uart();
    if(HAL_UART_Receive_IT(&huart, &c, 1) != HAL_OK){
        Error_Handler();
    }
    int written = 0;
    while(1){
        // GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
        // written = sprintf(c, "%d\n\r", state); 
        // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, !state);
        // HAL_UART_Receive(&huart, &c, 4, HAL_MAX_DELAY);
        // HAL_UART_Transmit(&huart, &c, 4, HAL_MAX_DELAY);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
        HAL_Delay(100);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == USART2){
        HAL_UART_Transmit(huart, &c, 1, HAL_MAX_DELAY);
        HAL_UART_Receive_IT(huart, &c, 1);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0){
        uint32_t now = HAL_GetTick();
        if (now - last_press < 20){
            return;
        }
        last_press = now;
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
    }
}

void setup_gpio(){
    GPIO_InitTypeDef init = {.Pin = GPIO_PIN_3|GPIO_PIN_2, .Mode = GPIO_MODE_OUTPUT_PP,
                             .Pull = GPIO_NOPULL, .Speed = GPIO_SPEED_FREQ_LOW};
    HAL_GPIO_Init(GPIOC, &init);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3|GPIO_PIN_2, GPIO_PIN_RESET);

    init = (GPIO_InitTypeDef){.Pin = GPIO_PIN_0, .Mode = GPIO_MODE_IT_FALLING,
                             .Pull = GPIO_PULLUP};
    HAL_GPIO_Init(GPIOC, &init);
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void setup_uart(){
    __HAL_RCC_USART2_CLK_ENABLE();

    GPIO_InitTypeDef init = {.Pin = GPIO_PIN_3 | GPIO_PIN_2, .Mode = GPIO_MODE_AF_PP,
                             .Pull = GPIO_NOPULL, .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
                             .Alternate = GPIO_AF7_USART2};
    HAL_GPIO_Init(GPIOA, &init);

    huart.Instance = USART2;
    huart.Init = (UART_InitTypeDef){
        .BaudRate = 115200, .WordLength = UART_WORDLENGTH_8B, 
        .StopBits = UART_STOPBITS_1, .Parity = UART_PARITY_NONE, 
        .Mode = UART_MODE_TX_RX, .HwFlowCtl = UART_HWCONTROL_NONE, 
        .OverSampling = UART_OVERSAMPLING_16};

    if (HAL_UART_Init(&huart) != HAL_OK){
        Error_Handler();
    }
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}
