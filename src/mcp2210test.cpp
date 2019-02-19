/**
 *    Copyright 2012, Kerry D. Wong
 *
 *      http://www.kerrywong.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <time.h>
#include "mcp2210.h"
#include "mcp2515.h"

using namespace std;

/**
 * Test GPIO
 * Generate a rectangular wave on GP0
 */
void TestGPIO(hid_device* handle) {
    ChipSettingsDef chipDef;

    /**
     * Set GPIO to be output
     */
    chipDef = GetChipSettings(handle);

    for (int i = 0; i < 9; i++) {
        chipDef.GP[i].PinDesignation = GP_PIN_DESIGNATION_GPIO;
        chipDef.GP[i].GPIODirection = GPIO_DIRECTION_OUTPUT;
        chipDef.GP[i].GPIOOutput = 0;
    }

    int r0 = SetChipSettings(handle, chipDef);

    /**
     * Configure GPIO0 direction to output
     */
    GPPinDef def = GetGPIOPinDirection(handle);
    def.GP[0].GPIODirection = GPIO_DIRECTION_OUTPUT;
    def.GP[0].PinDesignation = GP_PIN_DESIGNATION_GPIO;

    int r = SetGPIOPinDirection(handle, def);

    ///< Generate a rectangular wave by toggling GP0.
    while (1) {
        def.GP[0].GPIOOutput = 1 - def.GP[0].GPIOOutput;
        r = SetGPIOPinVal(handle, def);
    }
}

int main(int argc, char** argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    hid_device *handle;

    handle = InitMCP2210();

    if (handle == NULL)
    {
        printf("ERROR opening device. Try using sudo.\n");
        
        return 1;
    }

    printf("Going init mcp2515...\r\n");

    MCP_CAN *mcp2515 = new MCP_CAN(handle);

    if(mcp2515->begin(MCP_ANY, CAN_125KBPS, MCP_8MHZ) == CAN_OK)
    {
        printf("Begin ok!\r\n");

	    mcp2515->setMode(MCP_NORMAL);
    }
    else
    {
        printf("Begin fail!\r\n");

        return 1;
    }

    while(1)
    {
        static int lastTime = 0;

        int now = time(0);

        if(now - lastTime > 1)
        {
            lastTime = now;

            static int count = 0;

            printf("Going to write messag\rHeader: 0x100\rBuffer: 0x55, 0xAA, 0x01, 0x02, 0x55, 0xAA, 0x01, %02X \n", count);

            uint8_t data[] = {0x55, 0xAA, 0x01, 0x02, 0x55, 0xAA, 0x01, 0x02};

            if(mcp2515->sendMsgBuf(0x100, 0, 8, data) == CAN_OK)
                printf("Send ok!\r\n");
            else
                printf("Send fail!\r\n");

            count++;
        }

        ExternalInterruptPinStatusDef extInt = GetNumOfEventsFromInterruptPin(handle, 1);

        if(extInt.InterruptEventCounter)
            printf("Event count: %hu\r\n", extInt.InterruptEventCounter);

        while(extInt.InterruptEventCounter--)
        {
            printf("Going to read message\r\n");

            uint32_t header = 0x100;
            uint8_t length = 8;

            uint8_t data[16];
            memset(data, 0x00, 16);

            if(mcp2515->readMsgBuf(&header, &length, data) == CAN_OK)
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
        }
    }

    //TestGPIO(handle);

    ReleaseMCP2210(handle);

    return 0;
}
