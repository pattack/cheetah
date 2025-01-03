#ifndef REBEL_I2C_H
#define REBEL_I2C_H

// For use with _delay_us()
#define T2_TWI 5 //!< >4,7us
#define T4_TWI 4 //!< >4,0us

// Defines error code generating
//#define PARAM_VERIFICATION
//#define NOISE_TESTING
#define SIGNAL_VERIFY //!< Verifies the signal is correct. This should probably
                      //!< be on always.

/****************************************************************************
  Bit and byte definitions
****************************************************************************/
#define TWI_READ_BIT 0 //!< Bit position for R/W bit in "address byte".
#define TWI_ADR_BITS                                                           \
  1 //!< Bit position for LSB of the slave address bits in the init byte.
#define TWI_NACK_BIT 0 //!< Bit position for (N)ACK bit.

// Note these have been renumbered from the Atmel Apps Note. Most likely errors
// are now
//		lowest numbers so they're easily recognized as LED flashes.
#define I2C_NO_DATA 0x08 //!< Transmission buffer is empty
#define I2C_DATA_OUT_OF_BOUND                                              \
  0x09                            //!< Transmission buffer is outside SRAM space
#define I2C_UE_START_CON 0x07 //!< Unexpected Start Condition
#define I2C_UE_STOP_CON 0x06  //!< Unexpected Stop Condition
#define I2C_UE_DATA_COL 0x05  //!< Unexpected Data Collision (arbitration)
#define I2C_NO_ACK_ON_DATA 0x02 //!< The slave did not acknowledge  all data
#define I2C_NO_ACK_ON_ADDRESS                                              \
  0x01 //!< The slave did not acknowledge  the address
#define I2C_MISSING_START_CON                                              \
  0x03 //!< Generated Start Condition not detected on bus
#define I2C_MISSING_STOP_CON                                               \
  0x04 //!< Generated Stop Condition not detected on bus
#define I2C_BAD_MEM_READ 0x0A //!< Error during external memory read

// Device dependant defines ADDED BACK IN FROM ORIGINAL ATMEL .H

#if defined(__AVR_AT90Mega169__) | defined(__AVR_ATmega169__) |                \
    defined(__AVR_AT90Mega165__) | defined(__AVR_ATmega165__) |                \
    defined(__AVR_ATmega325__) | defined(__AVR_ATmega3250__) |                 \
    defined(__AVR_ATmega645__) | defined(__AVR_ATmega6450__) |                 \
    defined(__AVR_ATmega329__) | defined(__AVR_ATmega3290__) |                 \
    defined(__AVR_ATmega649__) | defined(__AVR_ATmega6490__)
#define DDR_USI DDRE
#define PORT_USI PORTE
#define PIN_USI PINE
#define PORT_USI_SDA PORTE5
#define PORT_USI_SCL PORTE4
#define PIN_USI_SDA PINE5
#define PIN_USI_SCL PINE4
#endif

#if defined(__AVR_ATtiny25__) | defined(__AVR_ATtiny45__) |                    \
    defined(__AVR_ATtiny85__) | defined(__AVR_AT90Tiny26__) |                  \
    defined(__AVR_ATtiny26__)
#define DDR_USI DDRB
#define PORT_USI PORTB
#define PIN_USI PINB
#define PORT_USI_SDA PORTB0
#define PORT_USI_SCL PORTB2
#define PIN_USI_SDA PINB0
#define PIN_USI_SCL PINB2
#endif

#if defined(__AVR_ATtiny84__) | defined(__AVR_ATtiny44__)
#define DDR_USI DDRA
#define PORT_USI PORTA
#define PIN_USI PINA
#define PORT_USI_SDA PORTA6
#define PORT_USI_SCL PORTA4
#define PIN_USI_SDA PINA6
#define PIN_USI_SCL PINA4
#endif

#if defined(__AVR_AT90Tiny2313__) | defined(__AVR_ATtiny2313__)
#define DDR_USI DDRB
#define PORT_USI PORTB
#define PIN_USI PINB
#define PORT_USI_SDA PORTB5
#define PORT_USI_SCL PORTB7
#define PIN_USI_SDA PINB5
#define PIN_USI_SCL PINB7
#endif

/* From the original .h
// Device dependant defines - These for ATtiny2313. // CHANGED FOR ATtiny85

    #define DDR_USI             DDRB
    #define PORT_USI            PORTB
    #define PIN_USI             PINB
    #define PORT_USI_SDA        PORTB0   // was PORTB5 - N/U
    #define PORT_USI_SCL        PORTB2   // was PORTB7 - N/U
    #define PIN_USI_SDA         PINB0    // was PINB5
    #define PIN_USI_SCL         PINB2    // was PINB7
*/

// General defines
#define TRUE 1  //!< True
#define FALSE 0 //!< False

//********** Prototypes **********//

void I2C_Master_Initialize(void);
unsigned char I2C_Start_Random_Read(unsigned char *, unsigned char);
unsigned char I2C_Start_Read_Write(unsigned char *, unsigned char);
unsigned char I2C_Master_Stop(void);
unsigned char I2C_Get_State_Info(void);

#endif //REBEL_I2C_H
