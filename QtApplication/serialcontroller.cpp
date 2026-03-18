#include "serialcontroller.h"

SerialController::SerialController(QObject *parent, const QString &portName, int baud)
    : QObject(parent), m_baudRate(baud)
{
    serial = new QSerialPort(this);


    bool found = false;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(info.vendorIdentifier() == 0x2341 || info.vendorIdentifier() == 0x1A86 || info.vendorIdentifier() == 0x0403)
        {
            m_portName = info.portName();
            found = true;
            qDebug() << "Arduino détecté sur le port:" << m_portName;
            break;
        }
    }

    if(!found)
    {
        qDebug() << "Aucun Arduino détecté automatiquement. Utilisation du port par défaut:" << portName;
        m_portName = portName;
    }

    serial->setPortName(m_portName);
    serial->setBaudRate(m_baudRate);

    connect(serial, &QSerialPort::readyRead, this, &SerialController::readData);
}

SerialController::~SerialController()
{
    closePort();
}

void SerialController::openPort()
{
    if(!serial->open(QIODevice::ReadWrite))
        qWarning() << "Failed to open port" << m_portName << ":" << serial->errorString();
    else
        qDebug() << "Serial port opened:" << m_portName;
}

void SerialController::closePort()
{
    if(serial->isOpen())
        serial->close();
}

// -----------------------
// Lecture série avec resynchronisation
// -----------------------
void SerialController::readData()
{
    buffer.append(serial->readAll());

    while(buffer.size() > 0)
    {
        int startIdx = buffer.indexOf('$');
        if(startIdx == -1)
        {
            buffer.clear();
            break;
        }

        if(buffer.size() < startIdx + 9)
            break;

        if(buffer[startIdx + 8] == '#')
        {
            QByteArray frame = buffer.mid(startIdx, 9);
            buffer.remove(0, startIdx + 9);
            // qDebug() << "Trame reçue OK:" << frame.toHex(' ').toUpper();
            parseCommand(frame);
        }
        else
        {
            buffer.remove(0, startIdx + 1);
        }
    }
}

// -----------------------
// Parsing trame
// -----------------------
void SerialController::parseCommand(const QByteArray &data)
{
    if(data.size() != 9 || data.at(0) != '$' || data.at(8) != '#')
        return;

    quint8 munition = static_cast<quint8>(data.at(1));
    quint8 joystickY = static_cast<quint8>(data.at(2));
    quint8 joystickX = static_cast<quint8>(data.at(3));
    quint8 bouton1 = static_cast<quint8>(data.at(4)&(1<<0));
    quint8 bouton2 = static_cast<quint8>(data.at(4)&(1<<1));
    quint8 boutonEncodeur = static_cast<quint8>(data.at(4)&(1<<2));
    quint8 boutonJoy = static_cast<quint8>(data.at(4)&(1<<3));
    quint8 encodeur = static_cast<quint8>(data.at(5));
    quint8 cursorX = static_cast<quint8>(data.at(6));
    quint8 cursorY = static_cast<quint8>(data.at(7));

    emit shoot(bouton1 != 0);
    if(bouton2 != 0)
        emit reload();
    emit boutonEncodeurPressed(boutonEncodeur != 0);

    emit updateCursor(cursorX, cursorY);
    emit updateMunition(munition);
    emit updateEncodeur(encodeur);

    emit moveBack(joystickY > 150);
    emit moveFront(joystickY < 100);
    emit moveLeft(joystickX > 150);
    emit moveRight(joystickX < 100);
}
