#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ijksdl/ijksdl_aout.h"
SDL_Aout *SDL_Aout_Qt_Create();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <math.h>
#include <QAudioSink>
#include <QByteArray>
#include <QComboBox>
#include <QIODevice>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QScopedPointer>
#include <QMediaDevices>
#include <QThread>
class AudioDataProvider: public QIODevice
{
    Q_OBJECT
public:
    AudioDataProvider(const QAudioFormat &format, qint64 durationUs, int sampleRate);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;
    qint64 size() const override { return m_buffer.size(); }

private:
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 m_pos = 0;
    QByteArray m_buffer;
};

class MyAudioThread: public QThread {
    Q_OBJECT
public:
    explicit MyAudioThread(SDL_Aout *aout, const QAudioFormat &format, QObject *parent = nullptr);
    
protected:
    virtual void run() Q_DECL_OVERRIDE;
 
private:
    SDL_Aout *aout_;
    QAudioFormat format_;
};

#endif
