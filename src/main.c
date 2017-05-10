// ATTiny24a @ 1MHz
// avrdude -p attiny24 -c usbasp -P usb  -U lfuse:w:0xE2:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m      8MHz
// avrdude -p attiny24 -c usbasp -P usb  -U lfuse:w:0x62:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m      1MHz

// ------- biblioteki standardowe -----
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

#include "utils.h"
#include "ds18b20.h"


#include <avr/io.h>
#ifndef _AVR_IOXXX_H_
#include <avr/iotn24a.h>
#endif
#ifndef BUILD_REV
#define BUILD_REV 111
#endif

#define BAUD_RATE 4800
#define UART_BIT_LENGTH (1e6 / BAUD_RATE - 0)

//---------------- definicje -----------------
#define TEMP_MIN        30 // temperatura załączenia
#define TEMP_MAX        70 // temperatura pełnych obrotów
#define PWM_MIN         40 // minimalne obroty wentylatora
//=================================================================
#define UART_TX     B, 0     // wyjście UART
#define DS12B20_IN  B, 1
#define PWM_OUT     B, 2

#define BUFF_SIZE 4
char buff[BUFF_SIZE];

void uart_tx(uint8_t c);
void uart_printNumber(const const uint16_t num);
void printStr(char* string);

int main(void) {

    INPUT(DS12B20_IN);
    OUTPUT(UART_TX);
    OUTPUT(PWM_OUT);

    TCCR0A = (1 << COM0A1) | (1 << WGM00); // phase correct PWM mode
    TCCR0B = (1 << CS10) | (1 << CS12); // clock source = CLK/1024, start PWM

    OCR0A = 200;

    float t = 0;
    int x = 0;

    printStr("\r\nTermometr PWM\r\n");

    while (1) {

        t = ds18b20_gettemp();
        x = 0;

        if (t >= TEMP_MIN) {
            x = PWM_MIN + (float) ((float) ((float) t - TEMP_MIN)
                    / (float) (TEMP_MAX - TEMP_MIN)) * (float) (255 - PWM_MIN);
            if (x > 255)
                x = 255;
        }

        // włącz na chwilę wysokie obroty
        if (x > 0 && OCR0A == 0)
            x = 200;

        OCR0A = x;


        printStr("TMP: ");

        //  dtostrf(t, 10, 1, buff);
        // printStr(buff);
        uart_printNumber(t);

        printStr(", PWM: ");
        uart_printNumber(OCR0A);


        printStr("\r\n");

        //-----------------------------

//        if (!READ(SW1)) {
//
//            TOGGLE(OUT1A);
//            TOGGLE(OUT1B);
//
//            _delay_ms(100);
//            while (!READ(SW1)) {
//
//            }
//
//        }
    }

}

void uart_tx(uint8_t c) {
    c = ~c;
    LOW(UART_TX); // start bit
    for (uint8_t i = 10; i; i--) { // 10 bits
        _delay_us(UART_BIT_LENGTH); // bit duration
        if (c & 1)
            LOW(UART_TX); // data bit 0
        else
            HIGH(UART_TX); // data bit 1 or stop bit
        c >>= 1;
    }
    _delay_us(1000);
}

void uart_printNumber(const const uint16_t num) {

    memset(buff, 0, BUFF_SIZE);
    itoa(num, (char*) buff, 10);

    for (int i = 0; i < BUFF_SIZE; i++)
        if (buff[i] > 32)
            uart_tx(buff[i]);
}

void printStr(char* string) {
    while (*string != 0x00) {
        uart_tx(*string);
        string++;
    }
}
