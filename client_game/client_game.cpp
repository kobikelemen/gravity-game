#include "client_game.h"



ClientGame::ClientGame(Player *p, sf::Vector2f screen_dimensions) : Game(p, screen_dimensions)
{

}


void ClientGame::start_connection()
{
    client.start_connection();
}


void ClientGame::update_lasers()
{

}


void ClientGame::set_groundtruth_state(game_state state)
{
    player->set_posx(state.player2_state.x); // set as player2 because for server it's other way around
    player->set_posy(state.player2_state.y);
    player2->set_posx(state.player1_state.x);
    player2->set_posy(state.player2_state.y);

    clear_projectiles();
    for (projectile_state sproj : state.projectiles) {
        Projectile *proj = new Projectile(sproj.posx, sproj.posy, sproj.velx, sproj.vely, 5.f);
        projectiles.push_back(proj);
    }
}


game_state ClientGame::get_groundtruth_state()
{
    GamestateMessage msg = client.ts_queue.pop_back();
    client.ts_queue.clear();
    game_state gstate = msg.get_game_state();
    return gstate;
}


void ClientGame::send_controls(Move move)
{
    client.send_data(move);
}


void ClientGame::update()
{
    poll_events();

    game_state state = get_groundtruth_state();

    set_groundtruth_state(state);

    update_gravity_objects();

    update_lasers();

    Move move = check_keyboard();

    update_player(player, move);

    // update_player2(); // for now just do ground truth

    update_screen_pos();

    update_arrows(); 

    send_controls(move); 
}