#pragma once
#include <cstdint>
#include <initializer_list>

enum Action: uint8_t {
    SHOOT_SELF = 0,
    SHOOT_OTHER
};

static const std::initializer_list<Action> ActionList{
        SHOOT_SELF,
        SHOOT_OTHER
};

enum TurnEnum {
    PLAYER, DAEMON
};

enum BulletType: uint8_t {
    LIVE = 0,
    BLANK
};