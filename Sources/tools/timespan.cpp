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

QDateTime TimeSpan::toDateTime() const
{
    return QDateTime::fromString(this->toString(), "dd:mm:hh");
}

QString TimeSpan::toString() const
{
    int minutes = (int)(this->totalSeconds / 60) % 60;
    int hours = (int)(this->totalSeconds / 3600) % 24;
    int days = (int)(this->totalSeconds / 86400);

    //Format each values
    QString day = QString("%1").arg(QString::number(days)).rightJustified(2,'0');
    QString hour = QString("%1").arg(QString::number(hours)).rightJustified(2,'0');
    QString minute = QString("%1").arg(QString::number(minutes)).rightJustified(2,'0');

    //format each values together
    return QString("%1:%2:%3").arg(day, hour, minute);
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

TimeSpan operator+(TimeSpan const &ts1, TimeSpan const &ts2)
{
    double totalSeconds = ts1.totalSeconds + ts2.totalSeconds;

    return TimeSpan(totalSeconds);
}

TimeSpan &TimeSpan::operator-=(const TimeSpan &ts)
{
    this->totalSeconds -= ts.totalSeconds;

    return *this;
}

TimeSpan &TimeSpan::operator+=(const TimeSpan &ts)
{
    this->totalSeconds += ts.totalSeconds;

    return *this;
}

bool operator<(const TimeSpan &ts1, const TimeSpan &ts2)
{
    return ts1.totalSeconds < ts2.totalSeconds;
}

bool operator>(const TimeSpan &ts1, const TimeSpan &ts2)
{
    return ts1.totalSeconds > ts2.totalSeconds;
}

bool operator<=(const TimeSpan &ts1, const TimeSpan &ts2)
{
    return !(ts1 > ts2);
}

bool operator>=(const TimeSpan &ts1, const TimeSpan &ts2)
{
    return !(ts1 < ts2);
}

bool operator==(const TimeSpan &ts1, const TimeSpan &ts2)
{
    return ts1.totalSeconds == ts2.totalSeconds;
}

bool operator!=(const TimeSpan &ts1, const TimeSpan &ts2)
{
    return !(ts1 == ts2);
}
