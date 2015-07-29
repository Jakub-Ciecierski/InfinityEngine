#include "smart_console.h"

#include <stdio.h>
#include <stdlib.h>

void SmartPrint(std::ostream& out, unsigned int debugLevel)
{
	if(debugLevel >= CSL_DEBUG_LVL)
		std::cout << "[" <<  __FILE__ << "]" << out << std::endl;
}

void SmartPrint(const char* msg, unsigned int debugLevel)
{
	if(debugLevel >= CSL_DEBUG_LVL)
		fprintf(stderr, "[%s] %s\n", __FILE__, msg);
}

void SmartPrint(const char* msg)
{
	unsigned int debugLevel = 1;
	if(debugLevel >= CSL_DEBUG_LVL)
			fprintf(stderr, "[%s] %s\n", __FILE__, msg);
}
