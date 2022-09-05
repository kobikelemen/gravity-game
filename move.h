#ifndef MOVE_H
#define MOVE_H

struct Move
{
    bool left;
    bool right;
    bool up;
    bool space;
    bool a;
    Move(bool l, bool r, bool u, bool s, bool a_) : left{l}, right{r}, up{u}, space{s} , a{a_}{};
    Move() : left{false}, right{false}, up{false}, space{false}, a{false} {};
};
#endif