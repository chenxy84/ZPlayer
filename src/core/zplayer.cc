#include "ZPlayer.h"

ZPlayer::ZPlayer() {
  mediaUrl = "";
  durationInMS = 0;
  isPlaying = false;
  volume = 1.0f;
  loop = false;
}

ZPlayer::~ZPlayer() {

}

void ZPlayer::play() {
  if (!isPlaying) {
    isPlaying = true;
    std::cout << "Playing " << mediaUrl << std::endl;
  } else {
    std::cout << "Media is already playing!" << std::endl;
  }
}

void ZPlayer::pause() {
  if (isPlaying) {
    isPlaying = false;
    std::cout << "Paused " << mediaUrl << std::endl;
  } else {
    std::cout << "Media is already paused!" << std::endl;
  }
}

void ZPlayer::stop() {
  if (isPlaying) {
    isPlaying = false;
    std::cout << "Stopped " << mediaUrl << std::endl;
  } else {
    std::cout << "Media is already stopped!" << std::endl;
  }
}

void ZPlayer::seek(int seconds) {
  std::cout << "Seeking " << seconds << " seconds into " << mediaUrl << std::endl;
  // Code for seeking to the specified time in the media
}

int ZPlayer::getDuration() {
  return durationInSeconds;
}

bool ZPlayer::getPlayingStatus() {
  return isPlaying;
}

void ZPlayer::setVolume(int vol) {
  volume = vol;
  std::cout << "Set volume to " << volume << std::endl;
}

void ZPlayer::setLoop(bool loopStatus) {
  loop = loopStatus;
  std::cout << "Set loop to " << loop << std::endl;
}
