#ifndef ZPLAYER_H
#define ZPLAYER_H

#include <iostream>
#include <string>
#include <ctype.h>

class ZPlayer {
  private:
    std::string url_;
    int duration_;
    bool is_playing_;
    int main_volume_;
    bool loop_;

  public:
    ZPlayer();
    ~ZPlayer();
    void Play();
    void Pause();
    void Stop();
    void Seek(int seconds);
    int GetDuration();
    bool GetPlayingStatus();
    void SetMainVolume(int vol);
    void SetLoop(bool loop);
};

#endif
