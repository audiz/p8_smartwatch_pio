
#ifndef _VARIANT_FEATHER52832_
#define _VARIANT_FEATHER52832_

/** Master clock frequency */
#define VARIANT_MCK       (64000000ul)

/*
The nRF has two options for the LFCLK. Either it can use an external LFXTAL, or the internal RC Oscillator. 
The nRF52840 DK has an external LFXTAL, so it is used by default in most examples. 
If the custom PCB doesn't have this external LFXTAL, and the project sets the LFCLK source to an external XTAL, 
the softdevice will try to start this XTAL, and wait for it to respond. If it doesn't respond, 
the softdevice will just stop in this wait state.*/

// USE_LFRC or USE_LFXO must be defined in board's variant.h
// LFRC 	Advantages : low cost Disadvantages : low accuracy, susceptible to temperature
// LFXO 	Advantages : high accuracy, not easy to receive interference. Disadvantages : increased hardware costs
// LFSYNT 	Advantages : low cost, relatively high accuracy. Disadvantage : increase power consumption
// Remarks: Set according to the actual hardware scheme and requirements NRF_SDH_CLOCK_LF_SRC, you can solve the stuck problem encountered above.

//#define USE_LFXO      // Board uses 32khz crystal for LF  CLOCK_LFCLKSRC_SRC_Xtal
//#define USE_LFRC    // Board uses RC for LF CLOCK_LFCLKSRC_SRC_RC
#define USE_LFRC 
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Number of pins defined in PinDescription array
#define PINS_COUNT           (32u)
#define NUM_DIGITAL_PINS     (32u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (0u)

// LEDs
#define PIN_LED1             (15) // 27
#define PIN_LED2             (10)

#define LED_BUILTIN          PIN_LED1
#define LED_CONN             PIN_LED2

#define LED_RED              PIN_LED1
#define LED_BLUE             PIN_LED2

#define LED_STATE_ON         1         // State when LED is litted

/*
 * Analog pins
 */
#define PIN_A0               (1) // P0.01
#define PIN_A1               (2) // P0.02
#define PIN_A2               (3) // P0.03
#define PIN_A3               (4) // P0.04
#define PIN_A4               (5) // P0.05
#define PIN_A5               (6) // P0.06

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A1  = PIN_A1 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A3  = PIN_A3 ;
static const uint8_t A4  = PIN_A4 ;
static const uint8_t A5  = PIN_A5 ;

#define ADC_RESOLUTION    14

/*
 * Serial interfaces
 */
// Serial
#define PIN_SERIAL_RX       (22) // P0.00
#define PIN_SERIAL_TX       (23) // P0.01

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         (4u) // P0.22
#define PIN_SPI_MOSI         (3u) // P0.23
#define PIN_SPI_SCK          (2u) // P0.24

static const uint8_t SS   = -1 ;  // P0.25
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (6) // P0.20  3
#define PIN_WIRE_SCL         (7) // P0.21  2

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#ifdef __cplusplus
}
#endif

#endif
