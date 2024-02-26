/**
 * This utility is derived from Ben Eater's sketch, preparing EEPROM image for 7-segment
 * multiplexed display.
 * 
 * Original code: https://github.com/beneater/eeprom-programmer/blob/master/multiplexed-display/multiplexed-display.ino
 */

/* 
 * Use powershell command "Format-Hex display.bin" to dump contents of bin file to terminal
 */

/*
 * Run .ino file in arduino IDE to upload hardware verify or TommyPROM to arduino EEPROM programmer. Then connect and send
 * to EEPROM via Tera Term, send file using XMODEM transfer protocol. See TommyPROM docs for further info
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define AT28C64_SIZE 8192

/* 
   In-memory array, emulating 16 kbit EEPROM
 */
uint8_t eeprom_data[AT28C64_SIZE];


/*
   Write a byte to the EEPROM at the specified address.
*/
void writeEEPROM(int address, uint8_t data) {
  eeprom_data[address] = data;
}


/*
   Write the contents of eeprom_data array into file.
*/
void saveToFile() {
  FILE *stream = fopen("display.bin", "wb");
  fwrite(eeprom_data, sizeof(eeprom_data), 1, stream);
  fclose(stream);
}


int main() {

  // Bit patterns for the digits 0..9, A..F, '-', and '.' for 5641AS 4-digit 7-segment, common-cathode LED display
  uint8_t digits[] = {0x3f,    0x06,   0x5b,   0x4f,   0x66,   0x6d,   0x7d,   0x07,   0x7f,   0x67,   0x77,   0x7c,   0x39,   0x5f,   0x79,   0x71,   0x40,   0x80};
  //                  0        1       2       3       4       5       6       7       8       9       A       B       C       D       E       F       -       .

  puts("Programming ones place");
  for (int value = 0; value <= 255; value += 1) {
    writeEEPROM(value, digits[value % 10]);
  }
  puts("Programming tens place");
  for (int value = 0; value <= 255; value += 1) {
    writeEEPROM(value + 256, digits[(value / 10) % 10]);
  }
  puts("Programming hundreds place");
  for (int value = 0; value <= 255; value += 1) {
    writeEEPROM(value + 512, digits[(value / 100) % 10]);
  }
  puts("Programming sign");
  for (int value = 0; value <= 255; value += 1) {
    writeEEPROM(value + 768, 0);
  }

  puts("Programming ones place (twos complement)");
  for (int value = -128; value <= 127; value += 1) {
    writeEEPROM((uint8_t)value + 1024, digits[abs(value) % 10]);
  }
  puts("Programming tens place (twos complement)");
  for (int value = -128; value <= 127; value += 1) {
    writeEEPROM((uint8_t)value + 1280, digits[abs(value / 10) % 10]);
  }
  puts("Programming hundreds place (twos complement)");
  for (int value = -128; value <= 127; value += 1) {
    writeEEPROM((uint8_t)value + 1536, digits[abs(value / 100) % 10]);
  }
  puts("Programming sign (twos complement)");
  for (int value = -128; value <= 127; value += 1) {
    if (value < 0) {
      writeEEPROM((uint8_t)value + 1792, digits[16]);
    } else {
      writeEEPROM((uint8_t)value + 1792, 0);
    }
  }

  puts("Programming HEX");
  for (int value = 0; value <= 255; value += 1) {
    uint16_t hex_repr =  
    // there is an interesting challenge to be had here!
  }

  saveToFile();

  return 0;
}