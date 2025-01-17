/*
 *  Copyright (c) 2010,
 *  Gavriloaie Eugen-Andrei (shiretu@gmail.com)
 *
 *  This file is part of crtmpserver.
 *  crtmpserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  crtmpserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with crtmpserver.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include "defines.h"
#include "utils/logging/baseloglocation.h"
#include "utils/logging/consoleloglocation.h"
#include "utils/logging/fileloglocation.h"
#include "utils/logging/logcatloglocation.h"
#include "utils/logging/sysloglocation.h"
#include "utils/logging/logger.h"



#ifdef VALIDATE_FROMAT_SPECIFIERS
#define __VALIDATE_FROMAT_SPECIFIERS(...) \
do { \
   char ___tempLocation[1024]; \
   snprintf(___tempLocation,1023,__VA_ARGS__); \
}while (0)
#else
#define __VALIDATE_FROMAT_SPECIFIERS(...)
#endif /* VALIDATE_FROMAT_SPECIFIERS */

#ifdef FILE_OVERRIDE
#define __FILE__OVERRIDE ""
#else
#define __FILE__OVERRIDE __FILE__
#endif

#ifdef LINE_OVERRIDE
#define __LINE__OVERRIDE 0
#else
#define __LINE__OVERRIDE __LINE__
#endif

#ifdef FUNC_OVERRIDE
#define __FUNC__OVERRIDE ""
#else
#define __FUNC__OVERRIDE __func__
#endif

#ifdef FILE_OVERRIDE
#define __FILE__OVERRIDE ""
#define E__FILE__ __FILE__OVERRIDE
#else /* FILE_OVERRIDE */
#define __FILE__OVERRIDE __FILE__
#ifdef SHORT_PATH_IN_LOGGER
#define E__FILE__ ((const char *)__FILE__OVERRIDE)+SHORT_PATH_IN_LOGGER
#else /* SHORT_PATH_IN_LOGGER */
#define E__FILE__ __FILE__OVERRIDE
#endif /* SHORT_PATH_IN_LOGGER */
#endif /* FILE_OVERRIDE */

class TrackContextLogger {
private:
	string _file;
	string _funcName;
	int _line;
public:

	TrackContextLogger(const char *pFile, const char *pFuncName, int line) {
		_file = pFile;
		_funcName = pFuncName;
		_line = line;
		printf("%s:%d ***** BEGIN %s\n", _file.c_str(), _line, _funcName.c_str());
	}

	virtual ~TrackContextLogger() {
		printf("%s:%d *****   END %s\n", _file.c_str(), _line, _funcName.c_str());
	}
};

#define TRACK_CONTEXT_LOGGER() TrackContextLogger ______tcl(E__FILE__,__FUNC__OVERRIDE,__LINE__OVERRIDE)



#define LOG(level,...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(level, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);}while(0)
#define FATAL(...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(_FATAL_, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);}while(0)

#define WARN(...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(_WARNING_, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);}while(0)
#define INFO(...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(_INFO_, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);}while(0)
#define DEBUG(...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(_DEBUG_, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);}while(0)
#define FINE(...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(_FINE_, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);}while(0)
#define FINEST(...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(_FINEST_, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);}while(0)
#define ASSERT(...) do{__VALIDATE_FROMAT_SPECIFIERS(__VA_ARGS__);BaseLogger::Log(_FATAL_, E__FILE__, __LINE__OVERRIDE, __FUNC__OVERRIDE, __VA_ARGS__);o_assert(false);abort();}while(0)
#define NYI WARN("%s not yet implemented",__FUNC__OVERRIDE);
#define NYIR do{NYI;return false;}while(0)
#define NYIA do{NYI;o_assert(false);abort();}while(0)
