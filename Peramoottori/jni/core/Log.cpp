#include "Log.h"
#include <android/log.h>

#include <cstdarg>
#include <cstdio>
#include <string>

using namespace pm;
using namespace std;

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_INFO", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "DEBUG_WARNING", __VA_ARGS__))

void Log::PrintInfo(const char* text...)
{
	char* tempInfo = FormatMessage(text);
	LOGI(tempInfo);
}

void Log::PrintWarning(const char* text...)
{
	char* tempWarning = FormatMessage(text);
	LOGW(tempWarning);
}

bool Log::PrintGLError(const char* file, const unsigned int line)
{
	GLenum tempError = GL_NO_ERROR;
	bool errors = false; // Make sure to get all errors before returning from function.

	do // Loop as long as there are error flags.
	{
		tempError = glGetError(); // Get current error.

		if (tempError != GL_NO_ERROR)
		{
			errors = true;
			DEBUG_WARNING(("OpenGL error (%i) %s on line %s.", tempError, file, line));
		}

	} while (tempError != GL_NO_ERROR);

	return errors;
}

void Log::ClearGLError()
{
	GLenum tempError = GL_NO_ERROR;

	// Logic here is to clear error queue from earlier error messages that didn't crash the program,
	// so we can be 100% sure of our error handling on more critical parts.

	while (true)
	{
		GLenum tempError = glGetError();
		if (tempError == GL_NO_ERROR)
			return;
	}
}

char* Log::FormatMessage(const char* text...)
{
	char* tempBuffer = nullptr; // Buffer to hold our formatted string.

	va_list arguments; // Type to hold information about variable arguments.
	va_start(arguments, text); // Initialize a variable argument list.

	vasprintf(&tempBuffer, text, arguments); // Composes string with the same text that would be printed if format was used on printf.

	va_end(arguments); // End using variable argument list.
	return tempBuffer;
}