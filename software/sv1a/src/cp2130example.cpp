
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include <stdio.h>

#include "cp2130.h"
#include "mcp2515.h"

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    libusb_context *ctx = NULL;
    if(libusb_init(&ctx) < 0)
    {
		printf("ERROR: failed in libusb init\r\n");
	}
	libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_WARNING);

    cp2130_device_t *spi = cp2130_init(ctx);

    // Print version
    uint8_t ubMajor, ubMinor;
    cp2130_get_version(spi, &ubMajor, &ubMinor);
    printf("Version: %0d.%0d\r\n", ubMajor, ubMinor);

    // Write OTP USB Config
    //cp2130_set_usb_cfg(spi, 0x10C4, 0x87A0, CP2130_USP_MAX_POW_MA(500u), CP2130_USB_BUS_POW_REG_EN, 3, 0, CP2130_USB_PRIORITY_WRITE, CP2130_USB_CFG_MSK_MAX_POW);

    // Read OTP USB Config
    uint16_t usVid, usPid;
    uint8_t ubMaxPow, ubPowMode, ubTransferPriority;
    cp2130_get_usb_cfg(spi, &usVid, &usPid, &ubMaxPow, &ubPowMode, &ubMajor, &ubMinor, &ubTransferPriority);
    printf("VID: 0x%04X\r\n", usVid);
    printf("PID: 0x%04X\r\n", usPid);
    printf("Max Power: %d mA\r\n", ubMaxPow * 2);
    printf("Power Mode: 0x%02X\r\n", ubPowMode);
    printf("Transfer Priority: 0x%02X\r\n", ubTransferPriority);

    // Read USB ID Strings / Serial
    uint8_t ubStr[63];
    memset(ubStr, 0x00, 63);
    cp2130_get_manufacturer_string(spi, ubStr);
    printf("Manufacturer String: %s\r\n", ubStr);
    memset(ubStr, 0x00, 63);
    cp2130_get_prod_string(spi, ubStr);
    printf("Product String: %s\r\n", ubStr);
    memset(ubStr, 0x00, 63);
    cp2130_get_serial(spi, ubStr);
    printf("Serial: %s\r\n", ubStr);

    // Config GPIOs
    cp2130_set_gpio_mode_level(spi, CP2130_GPIO1, CP2130_GPIO_OUT_PP, CP2130_GPIO_HIGH); // CAN Reset
    cp2130_set_gpio_mode_level(spi, CP2130_GPIO4, CP2130_GPIO_IN, CP2130_GPIO_HIGH); // CAN Interrupt

    // Config Clock Output
    cp2130_set_clockdiv(spi, 3); // 24 MHz / 3 = 8MHz

    // Config SPI Transaction settings (Channel 0)
    cp2130_set_spi_word(spi, CP2130_SPI_CH0, CP2130_SPI_WRD_CS_MODE_PP | CP2130_SPI_WRD_CLK_6M);
    cp2130_set_gpio_cs(spi, CP2130_CS_CH0, CP2130_CS_MD_EN_DIS_OTHERS);

    // Init CAN
    printf("Init CAN...\r\n");

    cp2130_set_gpio_values(spi, 0, CP2130_GPIO1_MSK); // Assert reset
    usleep(10000);
    cp2130_set_gpio_values(spi, CP2130_GPIO1_MSK, CP2130_GPIO1_MSK); // Deassert reset

    MCP_CAN *can = new MCP_CAN(spi);

    if(can->begin(MCP_ANY, CAN_125KBPS, MCP_8MHZ) == CAN_OK)
    {
        printf("CAN init ok!\r\n");

	    can->setMode(MCP_NORMAL);
    }
    else
    {
        printf("CAN init fail!\r\n");

        return 1;
    }

    while(1)
    {
        static int lastTime = 0;

        int now = time(0);

        if(now - lastTime > 60)
        {
            lastTime = now;

            static uint8_t count = 0;

            printf("Going to write message\r\nHeader: 0x100\r\nBuffer: 0x55, 0xAA, 0x01, 0x02, 0x55, 0xAA, 0x01, 0x%02X\r\n", count);

            uint8_t data[] = {0x55, 0xAA, 0x01, 0x02, 0x55, 0xAA, 0x01, count};

            if(can->sendMsgBuf(0x100, 0, 8, data) == CAN_OK)
                printf("Send ok!\r\n");
            else
                printf("Send fail!\r\n");

            if(count == 254) count = 0;
            else count++;
        }

        uint16_t gpioval;

        cp2130_get_gpio_values(spi, &gpioval);

        while(!(gpioval & CP2130_GPIO4_MSK))
        {
            printf("Going to read message\r\n");

            uint32_t header = 0x100;
            uint8_t length = 8;

            uint8_t data[16];
            memset(data, 0x00, 16);

            if(can->readMsgBuf(&header, &length, data) == CAN_OK)
            {
                printf("receive ok!\r\n");

                for(uint8_t i = 0; i < 8; i++)
                {
                    printf("data: %02X\r\n", data[i]);
                }
            }
            else
            {
                printf("receive fail!\r\n");
            }

            cp2130_get_gpio_values(spi, &gpioval);
        }
    }

    cp2130_free(spi);

	if(ctx)
		libusb_exit(ctx);
}