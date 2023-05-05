#include "player_controller.h"
#include <iostream>
#include "IJKMediaPlayer/ijkplayer_controller.h"

PlayerController::PlayerController(QObject *parent)
    : QObject{parent}
{
    mpc_ = new IJKMediaPlayerController();
}

//PlayerController::~PlayerController() {
//    delete mpc_;
//}

void PlayerController::Start(std::string url) {
    mpc_->SetSource(url);
    mpc_->Prepare();
}

void PlayerController::Stop() {
    mpc_->Stop();
}

void PlayerController::Play() {
    mpc_->Play();
}

void PlayerController::Pause() {
    mpc_->Pause();
}

void PlayerController::Seek(long ts) {
    mpc_->Seek(ts);
}

void PlayerController::SetDisplayView(void *view) {
    mpc_->SetDisplayView(view);
}
