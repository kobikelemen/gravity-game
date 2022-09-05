#include "networking/threadsafe_queue.h"
#include "networking/message.h"

int main()
{
    tsQueue<GamestateMessage> q;
    game_state state;
    state.player1_state = player_state(1.f,1.f);
    state.player2_state = player_state(2.f,2.f);
    state.projectiles.push_back(projectile_state(5.f,5.f,6.f,6.f));
    GamestateMessage msg(state);
    q.push_back(msg);
    
}