/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include <cr_section_macros.h>
#include "initialize.hpp"
#include "drv/timer32.h"
#include "drv/led.h"
#include "drv/uart.h"
#include "drv/petit_fs/PetitFs.hpp"

#include "drv/petit_fs/diskio.h"

// 変数を実体化するだけ
#define GLOBAL_VALUE_DEFINITION
#include "global.hpp"


// TODO: insert other include files here

// TODO: insert other definitions and declarations here
void TimerCallback();
void LED_Blink();

int g_LED_BlinkTimer = 0;
int g_LED_Blink = 0;

uint8_t buf[512];

void PrintFsResult( FRESULT result )
{
	switch( result ){
	case FR_OK:
		UART_Print( "FR_OK" );
		break;
	case FR_DISK_ERR:
		UART_Print( "FR_DISK_ERR" );
		break;
	case FR_NOT_READY:
		UART_Print( "FR_NOT_READY" );
		break;
	case FR_NO_FILE:
		UART_Print( "FR_NO_FILE" );
		break;
	case FR_NOT_OPENED:
		UART_Print( "FR_NOT_OPENED" );
		break;
	case FR_NOT_ENABLED:
		UART_Print( "FR_NOT_ENABLED" );
		break;
	case FR_NO_FILESYSTEM:
		UART_Print( "FR_NO_FILESYSTEM" );
		break;
	default:
		UART_Print( "It Must be BUG!!!" );
		break;
	}
}

int main(void) {

    // TODO: insert code here

	Initialize_CPU();
	Initialize_Peripheral();
	Call_Static_Initializers();

	Timer32B1_SetCallback( TimerCallback );

	UART_Print( "FileSys Initialize." );

	petitfs::FileSys& fs = petitfs::FileSys::Instance();
	PrintFsResult( fs.Mount() );
	Init_SPI_Fast();

	petitfs::Dir dir = fs.OpenDirectory( "/" );
	PrintFsResult( dir.Status() );
	while( 1 ){
		const petitfs::FileInfo& info = dir.NextEntry();
		if( !info.IsValid() ){
			UART_Print( "Failed Next Entry");
			break;
		}

		UART_Print( "Print Entry" );
		UART_Print( info.Name() );
	}

	PrintFsResult( fs.OpenFile( "/TEST.TXT" ) );

	while( 1 ){
		uint16_t readbyte;
		FRESULT result;
		if( (result = fs.Read( buf, sizeof(buf) - 1, &readbyte)) != FR_OK  ){
			UART_Print( "Failed to read." );
			PrintFsResult( result );
			break;
		}
		if( readbyte == 0 ){
			UART_Print( "EOF" );
			break;
		}
		buf[readbyte] = '\0';
		UART_Print( reinterpret_cast<const char*>(buf) );
	}


	TurnOnLED( LED_COLOR_BLUE );

    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	LED_Blink();
    }

    return 0 ;
}

void TimerCallback()
{
	++g_LED_BlinkTimer;
}

void LED_Blink()
{
	if( g_LED_BlinkTimer >= 500 ){
		g_LED_BlinkTimer = 0;
		++g_LED_Blink;
		if( (g_LED_Blink & 0x01) == 0x01 ){
			TurnOnLED( LED_COLOR_BLUE );
		}
		else {
			TurnOffLED( LED_COLOR_BLUE );
		}
	}
}
