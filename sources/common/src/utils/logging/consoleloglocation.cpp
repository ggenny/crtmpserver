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


#include "common.h"

ConsoleLogLocation::ConsoleLogLocation(Variant &configuration)
: BaseLogLocation(configuration) {
	_allowColors = false;
	ADD_VECTOR_END(_colors, FATAL_COLOR);
	ADD_VECTOR_END(_colors, ERROR_COLOR);
	ADD_VECTOR_END(_colors, WARNING_COLOR);
	ADD_VECTOR_END(_colors, INFO_COLOR);
	ADD_VECTOR_END(_colors, DEBUG_COLOR);
	ADD_VECTOR_END(_colors, FINE_COLOR);
	ADD_VECTOR_END(_colors, FINEST_COLOR);
}

ConsoleLogLocation::~ConsoleLogLocation() {
	SET_CONSOLE_TEXT_COLOR(NORMAL_COLOR);
}

bool ConsoleLogLocation::Init() {
	if (!BaseLogLocation::Init()) {
		return false;
	}
	if (_configuration.HasKeyChain(V_BOOL, false, 1, CONF_LOG_APPENDER_COLORED))
		_allowColors = (bool)_configuration.GetValue(
			CONF_LOG_APPENDER_COLORED, false);
	return true;
}

void ConsoleLogLocation::Log(int32_t level, const char *pFileName,
		uint32_t lineNumber, const char *pFunctionName, string &message) {
	if (_singleLine) {
		replace(message, "\r", "\\r");
		replace(message, "\n", "\\n");
	}
#ifdef ANDROID
	if (_allowColors) {
		printf("%s%s:%u %s%s\n",
				STR(_colors[level]),
				pFileName,
				lineNumber,
				STR(message),
				STR(_colors[6]));
	} else {
		printf("%s:%u %s\n",
				pFileName,
				lineNumber,
				STR(message));
	}
#else
	time_t now = time(NULL);
	struct tm *tminfo;
	char buf[sizeof "YYYY-MM-DD HH:MM:SS"];
	tminfo = localtime(&now);
	strftime(buf, sizeof(buf), "%F %T", tminfo);
	if (_allowColors) {
		SET_CONSOLE_TEXT_COLOR(_colors[level]);
#ifdef LINUX
		fprintf(stdout, "%s [%s]%d[%lu] %s:%" PRIu32" %s", STR(buf), STR(BaseLogger::LevelToString(level)),
                        getpid(), pthread_self(), pFileName, lineNumber, STR(message));
#else
		fprintf(stdout, "%s %s:%" PRIu32" %s", STR(buf), pFileName, lineNumber, STR(message));
#endif
		//fprintf(stdout, "%d %s:%" PRIu32" %s", (int) getpid(), pFileName, lineNumber, STR(message));
		SET_CONSOLE_TEXT_COLOR(_colors[6]);
		fprintf(stdout, "\n");
	} else {
#ifdef LINUX
		fprintf(stdout, "%s [%s]%d[%lu] %s:%" PRIu32" %s\n", STR(buf), STR(BaseLogger::LevelToString(level)),
                        getpid(), pthread_self(), pFileName, lineNumber, STR(message));
#else
		fprintf(stdout, "%s %s:%" PRIu32" %s\n", STR(buf), pFileName, lineNumber, STR(message));
#endif
	}
#endif /* ANDROID */
	fflush(stdout);
}

void ConsoleLogLocation::SignalFork(uint32_t forkId) {

}
