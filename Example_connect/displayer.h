#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QObject>

class displayer : public QObject
{
    Q_OBJECT
public:
    explicit displayer(QObject *parent = nullptr);

public slots:
    void valueChanged(int newValue);

signals:
};

#endif // DISPLAYER_H
