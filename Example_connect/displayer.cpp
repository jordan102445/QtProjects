#include "displayer.h"
#include <QDebug>

displayer::displayer(QObject *parent)
    : QObject{parent}
{}

void displayer::valueChanged(int newValue)
{
    qDebug() << "Value changed: " << newValue;
}
