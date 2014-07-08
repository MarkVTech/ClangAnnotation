#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <QObject>

class Counter : public QObject
{
Q_OBJECT
public:
    Counter();
    explicit Counter(int initialValue=0);

    void incrementCount();
    void reset();
    int getCount() const;

    void printCount() const;

    int operator+(int i);

public slots:
    void add(int i);
    int substract(int i)
    {
        count_ -= i;
    }

signals:
    void sig1(int i);

private:
    int count_;
};

#endif
