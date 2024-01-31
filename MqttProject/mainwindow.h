#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "publisher.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonConnect_clicked();
    void clientConnected();
    void clientDissconted();
    void on_buttonSubscribe_clicked();
    void on_buttonPublish_clicked();
    void publishMessageRecived(QByteArray data);

private:
    Ui::MainWindow *ui;
    publisher *publisherObject;
};
#endif // MAINWINDOW_H
