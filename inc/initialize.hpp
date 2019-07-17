/*
 * initialize.hpp
 *
 *  Created on: 2019/03/10
 *      Author: hogehogei
 */

#ifndef INITIALIZE_HPP_
#define INITIALIZE_HPP_


void Initialize_CPU();
void Initialize_Peripheral();
void Init_SPI_Slow();
void Init_SPI_Fast();
void Call_Static_Initializers();

#endif /* INITIALIZE_HPP_ */
