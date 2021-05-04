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

#ifdef SOLARIS
#ifndef _SOLARISPLATFORM_H
#define _SOLARISPLATFORM_H

#include "platform/baseplatform.h"

#ifndef PRIz
#define PRIz "z"
#endif /* PRIz */


//platform includes
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <algorithm>
#include <arpa/inet.h>
#include <assert.h>
#include <cctype>
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <list>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <vector>
#include <queue>
#include <sys/wait.h>
#include <limits.h>
#include <spawn.h>
#include <time.h>
#include <syslog.h>
using namespace std;


//platform defines
#define DLLEXP
#define EMS_RESTRICT __restrict__
#define HAS_MMAP 1
#define COLOR_TYPE const char *
#define FATAL_COLOR "\033[01;31m"
#define ERROR_COLOR "\033[22;31m"
#define WARNING_COLOR "\033[01;33m"
#define INFO_COLOR "\033[22;36m"
#define DEBUG_COLOR "\033[01;37m"
#define FINE_COLOR "\033[22;37m"
#define FINEST_COLOR "\033[22;37m"
#define NORMAL_COLOR "\033[0m"
#define SET_CONSOLE_TEXT_COLOR(color) fprintf(stdout,"%s",color)
#define READ_FD read
#define WRITE_FD write

//threading: mutex
#define THREADING_PTHREAD
#define MUTEX_TYPE pthread_mutex_t
#define MUTEX_INIT pthread_mutex_init
#define MUTEX_STATIC_INIT PTHREAD_MUTEX_INITIALIZER
#define MUTEX_DESTROY pthread_mutex_destroy
#define MUTEX_LOCK pthread_mutex_lock
#define MUTEX_UNLOCK pthread_mutex_unlock

#define SOCKET int32_t
#define SOCKET_TYPE SOCKET
#define LASTSOCKETERROR					errno
#define SOCKERROR_EINPROGRESS			EINPROGRESS
#define SOCKERROR_EAGAIN				EAGAIN
#define SOCKERROR_EWOULDBLOCK			EWOULDBLOCK
#define SOCKERROR_ECONNRESET			ECONNRESET
#define SOCKERROR_ENOBUFS				ENOBUFS
#define SOCKET_LAST_ERROR			LASTSOCKETERROR
#define SOCKET_ERROR_EINPROGRESS			SOCKERROR_EINPROGRESS
#define SOCKET_ERROR_EAGAIN				SOCKERROR_EAGAIN
#define SOCKET_ERROR_EWOULDBLOCK			SOCKERROR_EWOULDBLOCK
#define SOCKET_ERROR_ECONNRESET			SOCKERROR_ECONNRESET
#define SOCKET_ERROR_ENOBUFS				SOCKERROR_ENOBUFS
#define LIB_HANDLER void *
#define FREE_LIBRARY(libHandler) dlclose((libHandler))
#define LOAD_LIBRARY(file,flags) dlopen((file), (flags))
#define LOAD_LIBRARY_FLAGS RTLD_NOW | RTLD_LOCAL
#define OPEN_LIBRARY_ERROR STR(string(dlerror()))
#define GET_PROC_ADDRESS(libHandler, procName) dlsym((libHandler), (procName))
#define LIBRARY_NAME_PATTERN "lib%s.so"
#define PATH_SEPARATOR '/'
#define CLOSE_SOCKET(fd) if((fd)>=0) close((fd))
#define InitNetworking()
#define MAP_NOCACHE 0
#define MAP_NOEXTEND 0
#define MAP_FILE 0
#define FD_READ_CHUNK 32768
#define FD_WRITE_CHUNK FD_READ_CHUNK
#define SO_NOSIGPIPE 0
#define SET_UNKNOWN 0
#define SET_READ 1
#define SET_WRITE 2
#define SET_TIMER 3
#define FD_READ_CHUNK 32768
#define FD_WRITE_CHUNK FD_READ_CHUNK
#define RESET_TIMER(timer,sec,usec) timer.tv_sec=sec;timer.tv_usec=usec;
#define FD_COPY(src,dst) memcpy(dst,src,sizeof(fd_set));
#define MSG_NOSIGNAL 0
#define SRAND() srand(time(NULL));
#define Timestamp struct tm
#define Timestamp_init {0, 0, 0, 0, 0, 0, 0, 0, 0}
#define PIOFFT off_t
#define GetPid getpid
#define PutEnv putenv
#define TzSet tzset
#define Chmod chmod

#define CLOCKS_PER_SECOND 1000000L
#define GETCLOCKS(result,type) \
do { \
    struct timeval ___timer___; \
    gettimeofday(&___timer___,NULL); \
    result=(type)___timer___.tv_sec*(type)CLOCKS_PER_SECOND+(type) ___timer___.tv_usec; \
}while(0);

#define GETMILLISECONDS(result) \
do { \
    struct timespec ___timer___; \
    clock_gettime(CLOCK_MONOTONIC, &___timer___); \
    result=(uint64_t)___timer___.tv_sec*1000+___timer___.tv_nsec/1000000; \
}while(0);

#define GETNTP(result) \
do { \
	struct timeval tv; \
	gettimeofday(&tv,NULL); \
	result=(((uint64_t)tv.tv_sec + 2208988800U)<<32)|((((uint32_t)tv.tv_usec) << 12) + (((uint32_t)tv.tv_usec) << 8) - ((((uint32_t)tv.tv_usec) * 1825) >> 5)); \
}while (0);

#define GETCUSTOMNTP(result,value) \
do { \
	struct timeval tv; \
	tv.tv_sec=(uint64_t)value/CLOCKS_PER_SECOND; \
	tv.tv_usec=(uint64_t)value-tv.tv_sec*CLOCKS_PER_SECOND; \
	result=(((uint64_t)tv.tv_sec + 2208988800U)<<32)|((((uint32_t)tv.tv_usec) << 12) + (((uint32_t)tv.tv_usec) << 8) - ((((uint32_t)tv.tv_usec) * 1825) >> 5)); \
}while (0);

class SolarisPlatform
: public BasePlatform {
public:
	SolarisPlatform();
	virtual ~SolarisPlatform();
};

typedef void (*SignalFnc)(void);

typedef struct _select_event {
	uint8_t type;
} select_event;

#define MSGHDR struct msghdr
#define IOVEC iovec
#define MSGHDR_MSG_IOV msg_iov
#define MSGHDR_MSG_IOVLEN msg_iovlen
#define MSGHDR_MSG_IOVLEN_TYPE int
#define MSGHDR_MSG_NAME msg_name
#define MSGHDR_MSG_NAMELEN msg_namelen
#define IOVEC_IOV_BASE iov_base
#define IOVEC_IOV_LEN iov_len
#define IOVEC_IOV_BASE_TYPE uint8_t
#define SENDMSG(s,msg,flags,sent) sendmsg(s,msg,flags)

#define ftell64 ftello64
#define fseek64 fseeko64

string GetEnvVariable(const char *pEnvVarName);
void replace(string &target, string search, string replacement);
bool fileExists(string path);
string lowerCase(string value);
string upperCase(string value);
string changeCase(string &value, bool lowerCase);
string tagToString(uint64_t tag);
bool setMaxFdCount(uint32_t &current, uint32_t &max);
bool enableCoreDumps();
bool setFdJoinMulticast(SOCKET sock, string bindIp, uint16_t bindPort, string ssmIp);
bool setFdCloseOnExec(int fd);
bool setFdNonBlock(SOCKET fd);
bool setFdNoSIGPIPE(SOCKET fd);
bool setFdKeepAlive(SOCKET fd, bool isUdp);
bool setFdNoNagle(SOCKET fd, bool isUdp);
bool setFdReuseAddress(SOCKET fd);
bool setFdTTL(SOCKET fd, uint8_t ttl);
bool setFdMulticastTTL(SOCKET fd, uint8_t ttl);
bool setFdTOS(SOCKET fd, uint8_t tos);
bool setFdMaxSndRcvBuff(SOCKET fd);
bool setFdOptions(SOCKET fd, bool isUdp);
void killProcess(pid_t pid);
bool deleteFile(string path);
bool deleteFolder(string path, bool force);
bool createFolder(string path, bool recursive);
string getHostByName(string name);
bool isNumeric(string value);
void split(string str, string separator, vector<string> &result);
uint64_t getTagMask(uint64_t tag);
string generateRandomString(uint32_t length);
void lTrim(string &value);
void rTrim(string &value);
void trim(string &value);
int8_t getCPUCount();
map<string, string> mapping(string str, string separator1, string separator2, bool trimStrings);
void splitFileName(string fileName, string &name, string &extension, char separator = '.');
double getFileModificationDate(string path);
string normalizePath(string base, string file);
bool listFolder(string path, vector<string> &result,
		bool normalizeAllPaths = true, bool includeFolders = false,
		bool recursive = true);
bool moveFile(string src, string dst);
bool isAbsolutePath(string &path);
void installSignal(int sig, SignalFnc pSignalFnc);
void installQuitSignal(SignalFnc pQuitSignalFnc);
void installConfRereadSignal(SignalFnc pConfRereadSignalFnc);
time_t timegm(struct tm *tm);
#define getutctime() time(NULL)
time_t getlocaltime();
time_t gettimeoffset();
void GetFinishedProcesses(vector<pid_t> &pids, bool &noMorePids);
bool LaunchProcess(string fullBinaryPath, vector<string> &arguments, vector<string> &envVars, pid_t &pid);
bool OpenSysLog(const string name);
void Syslog(int32_t level, const char *message, ...);
void CloseSysLog();
#endif /* _SOLARISPLATFORM_H */
#endif /* SOLARIS */

