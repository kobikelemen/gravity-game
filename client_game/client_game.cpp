#include "client_game.h"



ClientGame::ClientGame(Player *p, sf::Vector2f screen_dimensions) : Game(p, screen_dimensions)
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
    // std::cout << "tsque size " << client->ts_queue.size() << std::endl;
    GamestateMessage msg = client->ts_queue.pop_back();
    client->ts_queue.clear();
    game_state gstate = msg.get_game_state();
    return gstate;
}


void ClientGame::send_controls(Move move)
{
    client->send_data(move);
}


void ClientGame::update()
{
    poll_events();
    std::cout << " 6 " << std::endl;
    if (client->ts_queue.size() > 0) {
        game_state state = get_groundtruth_state();
        std::cout << " 7 " << std::endl;
        set_groundtruth_state(state);
    }
    

    std::cout << " 8 " << std::endl;
    update_gravity_objects();
    std::cout << " 9 " << std::endl;
    update_lasers();
    std::cout << " 10 " << std::endl;
    Move move = check_keyboard();
    std::cout << " 11 " << std::endl;
    update_player(player, move);
    std::cout << " 12 " << std::endl;
    // update_player2(); // for now just do ground truth

    update_screen_pos();
    std::cout << " 13 " << std::endl;
    update_arrows(); 
    std::cout << " 14 " << std::endl;
    send_controls(move); 
}