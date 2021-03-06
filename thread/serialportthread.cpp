#include "serialportthread.h"
#include "qdebug.h"
#include "parser/protocal.h"

SerialPortThread *SerialPortThread::s_instance = NULL;

SerialPortThread::SerialPortThread(QObject *parent)
    : QThread(parent)
{
    m_isStopped = true;
    m_isSettingsChanged = false;
}

SerialPortThread::~SerialPortThread()
{
    wait();
}


SerialPortThread* SerialPortThread::getInstance()
{
    if(!s_instance)
    {
        s_instance = new SerialPortThread();
    }
    return s_instance;
}

void SerialPortThread::mStart(SerialPortSettingsDialog::Settings __settings)
{
    m_serialPortMutex.lock();
    m_isStopped = false;
    m_serialPortMutex.unlock();

    mSet(__settings);

    if (!this->isRunning())
        this->start();
}

void SerialPortThread::mStop()
{
    m_serialPortMutex.lock();
    m_isStopped = true;
    m_serialPortMutex.unlock();
}

void SerialPortThread::mSet(SerialPortSettingsDialog::Settings __settings)
{
    m_serialPortMutex.lock();
    m_currentSettings = __settings;
    m_serialPortMutex.unlock();

    m_serialPortMutex.lock();
    m_isSettingsChanged = true;
    m_serialPortMutex.unlock();
}

void SerialPortThread::mSendData(QByteArray __data)
{
    m_serialPortMutex.lock();
    m_dataToSend.append(__data);
    m_serialPortMutex.unlock();
}

void SerialPortThread::run()
{
    bool __isStopped = true;
    m_serialPortMutex.lock();
    __isStopped = m_isStopped;
    m_serialPortMutex.unlock();

    qDebug("thread running");

    SerialPortSettingsDialog::Settings __mSettings;
    bool __isSettingsChanged = false;
    QByteArray __dataToSend;
    unsigned char rx_buffer[256];
    while(!__isStopped)
    {
        m_serialPortMutex.lock();
        __isSettingsChanged = m_isSettingsChanged;
        m_serialPortMutex.unlock();
        if(__isSettingsChanged){
            if(serial.isOpen()){
                serial.close();
            }

            m_serialPortMutex.lock();
            __mSettings = m_currentSettings;
            m_serialPortMutex.unlock();
            serial.setPortName(__mSettings.name);
            serial.setBaudRate(__mSettings.baudRate);
            serial.setDataBits(__mSettings.dataBits);
            serial.setParity(__mSettings.parity);
            serial.setStopBits(__mSettings.stopBits);
            serial.setFlowControl(__mSettings.flowControl);
            emit message("settings changed !");
        }//settings changed

        if(!serial.isOpen()){

            if(serial.open(QIODevice::ReadWrite)){
                emit message("open successfully !");
            }
            else{
                m_serialPortMutex.lock();
                m_isStopped = true;
                m_serialPortMutex.unlock();
                emit message("open failed !");
                break;
            }
        }//if not open , while loop break

        /*=== opened , processing data here ===*/
        m_serialPortMutex.lock();
        if(!m_dataToSend.isEmpty()){
            __dataToSend.append(m_dataToSend);
            m_dataToSend.clear();
        }
        m_serialPortMutex.unlock();

        if(! __dataToSend.isEmpty()){
            if(serial.write(__dataToSend) > 0){
                if (serial.waitForBytesWritten(100) == true) {
                    qDebug() <<"write successfully !";
                    __dataToSend.clear();
                }
                else
                    qDebug() <<"write time out !";
            }
        }

        if (serial.waitForReadyRead(100)) {
            m_dataReceived = serial.readAll();
            while (serial.waitForReadyRead(10))
                m_dataReceived += serial.readAll();
        }
        //unpack the data received
        if(m_dataReceived.size() > 0){

            for(int i = 0; i < m_dataReceived.size(); i ++){

                if(FrameUnpack(m_dataReceived.at(i),rx_buffer)){

                    tHeader* pHeader = (tHeader*)rx_buffer;
                    if( pHeader->cmd  == CMD_ID_SENSOR_INFO){

                 //       Cmd_Data *pData = (Cmd_Data *)&rx_buffer[sizeof(tHeader)];//

                    }
                    else{

                    }
                }
            }
        }//unpack code end

        /*=== processing data end           ===*/

        m_serialPortMutex.lock();
        __isStopped = m_isStopped;
        m_serialPortMutex.unlock();
    }//while loop end

    if(serial.isOpen()){
        serial.close();
    }

    qDebug("thread exit");
}
