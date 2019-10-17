#ifndef SPREFERENCES_H
#define SPREFERENCES_H

#include <Constants.h>
#include <stdint.h>

namespace SSw
{

struct SPreferences
{
    SPreferences() : width(DEFAULT_HEIGHT),
                     height(DEFAULT_WIDTH),
                     sheep(DEFAULT_SHEEP),
                     level(DEFAULT_LEVEL),
                     perso(DEFAULT_CHECK_BOX_PERSO)
    {}

    int32_t width;
    int32_t height;
    int32_t sheep;
    int32_t level;
    bool perso;

};

} // namespace SSw

#endif // SPREFERENCES_H

