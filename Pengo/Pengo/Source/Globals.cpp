#include <stdio.h>
#include <stdarg.h>
#ifdef _WIN32
#include <windows.h>
#endif

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
#ifdef _WIN32
	vsprintf_s(tmp_string, 4096, format, ap);
#else
	vsnprintf(tmp_string, 4096, format, ap);
#endif
	va_end(ap);
#ifdef _WIN32
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);
#else
	snprintf(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	printf("%s", tmp_string2);
#endif
}
