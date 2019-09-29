
#include "LPC1100.h"
#include "drv/sdcard/SDC_Drv_SPI.hpp"
#include "drv/uart.h"
#include "initialize.hpp"

static constexpr uint32_t sk_SPI_Send_Timeout = 1000;
static constexpr uint32_t sk_SPI_Recv_Timeout = 1000;

SDC_Drv_SPI::SDC_Drv_SPI()
: m_SPI( SPI_Drv::Instance(0) )
{}

SDC_Drv_SPI::~SDC_Drv_SPI()
{}

void SDC_Drv_SPI::InitSlowSpeed()
{
	Init_SPI_Slow();
}

void SDC_Drv_SPI::InitFastSpeed()
{
	Init_SPI_Fast();
}

bool SDC_Drv_SPI::Select()
{
    //HAL_GPIO_WritePin( GPIOA, SDCARD_CS_Pin, GPIO_PIN_RESET );
	GPIO0DATA &= ~_BV(2);
	m_SPI.TxRx( 0xFF );

	if( waitReady() ){
		return true;
	}

	Release();
	return false;
}

void SDC_Drv_SPI::Release()
{
    //HAL_GPIO_WritePin( GPIOA, SDCARD_CS_Pin, GPIO_PIN_SET );
	GPIO0DATA |= _BV(2);

    // MMC/SDC の場合は SCLKに同期して DO信号の解放が行われる。
    // DO信号を確実に解放するために、1byte分クロックを送っておく。
	m_SPI.TxRx( 0xFF );
}

bool SDC_Drv_SPI::send( const uint8_t* data, uint32_t len )
{
    m_SPI.Send_U8( data, len );

    return true;
}

bool SDC_Drv_SPI::recv( uint8_t* data, uint32_t len )
{
	for( uint32_t i = 0; i < len; ++i ){
		data[i] = m_SPI.TxRx(0xFF);
	}

	return true;
}

bool SDC_Drv_SPI::flush()
{
    // 書き込みバッファは持たないので、特に何もしない
    return true;
}

bool SDC_Drv_SPI::waitReady()
{
	uint8_t tmp = 0;
	while(1){
		tmp = m_SPI.TxRx(0xFF);
		if( tmp == 0xFF ){
			break;
		}
	}

	return tmp == 0xFF;
}
