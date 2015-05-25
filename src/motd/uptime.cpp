#include <stdexcept>
#include <boost/throw_exception.hpp>
#include "uptime.h"

#if defined(BOOST_WINDOWS)
#include <windows.h>
#elif defined(__linux__) || defined(__linux) || defined(linux)
#include <sys/sysinfo.h>
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#include <sys/sysctl.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
#include <time.h>
#endif

unsigned int Uptime::get_uptime()
{
#if defined(BOOST_WINDOWS)
    return GetTickCount() / 1000u;
#elif defined(__linux__) || defined(__linux) || defined(linux)
    struct sysinfo info;
    if (sysinfo(&info) != 0)
        BOOST_THROW_EXCEPTION(std::runtime_error("Could not acquire uptime"));
    return info.uptime;
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
	struct timeval boottime;
	std::size_t len = sizeof(boottime);
	int mib[2] = { CTL_KERN, KERN_BOOTTIME };
	if (sysctl(mib, 2, &boottime, &len, NULL, 0) < 0)
		BOOST_THROW_EXCEPTION(std::runtime_error("Could not acquire uptime"));
	return time(NULL) - boottime.tv_sec;
#elif (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)) && defined(CLOCK_UPTIME)
    struct timespec ts;
    if (clock_gettime(CLOCK_UPTIME, &ts) != 0)
        BOOST_THROW_EXCEPTION(std::runtime_error("Could not acquire uptime"));
    return ts.tv_sec;
#else
    return 0;
#endif
}