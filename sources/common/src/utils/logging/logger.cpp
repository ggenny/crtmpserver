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
#include "version.h"

BaseLogger *BaseLogger::_pLogger = NULL;
string Version::_lifeId;
uint16_t Version::_instance;

string Version::GetBuildNumber() {
#ifdef CRTMPSERVER_VERSION_BUILD_NUMBER
	return CRTMPSERVER_VERSION_BUILD_NUMBER;
#else /* CRTMPSERVER_VERSION_BUILD_NUMBER */
	return "";
#endif /* CRTMPSERVER_VERSION_BUILD_NUMBER */
}

uint64_t Version::GetBuildDate() {
#ifdef CRTMPSERVER_VERSION_BUILD_DATE
	return CRTMPSERVER_VERSION_BUILD_DATE;
#else /* CRTMPSERVER_VERSION_BUILD_DATE */
	return 0;
#endif /* CRTMPSERVER_VERSION_BUILD_DATE */
}

string Version::GetBuildDateString() {
	time_t buildDate = (time_t) GetBuildDate();
	if (buildDate == 0) {
		return "";
	}
	struct tm *pTs = gmtime(&buildDate);
	Variant v(*pTs);
	return (string) v;
}

string Version::GetReleaseNumber() {
#ifdef CRTMPSERVER_VERSION_RELEASE_NUMBER
	return CRTMPSERVER_VERSION_RELEASE_NUMBER;
#else /* CRTMPSERVER_VERSION_RELEASE_NUMBER */
	return "";
#endif /* CRTMPSERVER_VERSION_RELEASE_NUMBER */
}

string Version::GetCodeName() {
#ifdef CRTMPSERVER_VERSION_CODE_NAME
	return CRTMPSERVER_VERSION_CODE_NAME;
#else /* CRTMPSERVER_VERSION_CODE_NAME */
	return "";
#endif /* CRTMPSERVER_VERSION_CODE_NAME */
}

string Version::GetBuilderOSName() {
#ifdef CRTMPSERVER_VERSION_BUILDER_OS_NAME
	return CRTMPSERVER_VERSION_BUILDER_OS_NAME;
#else /* CRTMPSERVER_VERSION_BUILDER_OS_NAME */
	return "";
#endif /* CRTMPSERVER_VERSION_BUILDER_OS_NAME */
}

string Version::GetBuilderOSVersion() {
#ifdef CRTMPSERVER_VERSION_BUILDER_OS_VERSION
	return CRTMPSERVER_VERSION_BUILDER_OS_VERSION;
#else /* CRTMPSERVER_VERSION_BUILDER_OS_VERSION */
	return "";
#endif /* CRTMPSERVER_VERSION_BUILDER_OS_VERSION */
}

string Version::GetBuilderOSArch() {
#ifdef CRTMPSERVER_VERSION_BUILDER_OS_ARCH
	return CRTMPSERVER_VERSION_BUILDER_OS_ARCH;
#else /* CRTMPSERVER_VERSION_BUILDER_OS_ARCH */
	return "";
#endif /* CRTMPSERVER_VERSION_BUILDER_OS_ARCH */
}

string Version::GetBuilderOSUname() {
#ifdef CRTMPSERVER_VERSION_BUILDER_OS_UNAME
	return CRTMPSERVER_VERSION_BUILDER_OS_UNAME;
#else /* CRTMPSERVER_VERSION_BUILDER_OS_UNAME */
	return "";
#endif /* CRTMPSERVER_VERSION_BUILDER_OS_UNAME */
}

string Version::GetBuilderOS() {
	if (GetBuilderOSName() == "")
		return "";
	string result = GetBuilderOSName();
	if (GetBuilderOSVersion() != "") {
		result += "-" + GetBuilderOSVersion();
	}
	if (GetBuilderOSArch() != "") {
		result += "-" + GetBuilderOSArch();
	}
	return result;
}

string Version::GetBanner() {
	string result = HTTP_HEADERS_SERVER_US;
	if (GetReleaseNumber() != "")
		result += " version " + GetReleaseNumber();
	result += " build " + GetBuildNumber();
	if (GetCodeName() != "")
		result += " - " + GetCodeName();
	if (GetBuilderOS() != "") {
		result += " - (built for " + GetBuilderOS() + " on " + GetBuildDateString() + ")";
	} else {
		result += " - (built on " + GetBuildDateString() + ")";
	}
	return result;
}

Variant Version::GetAll() {
	Variant result;
	result["buildNumber"] = (string) GetBuildNumber();
	result["buildDate"] = (uint64_t) GetBuildDate();
	result["releaseNumber"] = (string) GetReleaseNumber();
	result["codeName"] = (string) GetCodeName();
	result["banner"] = (string) GetBanner();
	return result;
}

Variant Version::GetBuilder() {
	Variant result;
	result["name"] = (string) GetBuilderOSName();
	result["version"] = (string) GetBuilderOSVersion();
	result["arch"] = (string) GetBuilderOSArch();
	result["uname"] = (string) GetBuilderOSUname();
	return result;
}

MUTEX_TYPE BaseLogger::_lock = MUTEX_STATIC_INIT;

BaseLogger::BaseLogger() {
	_freeAppenders = false;
}

BaseLogger::~BaseLogger() {
	if (_freeAppenders) {

		FOR_VECTOR(_logLocations, i) {
			delete _logLocations[i];
		}
		_logLocations.clear();
	}
}

void BaseLogger::Init() {
	LOCK(&_lock);
	if (_pLogger != NULL)
		return;
	_pLogger = new BaseLogger();
}

void BaseLogger::Free(bool freeAppenders) {
	LOCK(&_lock);
	if (_pLogger != NULL) {
		_pLogger->_freeAppenders = freeAppenders;
		delete _pLogger;
		_pLogger = NULL;
	}
}

//void Logger::Log(int32_t level, const char *pFileName, uint32_t lineNumber,
//		const char *pFunctionName, const char *pFormatString, ...) {
//	{
//		LOCK(&_lock);
//		if (_pLogger == NULL)
//			return;
//	}
//
//	va_list arguments;
//	va_start(arguments, pFormatString);
//	string message = vFormat(pFormatString, arguments);
//	va_end(arguments);
//
//	{
//		LOCK(&_lock);
//
//		FOR_VECTOR(_pLogger->_logLocations, i) {
//			if (_pLogger->_logLocations[i]->EvalLogLevel(level, pFileName, lineNumber,
//					pFunctionName))
//				_pLogger->_logLocations[i]->Log(level, pFileName,
//					lineNumber, pFunctionName, message);
//		}
//	}
//}

// TODO: This new version need refactoring...
void BaseLogger::Log(int32_t level, const char *pFileName, uint32_t lineNumber,
		const char *pFunctionName, const char *pFormatString, ...) {
	{
		LOCK(&_lock);
		if (_pLogger == NULL)
			return;
	}

	va_list arguments;
	va_start(arguments, pFormatString);
	string message = vFormat(pFormatString, arguments);
	va_end(arguments);

	// Add separator

	message = "- " + message;

	// FIX
	int fLen = strlen(pFileName);

	for (int i = fLen - 1 ; i >= 0 ; i--) {
	    if (pFileName[i] == '/') {
		pFileName = pFileName + i + 1;
		break;
	    }
	}

	FOR_VECTOR(_pLogger->_logLocations, i) {
		if (_pLogger->_logLocations[i]->EvalLogLevel(level, pFileName, lineNumber,
				pFunctionName))
			_pLogger->_logLocations[i]->Log(level, pFileName,
				lineNumber, pFunctionName, message);
	}
}

// TODO: This new version need refactoring...
void BaseLogger::SimpleLog(int32_t level, const char *pFileName, uint32_t lineNumber,
		const char *pFunctionName, const char *pFormatString) {
	{
		LOCK(&_lock);
		if (_pLogger == NULL)
			return;
	}

	string message = pFormatString;
        
        // Add separator
        
        message = "- " + message;
        
        // FIX        
        int fLen = strlen(pFileName);
        
        for (int i = fLen - 1 ; i >= 0 ; i--) {
            if (pFileName[i] == '/') {
                pFileName = pFileName + i + 1;
                break;
            }
        }

	FOR_VECTOR(_pLogger->_logLocations, i) {
		if (_pLogger->_logLocations[i]->EvalLogLevel(level, pFileName, lineNumber,
				pFunctionName))
			_pLogger->_logLocations[i]->Log(level, pFileName,
				lineNumber, pFunctionName, message);
	}
}


bool BaseLogger::AddLogLocation(BaseLogLocation *pLogLocation) {
	LOCK(&_lock);
	if (_pLogger == NULL)
		return false;
	if (!pLogLocation->Init())
		return false;
	ADD_VECTOR_END(_pLogger->_logLocations, pLogLocation);
	return true;
}

void BaseLogger::SignalFork(uint32_t forkId) {
	LOCK(&_lock);
	if (_pLogger == NULL)
		return;

	FOR_VECTOR(_pLogger->_logLocations, i) {
		_pLogger->_logLocations[i]->SignalFork(forkId);
	}
}

void BaseLogger::SetLevel(int32_t level) {
	LOCK(&_lock);
	if (_pLogger == NULL)
		return;

	FOR_VECTOR(_pLogger->_logLocations, i) {
		_pLogger->_logLocations[i]->SetLevel(level);
	}
}

string BaseLogger::LevelToString(int32_t level) {
    string result;

    switch (level) {
	case _DEBUG_:
	    result = "DEBUG";
	    break;
	case _ERROR_:
	    result = "ERROR";
	    break;
	case _FATAL_:
	    result = "FATAL";
	    break;
	case _FINEST_:
	    result = "FINEST";
	    break;
	case _FINE_:
	    result = "FINE";
	    break;
	case _INFO_:
	    result = "INFO";
	    break;
	case _WARNING_:
	    result = "WARN";
	    break;
	default:
	    result = "UNKNOWN";
    }

    return result;
}

int BaseLogger::GetLevel() {
    if (_pLogger == NULL)
        return -1;

    FOR_VECTOR(_pLogger->_logLocations, i) {
        return _pLogger->_logLocations[i]->GetLevel();
    }

    return -1;
}