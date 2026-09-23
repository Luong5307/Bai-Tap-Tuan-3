#include "max7219.h"

void MAX7219_Write(SPI_HandleTypeDef *hspi, uint8_t addr, uint8_t data) {
    uint8_t buf[2] = {addr, data};
    
    // Kéo CS xuống LOW
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    
    // Truyền dữ liệu qua SPI
    HAL_SPI_Transmit(hspi, buf, 2, HAL_MAX_DELAY);
    
    // Kéo CS lên HIGH để chốt dữ liệu
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void MAX7219_Init(SPI_HandleTypeDef *hspi) {
    MAX7219_Write(hspi, MAX7219_REG_DISPLAYTEST, 0x00); // Tắt Test Mode
    MAX7219_Write(hspi, MAX7219_REG_DECODEMODE, 0x00);  // Tắt BCD Mode
    MAX7219_Write(hspi, MAX7219_REG_SCANLIMIT, 0x07);   // Hiển thị 8 hàng
    MAX7219_Write(hspi, MAX7219_REG_INTENSITY, 0x01);   // Độ sáng mức nhỏ
    MAX7219_Write(hspi, MAX7219_REG_SHUTDOWN, 0x01);    // Bật IC (Normal operation)
    
    MAX7219_Clear(hspi);
}

void MAX7219_Clear(SPI_HandleTypeDef *hspi) {
    for (uint8_t i = 1; i <= 8; i++) {
        MAX7219_Write(hspi, i, 0x00);
    }
}

void MAX7219_DisplayBuffer(SPI_HandleTypeDef *hspi, uint8_t *buffer) {
    for (uint8_t i = 0; i < 8; i++) {
        MAX7219_Write(hspi, i + 1, buffer[i]);
    }
}
