#include "main.h"

void setup_gpio();

int main(){
    HAL_Init();
    SystemClock_Config();
    setup_gpio();

    while(1){
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
        HAL_Delay(200);
    }
}


void setup_gpio(){
    __HAL_RCC_GPIOA_CLK_ENABLE();   
    __HAL_RCC_GPIOB_CLK_ENABLE();   
    __HAL_RCC_GPIOC_CLK_ENABLE();   
    __HAL_RCC_GPIOD_CLK_ENABLE();   

    GPIO_InitTypeDef ginit = {.Pin = GPIO_PIN_12|GPIO_PIN_13, .Mode = GPIO_MODE_OUTPUT_PP, 
                    .Pull = GPIO_NOPULL, .Speed = GPIO_SPEED_FREQ_LOW};

    HAL_GPIO_Init(GPIOB, &ginit);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);
}
