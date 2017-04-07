#if defined(__unix__) || defined(__unix)
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <regex.h>
#define GetWorkingDirectory getcwd
#define CreateDirectory mkdir
#define FileSize_t off_t
#define __POSIX_SYS
#define OperatingSystem "POSIX_OS"

#else	//Not porting to Windows. If you want to, go ahead. Too much work and effort for something not serious.
#include <waypoint.h>
#include <waypoint/sys_utils.h>
#include <waypoint/lang/regex.h>
#define GetWorkingDirectory RetrieveDirectory
#define OperatingSystem "Waypoint"
#define __WAYPOINT
#endif





#if defined(__i386__)
#define CPUArch 0
#elif defined(__x86_64__) || defined(__amd64__)
#define CPUArch 1
#endif

