#include "utils.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

QString Utils::dateToString(QDateTime date)
{
    return date.toString("yyyy-MM-dd");
}

TimeSpan Utils::stringToTime(QString date)
{
    QList<QString> list = date.split(":");

    int day = list.at(0).toInt();
    int hour = list.at(1).toInt();
    int minute = list.at(2).toInt();

    return TimeSpan::fromDays(day)
            .add(TimeSpan::fromHours(hour))
            .add(TimeSpan::fromMinutes(minute));
}
