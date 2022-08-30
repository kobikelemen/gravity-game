#ifndef MESSAGE_H
#define MESSAGE_H


#include <utility>
#include <vector>
#include <stdint.h>
#include <iostream>
#include "../game.h"


struct projectile_state
{
    float posx;
    float posy;
    float velx;
    float vely;
    projectile_state(float px, float py, float vx, float vy);
    projectile_state();

};


struct pos
{
    float x;
    float y;
    pos(float _x, float _y);
    pos();
};


struct game_state
{
    pos planet_pos;
    pos player1_pos;
    pos player2_pos;
    // projectile_state projectiles[];
    std::vector<projectile_state> projectiles;
    game_state();
};




struct message_header
{
    float size;
    int id;
};



class GamestateMessage
{

    void serialize(game_state state);
    void deserialize(std::vector<float> buffer);
    game_state gstate;

public:
    GamestateMessage(game_state state);
    GamestateMessage(std::vector<float> buffer);

    message_header header;
    std::vector<float> body;
    game_state get_game_state();

};




class ControlMessage
{
    void serialize(Move control_input);
    void deserialize(std::vector<int> buffer);
    Move controls;

public:
    ControlMessage(Move control_input);
    ControlMessage(std::vector<int> buffer);

    message_header header;
    std::vector<int> body;
    Move get_controls();
};

#endif