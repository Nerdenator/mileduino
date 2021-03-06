/*#ifndef	DEFAULTS_H
#define	DEFAULTS_H

#define	P_MOSI	B,3
#define	P_MISO	B,4
#define	P_SCK	B,5

//#define	MCP2515_CS			D,3	// Rev A
#define	MCP2515_CS			B,2 // Rev B
#define	MCP2515_INT			D,2
#define LED2_HIGH			B,0
#define LED2_LOW			B,0

#endif	// DEFAULTS_H
*/
// Arduino Uno (Atmega 168/328 pin mapping)
//#define    P_MOSI            B,3 // pin 11
//#define    P_MISO            B,4 // pin 12
//#define    P_SCK             B,5 // pin 13
//#define    MCP2515_CS        B,2 // pin 10
//#define    MCP2515_INT       D,2 // pin 2
//#define    LED2_HIGH         B,0 // pin 8
//#define    LED2_LOW          B,0 // pin 8

// Pins remapped to Arduino Mega 2560
#define    P_MOSI              B,2 // pin 51
#define    P_MISO              B,3 // pin 50
#define    P_SCK               B,1 // pin 52
#define    MCP2515_CS          B,0 // pin 53
#define    MCP2515_INT         E,4 // pin 2
#define    LED2_HIGH           H,5 // pin 8
#define    LED2_LOW            H,5 // pin 8
