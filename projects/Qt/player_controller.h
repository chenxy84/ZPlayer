#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>

#include "IJKMediaPlayer/ijkplayer_controller.h"

class PlayerController : public QObject
{
    Q_OBJECT
public:
    explicit PlayerController(QObject *parent = nullptr);
    virtual ~PlayerController();


public:
    void Start(std::string url);
    void Stop();
    
    void Play();
    void Pause();
    
    void Seek(long ts);

signals:


private:
    IJKMediaPlayerController* mpc_;

};

#endif // PLAYERCONTROLLER_H
