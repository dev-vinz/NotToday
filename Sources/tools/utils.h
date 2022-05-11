#ifndef UTILS_H
#define UTILS_H

#include <QDateTime>
#include <QList>
#include <QString>

#include "timespan.h"

class Utils
{
public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    static QString dateToString(QDateTime date);
    static TimeSpan stringToTime(QString date);
};

#endif // UTILS_H
