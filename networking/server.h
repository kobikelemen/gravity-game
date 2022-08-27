#include <asio.hpp>


class Server
{
    asio::ip::tcp::acceptor *acceptor;
    asio::ip::tcp::socket *socket;
    asio::io_context context;
    asio::error_code ec;
    std::vector<char> buf;
    void wait_for_connection();

public:
    Server();
    ~Server();
    void grab_data();
    void send_data(std::vector<char> data);

};