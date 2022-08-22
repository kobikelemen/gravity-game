
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
    asio::io_service io_service;

    asio::ip::tcp::acceptor acceptor_(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 1234 ));

    for (;;) {
        asio::ip::tcp::socket socket_(io_service);

        acceptor_.accept(socket_);

        std::string message = read_(socket_);
        std::cout << message << std::endl;
    }
    
}