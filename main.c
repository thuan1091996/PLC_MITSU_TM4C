/* --------0.Project information--------------------
 * PLC MITSU FX series - TM4C123G communication
 * Author : TRAN MINH THUAN
 * Company: VIET MOLD MACHINE
 * Supported by: NGUYEN DUC QUYEN
 * Debugging diary:
 *          +Test (READ_D, WRITE_D) done from D0-D105
 *          +Test (READ_M)
 * -------------------------------------------------*/

/* --------1.System requirement--------------------
 * -
 * -First initialize UART port to communication with PLC FX series
 * -Systick initialization and Systick interrupt EN in the delay_ns function
 *  and auto disable after finish delay
 * -Read - Write to D memory (size - 16-bit)
 *
 * Read - Write to M memory (size - 16-bit)
 * Author : TRAN MINH THUAN
 * Company: Viet Mold Machine
 * Supported by: NGUYEN DUC QUYEN
 * -------------------------------------------------*/

// ***** 2. Pre-processor Directives Section *****
//Add libraries
#include "include.h"
//-----------------Buttons-----------------------
#define BUTTON_PORT    SYSCTL_PERIPH_GPIOF
#define BUTTON_BASE    GPIO_PORTF_BASE
#define BUTTON_PIN     GPIO_PIN_4


unsigned long Tick=0;              //Tick for creating delay using Systick interrupt
unsigned long Tick_count=0;
unsigned long start=0;
unsigned long end=0;
uint32_t Temp_Test=0;
uint16_t Temp_Test1=0;
uint16_t Temp_Test2=0;
uint16_t Temp_Test3=0;

/* Button Initialization
 * Function: 4MA, Pull-up resistor
 * Input: No
 * Output: No
*/
void Button_Init(void)
{
    if(!SysCtlPeripheralReady(BUTTON_PORT))             //Check Clock peripheral
    {
        SysCtlPeripheralEnable(BUTTON_PORT);            //Enable if not ready (busy or disable)
        while (!SysCtlPeripheralReady(BUTTON_PORT));    //Wait for peripheral ready
    }
    GPIOPinTypeGPIOInput(BUTTON_BASE, BUTTON_PIN);      //Input
    GPIOPadConfigSet(BUTTON_BASE, BUTTON_PIN, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
}
/*------------------------------------------------------------- */

/*--------------------------\\//------------------------------- */
/*-----------------4.Function definition section------------------*/
int main(void)
{
    // Clock configure at 80Mhz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    UART_Init();
    Systick_Init();
    Button_Init();
    IntMasterEnable();
while (1)
    {
    uint8_t ui32Button=0;
            ui32Button=GPIOPinRead(BUTTON_BASE, BUTTON_PIN); //Read button
            if(ui32Button==0)                                //If pressed
            {
                Write_D(Temp_Test2, Temp_Test3);
                delay_us(100000);
                Temp_Test=Read_D(Temp_Test1);
                delay_us(200000);                            //delay to debounce button
            }
    }
}
void Systick_ISR(){
    Tick++;             //Increase every 1 us corresponding to Reload value
}



