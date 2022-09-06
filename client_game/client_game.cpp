#include "client_game.h"



ClientGame::ClientGame(Player *p, sf::Vector2f screen_dimensions, std::string win_name) : Game(p, screen_dimensions, win_name)
{

}


ClientGame::~ClientGame()
{
    delete context_thread;
    delete client;

}


void ClientGame::start_connection()
{
    std::cout << " 1 " << std::endl;
    client = new Client();
    std::cout << " 2 " << std::endl;
    client->start_connection();
    std::cout << " 3 " << std::endl;
    std::thread *context_thread = new std::thread([&]() { client->context.run(); });
    std::cout << " 4 " << std::endl;
}


void ClientGame::update_lasers()
{

}


void ClientGame::set_groundtruth_state(game_state state)
{
    player->set_posx(state.player2_state.x); // set as player2 because for server it's other way around
    player->set_posy(state.player2_state.y);
    player->set_shape_pos(state.player2_state.x, state.player2_state.y);
    player->set_shape_angle(state.player2_state.angle);

    player2->set_posx(state.player1_state.x);
    player2->set_posy(state.player1_state.y);
    player2->set_shape_pos(state.player1_state.x, state.player1_state.y);
    player2->set_shape_angle(state.player1_state.angle);

    // clear_projectiles();
    for (projectile_state sproj : state.projectiles) {
        Projectile *proj = new Projectile(sproj.posx, sproj.posy, sproj.velx, sproj.vely, 5.f);
        projectiles.push_back(proj);
        // sproj->set_position();
        // proj->set_posx()
    }
}


game_state ClientGame::get_groundtruth_state()
{
    // std::cout << "tsque size " << client->ts_queue.size() << std::endl;
    GamestateMessage msg = client->ts_queue.pop_back();
    client->ts_queue.clear();
    game_state gstate = msg.get_game_state();
    // std::cout << "\n\nrecieved game state:" << std::endl;
    // std::cout << "p1 " <<gstate.player1_state.x << " " << gstate.player1_state.y << "  p2 " << gstate.player2_state.x << " " << gstate.player2_state.y;
    // std::cout << " projectiles ";
    // for (auto p : gstate.projectiles) {
    //     std::cout << p.posx << "," << p.posy << "   ";
    // }
    std::cout << std::endl;

    return gstate;
}


void ClientGame::send_controls(Move move)
{
    client->send_data(move);
}


void ClientGame::update()
{
    poll_events();

    if (client->ts_queue.size() > 0) {
        game_state state = get_groundtruth_state();
        set_groundtruth_state(state);
    }

    update_gravity_objects();

    update_lasers();

    Move move = check_keyboard();

    update_player(player, move);

    // update_player2(); // for now just do ground truth

    update_screen_pos();

    update_arrows(); 

    send_controls(move); 
}