#include "ssd1306.h"

#include <stdint.h>
#include <string.h>
#include <stdarg.h>

uint8_t i2c_packet[SSD1306_I2C_PACKET_MAX_SIZE];

void ssd1306_init(uint8_t address)
{
    uint8_t cmd[] = {
        SSD1306_CMD_SET_DISPLAY_OFF,
        SSD1306_CMD_SET_MEM_ADDRESSING_MODE, SSD1306_ADDRESSING_MODE_HORIZONTAL,
        SSD1306_CMD_SET_PAGE_START_ADDR,
        SSD1306_CMD_SET_REMAPPED_MODE_COM_OUTPUT_SCAN_DIRECTION,
        SSD1306_CMD_SET_LO_COL_START_ADD | 0x00,
        SSD1306_CMD_SET_HI_COL_START_ADD | 0x00,
        SSD1306_CMD_SET_DISPLAY_START_LINE,
        SSD1306_CMD_SET_CONTRAST_CONTROL, 63,
        SSD1306_CMD_MAP_SEG0_TO_COL_127,
        SSD1306_CMD_SET_DISPLAY_NORMAL,
        SSD1306_CMD_SET_MULTIPLEX_RATIO, (DISPLAY_HEIGHT - 1),
        SSD1306_CMD_ENTIRE_DISPLAY_ON_FOLLOW_RAM,
        SSD1306_CMD_SET_DISPLAY_OFFSET, 0x00,
        SSD1306_CMD_SET_DISPLAY_CK_RATIO_AND_OSC, 0xF0,
        SSD1306_CMD_SET_PRE_CHRG_PERIOD, 0x22,
        SSD1306_CMD_SET_COM_PINS_HW_CONF, (SSD1306_COM_PIN_CFG_SEQUENTIAL | SSD1306_COM_LEFT_RIGHT_REMAP_DISABLE),
        SSD1306_CMD_SET_VCOMH, SSD1306_VCOMH_0_77VCC,
        SSD1306_CMD_CHARGE_PUMP_SET, SSD1306_CHARGE_PUMP_ENABLED,
        SSD1306_CMD_SET_DISPLAY_ON
    };

    ssd1306_cmd(address, cmd, sizeof(cmd));

    return;
}

void ssd1306_cmd(uint8_t address, uint8_t* cmd, uint32_t size)
{
    i2c_packet[0] = SSD1306_CTRL_BYTE_CMD;
    memcpy(i2c_packet + 1, cmd, size);

    ssd1306_i2c_write(address, i2c_packet, size + 1);
}

void ssd1306_data(uint8_t address, uint8_t* data, uint32_t size)
{
    i2c_packet[0] = SSD1306_CTRL_BYTE_DATA;
    memcpy(i2c_packet + 1, data, size);
    ssd1306_i2c_write(address, i2c_packet, size + 1);
}

void ssd1306_goto(uint8_t address, uint8_t column, uint8_t page)
{
    uint8_t cmd[] = {
        SSD1306_CMD_SET_PAGE_START_ADDR + page,
        SSD1306_CMD_SET_COL_ADDRESS,
        column,
        DISPLAY_WIDTH - 1
    };

    ssd1306_cmd(address, cmd, sizeof(cmd));
}

void ssd1306_clear_screen(uint8_t address)
{
    uint8_t i;
    uint8_t zeros[DISPLAY_WIDTH] = { 0 };

    ssd1306_reset_column_and_page_boundaries(address);

    for (i = 0; i < DISPLAY_HEIGHT / 8; i++) {
        ssd1306_goto(address, 0, i);
        ssd1306_data(address, zeros, DISPLAY_WIDTH);
    }
}

void ssd1306_set_column_and_page_address_boundary(
    uint8_t address, ssd1306_address_boundary_t column, ssd1306_address_boundary_t page)
{
    uint8_t cmd[] = {
        SSD1306_CMD_SET_COL_ADDRESS,
        column.start,
        column.end,
        SSD1306_CMD_SET_PAGE_ADDRESS,
        page.start,
        page.end
    };

    ssd1306_cmd(address, cmd, sizeof(cmd));
}

void ssd1306_set_column_address_boundary(uint8_t address, uint8_t start, uint8_t end)
{
    uint8_t cmd[] = { SSD1306_CMD_SET_COL_ADDRESS, start, end };
    ssd1306_cmd(address, cmd, sizeof(cmd));
}

void ssd1306_set_page_address_boundary(uint8_t address, uint8_t start, uint8_t end)
{
    uint8_t cmd[] = { SSD1306_CMD_SET_PAGE_ADDRESS, start, end };
    ssd1306_cmd(address, cmd, sizeof(cmd));
}

void ssd1306_reset_column_and_page_boundaries(uint8_t address)
{
    ssd1306_address_boundary_t column = { 0, DISPLAY_WIDTH - 1 };
    ssd1306_address_boundary_t page = { 0, DISPLAY_HEIGHT / 8 - 1 };
    ssd1306_set_column_and_page_address_boundary(address, column, page);
}
