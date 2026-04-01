#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <stdint.h>

#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 128
#define SSD1306_I2C_PACKET_MAX_SIZE DISPLAY_HEIGHT / 8 * DISPLAY_WIDTH + 1

#define SSD1306_I2C_ADDRESS 0x3C
#define SSD1306_CTRL_BYTE_CMD 0x00
#define SSD1306_CTRL_BYTE_DATA 0x40

/* Fundamental Command */
#define SSD1306_CMD_SET_CONTRAST_CONTROL 0x81
#define SSD1306_CMD_ENTIRE_DISPLAY_ON_FOLLOW_RAM 0xA4
#define SSD1306_CMD_ENTIRE_DISPLAY_ON_IGNORE_RAM 0xA5
#define SSD1306_CMD_SET_DISPLAY_NORMAL 0xA6
#define SSD1306_CMD_SET_DISPLAY_INVERSE 0xA7
#define SSD1306_CMD_SET_DISPLAY_ON 0xAF
#define SSD1306_CMD_SET_DISPLAY_OFF 0xAE

/* Scrolling Command */
#define SSD1306_CMD_CONTINUOUS_HORIZONTAL_SCROLL_RIGHT 0x26
#define SSD1306_CMD_CONTINUOUS_HORIZONTAL_SCROLL_LEFT 0x27
#define SSD1306_CMD_CONTINUOUS_VERTICAL_AND_HORIZONTAL_SCROLL_RIGHT 0x29
#define SSD1306_CMD_CONTINUOUS_VERTICAL_AND_HORIZONTAL_SCROLL_LEFT 0x2A
#define SSD1306_CMD_DEACTIVATE_SCROLL 0x2E
#define SSD1306_CMD_ACTIVATE_SCROLL 0x2F
#define SSD1306_CMD_SET_VERTICAL_SCROLL_AREA 0xA3

/* Scrolling Constants */
#define SSD1306_SCROLL_LEFT 0x00
#define SSD1306_SCROLL_RIGHT 0x01

#define SSD1306_CONTINUOUS_SCROLL_PAGE0 0x00
#define SSD1306_CONTINUOUS_SCROLL_PAGE1 0x01
#define SSD1306_CONTINUOUS_SCROLL_PAGE2 0x02
#define SSD1306_CONTINUOUS_SCROLL_PAGE3 0x03
#define SSD1306_CONTINUOUS_SCROLL_PAGE4 0x04
#define SSD1306_CONTINUOUS_SCROLL_PAGE5 0x05
#define SSD1306_CONTINUOUS_SCROLL_PAGE6 0x06
#define SSD1306_CONTINUOUS_SCROLL_PAGE7 0x07

#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_5 0x00
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_64 0x01
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_128 0x02
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_256 0x03
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_3 0x04
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_4 0x05
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_25 0x06
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_2 0x07

/* Addressing Setting Command */
#define SSD1306_CMD_SET_LO_COL_START_ADD 0x00
#define SSD1306_CMD_SET_HI_COL_START_ADD 0x10
#define SSD1306_CMD_SET_MEM_ADDRESSING_MODE 0x20
#define SSD1306_CMD_SET_COL_ADDRESS 0x21
#define SSD1306_CMD_SET_PAGE_ADDRESS 0x22
#define SSD1306_CMD_SET_PAGE_START_ADDR 0xB0

/* Addressing Setting Constants */
#define SSD1306_ADDRESSING_MODE_HORIZONTAL 0x00
#define SSD1306_ADDRESSING_MODE_VERTICAL 0x01
#define SSD1306_ADDRESSING_MODE_PAGE 0x02

/* Hardware Configuration Command */
#define SSD1306_CMD_SET_DISPLAY_START_LINE 0x40
#define SSD1306_CMD_MAP_SEG0_TO_COL_0 0xA0
#define SSD1306_CMD_MAP_SEG0_TO_COL_127 0xA1
#define SSD1306_CMD_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_CMD_SET_NORMAL_MODE_COM_OUTPUT_SCAN_DIRECTION 0xC0
#define SSD1306_CMD_SET_REMAPPED_MODE_COM_OUTPUT_SCAN_DIRECTION 0xC8
#define SSD1306_CMD_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_CMD_SET_COM_PINS_HW_CONF 0xDA

/* Hardware Configuration Constants */
#define SSD1306_MAP_SEG0_TO_COL_0 0
#define SSD1306_MAP_SEG0_TO_COL_127 1
#define SSD1306_COM_NORMAL_MODE_SCAN 0
#define SSD1306_COM_REMAPPED_MODE_SCAN 1
#define SSD1306_COM_PIN_CFG_SEQUENTIAL 0x00
#define SSD1306_COM_PIN_CFG_ALTERNATIVE 0x10
#define SSD1306_COM_LEFT_RIGHT_REMAP_DISABLE 0x00
#define SSD1306_COM_LEFT_RIGHT_REMAP_ENABLE 0x20

/* Timing and Driving Scheme Setting Command */
#define SSD1306_CMD_SET_DISPLAY_CK_RATIO_AND_OSC 0xD5
#define SSD1306_CMD_SET_PRE_CHRG_PERIOD 0xD9
#define SSD1306_CMD_SET_VCOMH 0xDB
#define SSD1306_CMD_NOP 0xE3

/* Timing and Driving Scheme Setting Constants */
#define SSD1306_VCOMH_0_65VCC 0x00
#define SSD1306_VCOMH_0_77VCC 0x20
#define SSD1306_VCOMH_0_83VCC 0x30

/* Charge Pump Command */
#define SSD1306_CMD_CHARGE_PUMP_SET 0x8D

/* Charge Pump Constants */
#define SSD1306_CHARGE_PUMP_DISABLED 0x10
#define SSD1306_CHARGE_PUMP_ENABLED 0x14

/* Structures to interface with the driver */
typedef struct {
    uint8_t start;
    uint8_t end;
} ssd1306_address_boundary_t;

/* User implemented funciton */
extern uint8_t ssd1306_i2c_write(uint8_t i2c_address, uint8_t *data, uint32_t size);

/* Low level device control functions */
void ssd1306_data(uint8_t address, uint8_t* data, uint32_t size);
void ssd1306_cmd(uint8_t address, uint8_t* cmd, uint32_t size);

/* High level functions */
void ssd1306_init(uint8_t address);
void ssd1306_clear_screen(uint8_t address);
void ssd1306_goto(uint8_t address, uint8_t column, uint8_t page);
void ssd1306_set_column_and_page_address_boundary(uint8_t address, ssd1306_address_boundary_t column, ssd1306_address_boundary_t page);
void ssd1306_set_column_address_boundary(uint8_t address, uint8_t start, uint8_t end);
void ssd1306_set_page_address_boundary(uint8_t address, uint8_t start, uint8_t end);
void ssd1306_reset_column_and_page_boundaries(uint8_t address);

#ifdef SSD1306_PRINTF
void ssd1306_printf(uint8_t address, const char* fmt, ...);
#endif

#endif /* __SSD1306_H__ */
