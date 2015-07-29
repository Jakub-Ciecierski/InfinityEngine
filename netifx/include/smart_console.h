/*
 * smart_console.h
 *
 *  Created on: Jul 26, 2015
 *      Author: jakub
 */

#ifndef _NETWORK_SMART_CONSOLE_H_
#define _NETWORK_SMART_CONSOLE_H_

#include <iostream>

/**
 * Is used as the upper bound for debugLevel in PrintLine()
 * If debulLevel is lower than DEBUG_LEVEL
 * then it will not be printed.
 *
 * If CSL_DEBUG_LVL is equal to 0, no print will show
 */
#define CSL_DEBUG_LVL 1

void SmartPrint(std::ostream& os, unsigned int debugLevel);

void SmartPrint(const char* msg, unsigned int debugLevel);
void SmartPrint(const char* msg);

#endif /* _NETWORK_SMART_CONSOLE_H_ */
