#include "utils.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

QString Utils::dateFormat()
{
    return "dd/MM/yyyy";
}

QString Utils::dateRegex()
{
    return "(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(2[0-1][0-9][0-9])";
}

QString Utils::dateToString(QDateTime date)
{
    return date.toString(Utils::dateFormat());
}

QString Utils::timeFormat()
{
    return "dd:HH:mm";
}

QString Utils::timeRegex()
{
    return "((0[0-9]|1[0-9]|2[0-9]|3[0-1]):([0-1][0-9]|2[0-4]):([0-5][0-9]|6[0]))";
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
