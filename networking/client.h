#include <asio.hpp>
#include <string>
#include <chrono>



class Client
{
    asio::io_context context;
    asio::ip::tcp::endpoint *endpoint;
    asio::ip::tcp::socket *socket;
    asio::error_code ec;
    void grab_data();

public:
    Client();
    ~Client();
    // void read_data();
    void write_data(std::string s);

};