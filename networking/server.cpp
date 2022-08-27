
#include <iostream>
#include <thread>

#include <asio.hpp>


std::string read_(asio::ip::tcp::socket & socket) {
       asio::streambuf buf;
       asio::read_until( socket, buf, "\n" );
       std::string data = asio::buffer_cast<const char*>(buf.data());
       return data;
}

int main()
{

    acceptor = new asio::ip::tcp::acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 1234 ));

    for (;;) {
        asio::ip::tcp::socket socket_(io_service);

        acceptor.accept(socket_);

        std::string message = read_(socket_);
        std::cout << message << std::endl;
    }
    
}





Server::Server()
{
    acceptor = new asio::ip::tcp::acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 1234 ));
    socket = new asio::ip::tcp::socket socket(context);
    
    wait_for_connection();
}

Server::~Server()
{
    delete socket;
    delete acceptor;
}

void Server::grab_data()
{
    std::vector<char> buf(256);
    asio::async_read_some(asio::buffer(buf.data(), buf.size())),
    [this](std::error_code ec, std::size_T length)
    {
        if (!ec) {
            std::cout << "Recieved" << std::endl;
            for (int i=0; i < length; i ++) {
                std::cout << buffer[i];
            }
            send_data(buffer);
            grab_data();
        }
    }
}


void Server::send_data(std::vector<char> data)
{
    std::string strdata(data.begin(), data.end());
    strdata += "echo";
    asio::write(socket, asio::buffer(strdata)
}

void wait_for_connection()
{
    acceptor->accept(*socket);

    // acceptor->async_accept(
    //     [this](std::error_code ec, asio::ip::tcp::socket socket) {

    //     }
    // )
}


int main()
{
    Server server;
    
}
