#include <QCoreApplication>
#include <QObject>
#include "counter.h"
#include "displayer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Counter aCounter, bCounter;
    displayer disp;

    // Connect signals and slots within the main function
    QObject::connect(&aCounter, &Counter::setValue, [](int value){
        qDebug() << "New value " << value;
    }); // lambda init

    QObject::connect(&aCounter,&Counter::setValue,&bCounter, &Counter::valueChanged);


    aCounter.changeValue(48);  // a.value() == 12, b.value() == 12
    bCounter.changeValue(48);  // a.value() == 12, b.value() == 48

    // You might want to use QCoreApplication::processEvents()
    // to process events if needed

    return a.exec();
}
