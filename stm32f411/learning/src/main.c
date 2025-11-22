#include "main.h"

char c = 'a';

void setup_gpio();
void setup_uart();
UART_HandleTypeDef huart; 

int main(){
    HAL_Init();
    SystemClock_Config();
    setup_gpio();
    setup_uart();

    HAL_UART_Receive_IT(&huart, &c, 1);
    while(1){
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
        HAL_Delay(100);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == USART2){
        HAL_UART_Transmit(huart, &c, 1, HAL_MAX_DELAY);
        HAL_UART_Receive_IT(huart, &c, 1);
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

void setup_uart(){
    __HAL_RCC_USART2_CLK_ENABLE();

    GPIO_InitTypeDef ginit = {.Pin = GPIO_PIN_2|GPIO_PIN_3, .Mode = GPIO_MODE_AF_PP, 
                    .Pull = GPIO_NOPULL, .Speed = GPIO_SPEED_FREQ_VERY_HIGH, .Alternate = GPIO_AF7_USART2};

    HAL_GPIO_Init(GPIOA, &ginit);

    UART_InitTypeDef hinit = {.BaudRate = 115200, .WordLength = UART_WORDLENGTH_8B, .StopBits = UART_STOPBITS_1,
                                .Parity = UART_PARITY_NONE, .Mode = UART_MODE_TX_RX, 
                                .OverSampling = UART_OVERSAMPLING_16, .HwFlowCtl = UART_HWCONTROL_NONE};
    
    huart.Instance = USART2;
    huart.Init = hinit;
    if(HAL_UART_Init(&huart) != HAL_OK){
        Error_Handler();
    }

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}
