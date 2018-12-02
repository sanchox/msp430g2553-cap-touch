#include <msp430.h> 
#include <stdbool.h>

#include "structure.h"
#include "CTS_Layer.h"

#include "i2caddr.h"

typedef enum i2c_regmap {
    I2C_REGMAP_RAW_CAP = 0x0,
    I2C_REGMAP_RAW_CAP_GUARD = TOTAL_NUMBER_OF_ELEMENTS * sizeof(uint16_t),
    I2C_REGMAP_WHEEL_POS = I2C_REGMAP_RAW_CAP_GUARD,
    I2C_REGMAP_HORISONTAL_SLIDER_POS = I2C_REGMAP_WHEEL_POS + sizeof(uint16_t),
    I2C_REGMAP_VERTICAL_SLIDER_POS = I2C_REGMAP_HORISONTAL_SLIDER_POS + sizeof(uint16_t),
    I2C_REGMAP_SIZE = 0xFF,
} i2c_reg_t;

volatile uint8_t i2c_regmap[I2C_REGMAP_SIZE] = {0};
volatile uint8_t i2c_regnum = 0;
struct Element * keyPressed;

extern uint16_t baseCnt[TOTAL_NUMBER_OF_ELEMENTS];

uint16_t plane_val[9];

uint16_t pos = ILLEGAL_SLIDER_WHEEL_POSITION;

void sleep(unsigned int time)
{
    for (int i = time * 100; i > 0; --i) __no_operation();
}

void config_i2c_slave(unsigned char addr)
{
    __disable_interrupt();

    UCB0CTL1 |= UCSWRST;                      // Enable SW reset

    UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode

    UCB0I2COA = addr & 0x7f;                  // Own Address

    P1SEL  |= BIT6 + BIT7;                    // Assign I2C pins to USCI_B0
    P1SEL2 |= BIT6 + BIT7;                    // Assign I2C pins to USCI_B0

    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

    UCB0I2CIE |= UCSTTIE;                     // Enable STT interrupt
    UCB0I2CIE |= UCSTPIE;                     // Enable STP interrupt

    __enable_interrupt();
}

void set_i2c_reg(i2c_reg_t reg, uint16_t value)
{
    i2c_regmap[reg] = value >> 8;
    i2c_regmap[reg + 1] = value & 0xFF;
}

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

    BCSCTL1 = CALBC1_16MHZ;               // Set DCO to 1, 8, 12 or 16MHz
    DCOCTL = CALDCO_16MHZ;

    BCSCTL1 |= DIVA_0;                    // ACLK/1 [ACLK/(0:1,1:2,2:4,3:8)]
    BCSCTL2 |= DIVS_3;                    // SMCLK/8 [SMCLK/(0:1,1:2,2:4,3:8)]
    BCSCTL3 |= LFXT1S_2;                  // LFXT1 = VLO Clock Source

    P1OUT = 0x00;                         // Drive all Port 1 pins low
    P1DIR = 0xFF;                         // Configure all Port 1 pins outputs

    P2OUT = 0x00;                         // Drive all Port 2 pins low
    P2DIR = 0xFF;                         // Configure all Port 2 pins outputs

    config_i2c_slave(I2C_SLAVE_ADDR);

    // Initialize Baseline measurement
    TI_CAPT_Init_Baseline(&plane);
    // Update baseline measurement (Average 5 measurements)
    TI_CAPT_Update_Baseline(&plane, 10);

    // Initialize Baseline measurement
//    TI_CAPT_Init_Baseline(&wheel);
    // Update baseline measurement (Average 5 measurements)
//    TI_CAPT_Update_Baseline(&wheel, 5);

    // Initialize Baseline measurement
//    TI_CAPT_Init_Baseline(&horisontal_slider);
    // Update baseline measurement (Average 5 measurements)
//    TI_CAPT_Update_Baseline(&horisontal_slider, 5);

    // Initialize Baseline measurement
//    TI_CAPT_Init_Baseline(&vertical_slider);
    // Update baseline measurement (Average 5 measurements)
//    TI_CAPT_Update_Baseline(&vertical_slider, 5);

    memcpy((uint16_t *)(i2c_regmap + 0xa0), baseCnt, TOTAL_NUMBER_OF_ELEMENTS * sizeof(*baseCnt));

    // Main loop starts here
    while (1)
    {
        TI_CAPT_Raw(&plane, (uint16_t *)i2c_regmap);
        __no_operation(); // Set breakpoint here

        TI_CAPT_Custom(&plane, plane_val);
        memcpy((uint16_t *)(i2c_regmap + 0x20), plane_val, 9 * sizeof(*plane_val));
        __no_operation(); // Set breakpoint here
/*
        pos = TI_CAPT_Wheel(&wheel);
        if (pos != ILLEGAL_SLIDER_WHEEL_POSITION)
            set_i2c_reg(I2C_REGMAP_WHEEL_POS, pos);

        pos = TI_CAPT_Slider(&horisontal_slider);
        if (pos != ILLEGAL_SLIDER_WHEEL_POSITION)
            set_i2c_reg(I2C_REGMAP_HORISONTAL_SLIDER_POS, pos);

        pos = TI_CAPT_Slider(&vertical_slider);
        if (pos != ILLEGAL_SLIDER_WHEEL_POSITION)
            set_i2c_reg(I2C_REGMAP_VERTICAL_SLIDER_POS, pos);
*/
        //sleep(1);
    }
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCIAB0TX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    if (IFG2 & UCB0RXIFG) // Receiver
    {
        i2c_regnum = UCB0RXBUF;
    }
    else if (IFG2 & UCB0TXIFG) // Transmitter
    {
        UCB0TXBUF = i2c_regmap[i2c_regnum++];
    }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCIAB0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    if (UCB0STAT & UCSTTIFG)
    {
        UCB0STAT &= ~UCSTTIFG;                 // Clear start condition int flag

        if (UCB0CTL1 & UCTR)
            IE2 |= UCB0TXIE;                          // Enable TX interrupt
        else
            IE2 |= UCB0RXIE;                          // Enable RX interrupt
    }
    else
    {
        UCB0STAT &= ~UCSTPIFG;                 // Clear start condition int flag

        IE2 &= ~UCB0TXIE;
        IE2 &= ~UCB0RXIE;
    }

}
