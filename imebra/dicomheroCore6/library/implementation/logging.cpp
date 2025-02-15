#include "logging.h"
#include <array>
#include <ctime>

#ifdef DICOMHERO_WINDOWS
#include <time.h>
#endif
namespace dicomhero
{

namespace implementation
{

std::string getCurrentTime()
{
    time_t rawTime;
    time (&rawTime);

    struct tm timeInfo;

#ifdef DICOMHERO_WINDOWS
    ::localtime_s(&timeInfo, &rawTime);
#else
    ::localtime_r (&rawTime, &timeInfo);
#endif

    std::array<char, 128> buffer;
    size_t requiredSize = strftime(buffer.data(), buffer.size(), "%F %T ", &timeInfo);

    if(requiredSize == 0)
    {
        return "Unknown time";
    }

    return std::string(buffer.data());
}

}


}
