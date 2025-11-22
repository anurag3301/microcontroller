# I2C Scan stm
```c
uint8_t I2C_Scan(I2C_HandleTypeDef *hi2c) {
    HAL_StatusTypeDef status;

    for (uint8_t address = 1; address <= 127; address++) {
        status = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(address << 1), 2, 2);
        if (status == HAL_OK) {
        	return address;
        }
    }
}
```

