
#include "message.h"



player_state::player_state(float _x, float _y, float ang)
{
    x = _x;
    y = _y;
    angle = ang;
}


player_state::player_state()
{

}


projectile_state::projectile_state(float px, float py, float vx, float vy) 
{
    posx = px;
    posy = py;
    velx = vx;
    vely = vy;
}


projectile_state::projectile_state()
{

}

game_state::game_state()
{

}


GamestateMessage::GamestateMessage(game_state state)
{
    serialize(state);
    gstate = state;
}


GamestateMessage::GamestateMessage(std::vector<float> buffer)
{
    deserialize(buffer);
}


void GamestateMessage::serialize(game_state state)
{
    
    // header.id = 1;
    body.push_back(header.size);
    body.push_back(state.player1_state.x);
    body.push_back(state.player1_state.y);
    body.push_back(state.player1_state.angle);

    body.push_back(state.player2_state.x);
    body.push_back(state.player2_state.y);
    body.push_back(state.player2_state.angle);

    body.push_back(state.projectiles.size());
    for (projectile_state &proj : state.projectiles) {
        body.push_back(proj.posx);
        body.push_back(proj.posy);
        body.push_back(proj.velx);
        body.push_back(proj.vely);
    }
    header.size = body.size();
    body.insert(body.begin(), header.size);
    std::cout << "size " << header.size << std::endl;
}


void GamestateMessage::deserialize(std::vector<float> buffer)
{   
    game_state state;
    // int size = static_cast<int>(buffer[1]);
    int size = (int)buffer[0];
    // state.planet_pos.x = buffer[1];
    // state.planet_pos.y = buffer[2];
    state.player1_state.x = buffer[2];
    state.player1_state.y = buffer[3];
    state.player1_state.angle = buffer[4];
    state.player2_state.x = buffer[5];
    state.player2_state.y = buffer[6];
    state.player2_state.angle = buffer[7];
    std::cout << " size " << size << std::endl;
    for (int i=8; i < size; i +=4) {
        
        state.projectiles.push_back(projectile_state(buffer[i], buffer[i+1], buffer[i+2], buffer[i+3]));
    }
    gstate = state;
}


game_state GamestateMessage::get_game_state()
{
    return gstate;
}




ControlMessage::ControlMessage(Move control_input)
{
    serialize(control_input);
}

ControlMessage::ControlMessage(std::vector<int> buffer)
{
    deserialize(buffer);
}

void ControlMessage::serialize(Move control_input)
{

    header.size = body.size();
    
    body.push_back(static_cast<int>(header.size));
    body.push_back(static_cast<int>(control_input.left));
    body.push_back(static_cast<int>(control_input.right));
    body.push_back(static_cast<int>(control_input.up));
    body.push_back(static_cast<int>(control_input.space));
    body.push_back(static_cast<int>(control_input.a));
    body.push_back(-1);
}

void ControlMessage::deserialize(std::vector<int> buffer)
{
    Move control;
    int size = buffer[0];
    control.left = buffer[1];
    control.right = buffer[2];
    control.up = buffer[3];
    control.space = buffer[4];
    control.a = buffer[5];
    controls = control;
}

Move ControlMessage::get_controls()
{
    return controls;
}