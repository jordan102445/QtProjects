#include "counter.h"
#include <QDebug>

Counter::Counter(QObject *parent)
    : QObject{parent}
{}

void Counter::changeValue(int value)
{
    if (value != m_value) {
        m_value = value;
        emit setValue(value);
    }
}

void Counter::valueChanged(int newValue)
{
    qDebug() << "New value " << newValue;
}
