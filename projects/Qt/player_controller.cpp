#include "player_controller.h"
#include <iostream>

PlayerController::PlayerController(QObject *parent)
    : QObject{parent}
{
    mpc_ = new IJKMediaPlayerController();
}

PlayerController::~PlayerController() {

}


void PlayerController::Start(std::string url) {
    std::cout<<"player start" << std::endl;
    mpc_->SetSource(url);
    mpc_->Prepare();
}


void PlayerController::Stop() {
    std::cout<<"player stop" << std::endl;
}
