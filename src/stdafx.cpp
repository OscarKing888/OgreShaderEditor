#include "stdafx.h"

using namespace Ogre;

String formatString(const char* fmtStr, ...)
{		
	char tmp[512];
	memset(tmp, 0, 512 * sizeof(char));

	va_list args;
	va_start(args, fmtStr);
	_vsnprintf(tmp, 512, fmtStr, args);
	va_end(args);

	return String(tmp);
}