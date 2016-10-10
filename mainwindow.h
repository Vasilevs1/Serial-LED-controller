#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMainWindow>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduinoUno_ProductID = 67;
    static const quint16 arduinoUno_VendorID = 9025;
    bool arduinoIsAvailable;
    QString arduino_Portname;

private slots:
    //void changeLed();
    void led();
    void updateRed(int red);
    void updateGreen(int green);
    void updateBlue(int blue);
};

#endif // MAINWINDOW_H
