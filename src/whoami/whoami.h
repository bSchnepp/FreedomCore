#ifndef _FREEDOM_CORE_WHOAMI_H_
#define _FREEDOM_CORE_WHOAMI_H_
#include <abstract.h>

#ifdef __POSIX_SYS

#define GET_USERNAME_MACRO	\
	register struct passwd* pw;	\
	register uid_t uid = geteuid();	\
	int c;	\
	pw = getpwuid(uid);

#define GET_USERNAME_AS_STRING	pw->pw_name

#else

#include <waypoint/user.h>
#define GET_USERNAME_MACRO	char* username = GetCurrentRunningUserName(); int pw = 1;
#define GET_USERNAME_AS_STRING        username;

#endif
#endif
