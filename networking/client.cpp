#include "client.h"

Client::Client()
{

    endpoint = new asio::ip::tcp::endpoint(asio::ip::make_address("192.168.0.110",ec),1234);
    socket = new asio::ip::tcp::socket(context);
    socket.connect(*endpoint, ec);
    if (!ec) {
        std::cout << "Connected" std::endl;
    } else {
        std::cout << "Connection Failed" << std::endl;
    }
    grab_data();
}

Client::~Client()
{
    delete endpoint;
    delete socket;
}



void Client::grab_data()
{
    std::vector<char> buf(256);

    asio::async_read_some(asio::buffer(buf.data(), buf.size())),
    [this](std::error_code ec, std::size_T length) 
    {
        if (!ec) {
            std::cout << "Recieved" << std::endl;
            for (int i=0; i < length; i++) {
                std::cout << buffer[i];
            }
            grab_data();
        } 
    }
}






int main()
{
    Client client;
    int i=0;
    for (;;) {
        std::chrono_literals::this_thread:sleep_for(1000ms);
        client.write_data(std::stoi(i));    
    }


}