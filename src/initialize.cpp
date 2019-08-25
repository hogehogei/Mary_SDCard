/*
 * initialize.cpp
 *
 *  Created on: 2019/03/10
 *      Author: hogehogei
 */

#include "LPC1100.h"
#include "initialize.hpp"
#include "drv/led.h"
#include "drv/timer32.h"
#include "drv/uart.h"
#include "drv/systick.h"
#include "drv/spi.h"

// For initialize static constructor
extern void (*__init_array_start[]) ();
extern void (*__init_array_end[]) ();

// Initialize functions
void Init_Port();

void Initialize_CPU()
{
	/* Configure BOD control (Reset on Vcc dips below 2.7V) */
	BODCTRL = 0x13;

	/* Configure system clock generator (36MHz system clock with IRC) */
	MAINCLKSEL = 0;							/* Select IRC as main clock */
	MAINCLKUEN = 0; MAINCLKUEN = 1;
	FLASHCFG = (FLASHCFG & 0xFFFFFFFC) | 2;	/* Set wait state for flash memory (1WS) */

	SYSPLLCLKSEL = 0;						/* Select IRC for PLL-in */
	SYSPLLCLKUEN = 0; SYSPLLCLKUEN = 1;
	SYSPLLCTRL = (3 - 1) | (2 << 6);		/* Set PLL parameters (M=3, P=4) */
	PDRUNCFG &= ~0x80;						/* Enable PLL */
	while ((SYSPLLSTAT & 1) == 0) ;			/* Wait for PLL locked */

	SYSAHBCLKDIV = 1;						/* Set system clock divisor (1) */
	MAINCLKSEL = 3;							/* Select PLL-out as main clock */
	MAINCLKUEN = 0; MAINCLKUEN = 1;

	SYSAHBCLKCTRL |= 0x1005F;
}

void Initialize_Peripheral()
{
	// ポート入出力初期化
	Init_Port();
	// UARTの初期化
	Init_UART();
	UART_Print( "Init_UART()" );
	// オンボードLEDの初期化
	Init_LED();
	UART_Print( "Init_LED()" );
	// Systick Timerの初期化
	Init_Systick();
	UART_Print( "Init_Systick()" );
	// Timer32B1 の初期化 パケット送信タイマーに用いる
	Init_Timer32B1( 1000 );    // 1ms
	UART_Print( "Init_Timer32B1()" );
}

void Init_SPI_Slow()
{
	SPI_Drv::Settings settings = {
			0,
			8,
			100,
			SPI_Drv::Role::ROLE_MASTER,
			SPI_Drv::Mode::MODE0
	};

	SPI_Drv::Stop();
	if( SPI_Drv::Initialize(settings) ){
		UART_Print( "Init_SPI_Slow() succeeded." );
	}
	else {
		UART_Print( "Init_SPI_Slow() failed." );
	}
}

void Init_SPI_Fast()
{
	SPI_Drv::Settings settings = {
			0,
			8,
			2,
			SPI_Drv::Role::ROLE_MASTER,
			SPI_Drv::Mode::MODE0
	};

	SPI_Drv::Stop();
	if( SPI_Drv::Initialize(settings) ){
		UART_Print( "Init_SPI_Fast() succeeded." );
	}
	else {
		UART_Print( "Init_SPI_Fast() failed." );
	}
}

void Init_Port()
{
	GPIO0DIR |= _BV(2);
}

__attribute__ ((section(".after_vectors")))
void Call_Static_Initializers()
{
	int count = __init_array_end - __init_array_start;
	for( int i = 0; i < count; ++i ){
		__init_array_start[i]();
	}
}

