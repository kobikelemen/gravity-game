#include <asio.hpp>


class Server
{
    asio::ip::tcp::acceptor *acceptor;
    asio::ip::tcp::socket *socket;
    asio::io_context context;

public:
    Server();
    ~Server();
    void grab_data();
    void send_data(std::vector<char> data);
}