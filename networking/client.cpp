#include "client.h"

Client::Client()
{

}

Client::~Client()
{
    delete endpoint;
    delete socket;
}


void Client::start_connection()
{
    buf = std::vector<float>(1024 * 10);
    std::string ip_address = "192.168.0.91";
    endpoint = new asio::ip::tcp::endpoint(asio::ip::make_address(ip_address,ec),1234);
    socket = new asio::ip::tcp::socket(context);
    socket->connect(*endpoint, ec);
    if (!ec) {
        std::cout << "Connected" << std::endl;
    } else {
        std::cout << "Connection Failed\n" << ec.message() << std::endl;
    }
    grab_data();
    asio::io_context::work idle_work(context);
}


void Client::grab_data()
{

    socket->async_read_some(asio::buffer(buf.data(), buf.size()),
        [this](std::error_code ec, std::size_t length) 
        {
            if (!ec) {
                // std::cout << "Recieved" << std::endl;
                // for (int i=0; i < length; i++) {
                //     std::cout << buf[i];
                // }
                GamestateMessage msg = GamestateMessage(buf);
                game_state gs = msg.get_game_state();
                // std::cout << "\n\nrecieved game state:" << std::endl;
                // std::cout << "p1 " <<gs.player1_state.x << " " << gs.player1_state.y << "  p2 " << gs.player2_state.x << " " << gs.player2_state.y << std::endl;
                ts_queue.push_front(msg);
                grab_data();
            } 
        }
    );
}


void Client::send_data(Move controls)
{
    // std::cout << "sending controls: " << controls.left << " " << controls.right << " " << controls.up << " " << controls.space << " " << std::endl;
    // Move c(true,false,true,true,false);
    ControlMessage cmsg(controls);
    asio::write(*socket, asio::buffer(cmsg.body));
}



// int main()
// {
//     Client client; 
//     client.start_connection();   
//     std::thread context_thread = std::thread([&]() { client.context.run(); });
//     int i=0;
//     for (;;) {
//         std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//         client.send_data(std::to_string(i));
//         i++;
        
//     }

// }