#include <iostream>
#include <asio.hpp>
#include <string>
#include <chrono>
#include <thread>


class Client
{
    
    asio::ip::tcp::endpoint *endpoint;
    asio::ip::tcp::socket *socket;
    asio::error_code ec;
    std::vector<char> buf;
    void grab_data();

public:
    asio::io_context context;
    Client();
    ~Client();
    // void read_data();
    void send_data(std::string data);

};