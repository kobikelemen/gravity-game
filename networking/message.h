
#include <utility>
#include <vector>
#include <stdint.h>

struct projectile_state
{
    float posx;
    float posy;
    float velx;
    float vely;
};


struct pos
{
    float x;
    float y;
};


struct game_state
{
    pos planet_pos[];
    pos player1_pos;
    pos player2_pos;
    projectile_state projectiles[];
};


struct message_header
{
    uint_32 size;
    int id;
};



class Message
{

    void serialize(game_state state);
public:
    Message(game_state state);

    message_header header;
    std::vector<uint_8> body;

};