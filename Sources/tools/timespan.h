#ifndef TIMESPAN_H
#define TIMESPAN_H

#include <QDateTime>
#include <QString>

class TimeSpan
{
private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    float totalSeconds;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    TimeSpan(int seconds);

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    TimeSpan();

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    double totalMinutes() const;
    double totalHours() const;
    double totalDays() const;

    TimeSpan add(const TimeSpan);
    TimeSpan substract(const TimeSpan);

    QDateTime toDateTime() const;
    QString toString() const;

    static TimeSpan fromMinutes(int minutes);
    static TimeSpan fromHours(int hours);
    static TimeSpan fromDays(int days);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                         OPERATORS OVERLOAD                        *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    friend TimeSpan operator-(TimeSpan const &ts1, TimeSpan const &ts2);
    friend TimeSpan operator+(TimeSpan const &ts1, TimeSpan const &ts2);

    TimeSpan &operator-=(const TimeSpan &ts);
    TimeSpan &operator+=(const TimeSpan &ts);

    friend bool operator<(const TimeSpan &ts1, const TimeSpan &ts2);
    friend bool operator>(const TimeSpan &ts1, const TimeSpan &ts2);
    friend bool operator<=(const TimeSpan &ts1, const TimeSpan &ts2);
    friend bool operator>=(const TimeSpan &ts1, const TimeSpan &ts2);

    friend bool operator==(const TimeSpan &ts1, const TimeSpan &ts2);
    friend bool operator!=(const TimeSpan &ts1, const TimeSpan &ts2);
};

#endif // TIMESPAN_H
