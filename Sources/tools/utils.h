#ifndef UTILS_H
#define UTILS_H

#include <QDateTime>
#include <QString>

class Utils
{
public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    static QString dateToString(QDateTime date);
};

#endif // UTILS_H
