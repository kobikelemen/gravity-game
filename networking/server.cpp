
#include "server.h"
#include "message.h"

// g++ server.cpp -I/home/linuxbrew/.linuxbrew/Cellar/asio/1.24.0/include -o server



Server::Server()
{
    buf = std::vector<int>(1024 * 10);
    acceptor = new asio::ip::tcp::acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 1234 ));
    socket = new asio::ip::tcp::socket(context);    
    wait_for_connection();
    asio::io_context::work idle_work(context);
}

Server::~Server()
{
    delete socket;
    delete acceptor;
}



void Server::grab_data()
{
    socket->async_read_some(asio::buffer(buf.data(), buf.size()),
        [this](std::error_code ec, std::size_t length)
        {
            if (!ec) {
                std::cout << "Recieved" << std::endl;
                for (int i=0; i < length; i ++) {
                    std::cout << buf[i] << " " << std::endl;
                }

                send_data(std::vector<float>(1.f));
            } else {
                std::cout << "Read failed" << std::endl;
            }
            grab_data();
        }
    );
}


void Server::send_data(std::vector<float> data)
{    

    game_state state;
    state.planet_pos = pos(1.f,1.f);
    state.player1_pos = pos(2.f,2.f);
    state.player2_pos = pos(3.f,3.f);
    state.projectiles.push_back(projectile_state(4.f,4.f,4.f,4.f));

    GamestateMessage msg(state);
    std::cout << "msg body: ";
    for (int i=0; i < msg.body.size(); i ++) {
        std::cout << msg.body[i] << " ";
    }
    asio::write(*socket, asio::buffer(msg.body));
}

void Server::wait_for_connection()
{
    acceptor->accept(*socket);
    grab_data();
}


int main()
{
    
    Server server;
    std::thread context_thread = std::thread([&]() { server.context.run(); });
    for (;;)
    {

    }
}
