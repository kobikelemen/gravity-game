#include <iostream>
// #include "message.h"
#include "threadsafe_queue.h"


int main()
{
    // game_state state;
    // state.planet_pos = pos(1,1);
    // state.player1_pos = pos(2,2);
    // state.player2_pos = pos(3,3);
    // state.projectiles.push_back(projectile_state(4,4,4,4));

    // Message msg(state);
    // std::cout << "msg body: ";
    // for (int i=0; i < msg.body.size(); i ++) {
    //     std::cout << msg.body[i] << " ";
    // }
    // Message m(msg.body);
    // game_state gs = m.get_game_state();
    // std::cout << "\n\ngame state:" << std::endl;
    // std::cout << gs.planet_pos.x << " " << gs.planet_pos.y << " " << gs.player1_pos.x << std::endl;
    tsQueue<Message> ts_queue;

}