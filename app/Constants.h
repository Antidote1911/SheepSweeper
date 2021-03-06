#ifndef CONSTANTS
#define CONSTANTS

#include <QString>

namespace SSw
{

// Global names
const QString APP               = "SheepSweeper";
const QString ORG               = "katecpp";

// Icon path
const QString SMALL_SHEEP_PATH      = ":/images/small_sheep.png";
const QString SMALL_RED_SHEEP_PATH  = ":/images/small_red_sheep.png";
const QString BIG_SHEEP_PATH        = ":/images/big_sheep.png";
const QString DISARMED_PATH         = ":/images/disarmed.png";
const QString DISARMED_RED_PATH     = ":/images/disarmed_red.png";
const QString QUESTION_PATH         = ":/images/question.png";
const QString SAD_FACE              = "://images/sad_32.png";
const QString NORMAL_FACE           = "://images/normal_32.png";
const QString FEAR_FACE             = "://images/fear_32.png";
const QString HAPPY_FACE            = "://images/happy_32.png";

// Icon size
const int32_t FIELD_SIZE        = 26;
const int32_t ICON_SIZE         = 16;

// Default game preferences
const bool    DEFAULT_CHECK_BOX_PERSO= false;
const int32_t DEFAULT_LEVEL        = 2;  //0,1,2,3,4,5
const int32_t DEFAULT_HEIGHT       = 10;
const int32_t DEFAULT_WIDTH        = 10;
const int32_t DEFAULT_SHEEP        = 10;

const int32_t MSG_TIMEOUT       = 5000;

const double MIN_DENSITY        = 0.05;
const double MAX_DENSITY        = 0.95;

} // namespace SSw

#endif // CONSTANTS

