#if defined(__unix__) || defined(__unix)
#include <unistd.h>
#define GetWorkingDirectory getcwd
#else
#include <waypoint.h>
#define GetWorkingDirectory RetrieveDirectory
#endif
