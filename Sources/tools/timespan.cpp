#include "timespan.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TimeSpan::TimeSpan() : totalSeconds(0)
{
}

TimeSpan::TimeSpan(int seconds) : totalSeconds(seconds)
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

double TimeSpan::totalMinutes() const
{
    return this->totalSeconds / 60.;
}

double TimeSpan::totalHours() const
{
    return this->totalMinutes() / 60.;
}

double TimeSpan::totalDays() const
{
    return this->totalHours() / 24.;
}

TimeSpan TimeSpan::add(const TimeSpan ts)
{
    this->totalSeconds += ts.totalSeconds;

    return *this;
}

TimeSpan TimeSpan::substract(const TimeSpan ts)
{
    this->totalSeconds -= ts.totalSeconds;

    return *this;
}

QString TimeSpan::toString() const
{
    /*TimeSpan ts = TimeSpan::fromMinutes(this->totalMinutes());
    int days = ts.totalDays();
    ts.substract(days*60*60*24);
    int hours = ts.totalHours();
    ts.substract(hours*60*60);
    //int minutes = ts.totalMinutes();*/

    int minutes = (int)(this->totalSeconds / 60) % 60;
    int hours = (int)(this->totalSeconds / 3600) % 24;
    int days = (int)(this->totalSeconds / 86400);

    return QString("%1:%2:%3").arg(QString::number(days), QString::number(hours), QString::number(minutes));
}

TimeSpan TimeSpan::fromMinutes(int minutes)
{
    return TimeSpan(minutes * 60);
}

TimeSpan TimeSpan::fromHours(int hours)
{
    return TimeSpan::fromMinutes(hours * 60);
}

TimeSpan TimeSpan::fromDays(int days)
{
    return TimeSpan::fromHours(days * 24);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                         OPERATORS OVERLOAD                        *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TimeSpan operator-(TimeSpan const &ts1, TimeSpan const &ts2)
{
    double diffSeconds = ts1.totalSeconds - ts2.totalSeconds;

    return TimeSpan(diffSeconds);
}
