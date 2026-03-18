#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class SerialController : public QObject
{
    Q_OBJECT
public:
    explicit SerialController(QObject *parent = nullptr, const QString &portName = "COM3", int baud = 9600);
    ~SerialController();

    void openPort();
    void closePort();

signals:
    void moveFront(bool active);
    void moveBack(bool active);
    void moveLeft(bool active);
    void moveRight(bool active);
    void rotateLeft(bool active);
    void rotateRight(bool active);
    void shoot(bool active);
    void reload();
    void updateCursor(int x, int y);
    void updateMunition(int count);
    void updateEncodeur(int count);
    void boutonEncodeurPressed(bool active);

private slots:
    void readData();

private:
    QSerialPort *serial;
    QString m_portName;
    int m_baudRate;
    QByteArray buffer;

    void parseCommand(const QByteArray &data);
};

#endif // SERIALCONTROLLER_H
