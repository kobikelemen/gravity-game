#include "client.h"

Client::Client()
{
    buf = std::vector<int32_t>(1024 * 10);
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

Client::~Client()
{
    delete endpoint;
    delete socket;
}



void Client::grab_data()
{

    socket->async_read_some(asio::buffer(buf.data(), buf.size()),
        [this](std::error_code ec, std::size_t length) 
        {
            if (!ec) {
                std::cout << "Recieved" << std::endl;
                for (int i=0; i < length; i++) {
                    std::cout << buf[i];
                }
                grab_data();
            } 
        }
    );
}


void Client::send_data(std::string data)
{
    std::cout << "data sent" << std::endl;
    asio::write(*socket, asio::buffer(data, sizeof(data)));
}



int main()
{
    Client client;    
    std::thread context_thread = std::thread([&]() { client.context.run(); });
    int i=0;
    for (;;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        client.send_data(std::to_string(i));
        i++;
        
    }

}