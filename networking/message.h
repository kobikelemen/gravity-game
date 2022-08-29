
#include <utility>
#include <vector>
#include <stdint.h>
#include <iostream>


struct projectile_state
{
    int32_t posx;
    int32_t posy;
    int32_t velx;
    int32_t vely;
    projectile_state(int32_t px, int32_t py, int32_t vx, int32_t vy);
    projectile_state();

};


struct pos
{
    int32_t x;
    int32_t y;
    pos(int32_t _x, int32_t _y);
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
    int32_t size;
    int id;
};



class Message
{

    void serialize(game_state state);
    void deserialize(std::vector<char> buffer);
public:
    Message(game_state state);
    Message(std::vector<char> buffer);

    message_header header;
    std::vector<int32_t> body;

};