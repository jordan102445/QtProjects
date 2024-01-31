#ifndef COUNTER_H
#define COUNTER_H

#include "qtmetamacros.h"
#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = nullptr);

    int value() const { return m_value; };
    void changeValue(int value);
public slots:
    void valueChanged(int newValue);

signals:
    void setValue(int value);

private:
    int m_value;
};

#endif // COUNTER_H
