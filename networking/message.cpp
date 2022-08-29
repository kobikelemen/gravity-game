
#include "message.h"



projectile_state::projectile_state(int32_t px, int32_t py, int32_t vx, int32_t vy) 
{
    posx = px;
    posy = py;
    velx = vx;
    vely = vy;
}


pos::pos(int32_t _x, int32_t _y) 
{
    x = _x;
    y = _y;
}

pos::pos()
{

}

game_state::game_state()
{

}


Message::Message(game_state state)
{
    serialize(state);
}


Message::Message(std::vector<char> buffer)
{
    deserialize(buffer);
}


void Message::serialize(game_state state)
{
    body.push_back(state.planet_pos.x);
    body.push_back(state.planet_pos.y);
    body.push_back(state.player1_pos.x);
    body.push_back(state.player1_pos.y);
    body.push_back(state.player2_pos.x);
    body.push_back(state.player2_pos.y);
    body.push_back(state.projectiles.size());
    for (projectile_state &proj : state.projectiles) {
        body.push_back(proj.posx);
        body.push_back(proj.posy);
        body.push_back(proj.velx);
        body.push_back(proj.vely);
    }

    
    
    // size_t i = body.size();
    // size_t pos_size = sizeof(pos);

    // body.resize(body.size() + sizeof(state));
    
    // std::memcpy(body.data() + i, &state.planet_pos.x, sizeof(int32_t));
    // std::memcpy(body.data() + i + sizeof(int32_t), &state.planet_pos.y, sizeof(int32_t));
    // std::memcpy(body.data() + i + pos_size, &state.player1_pos, pos_size);
    // std::memcpy(body.data() + i + 2*pos_size, &state.player2_pos, pos_size);
    // std::memcpy(body.data() + i + 3*pos_size, state.projectiles.data(), state.projectiles.size());
    header.size = body.size();
    header.id = 1;
}


void Message::deserialize(std::vector<char> buffer)
{

}