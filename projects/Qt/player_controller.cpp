#include "player_controller.h"
#include <iostream>

PlayerController::PlayerController(QObject *parent)
    : QObject{parent}
{

}

PlayerController::~PlayerController() {

}


void PlayerController::Start(std::string url) {
    std::cout<<"player start" << std::endl;
}


void PlayerController::Stop() {
    std::cout<<"player stop" << std::endl;
}
