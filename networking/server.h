#ifndef SERVER_H
#define SERVER_H

#include <asio.hpp>
#include <iostream>
#include <thread>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <chrono>
#include <thread>
#include "threadsafe_queue.h"


class Server
{
    tsQueue<ControlMessage> ts_queue;
    asio::ip::tcp::acceptor *acceptor;
    asio::ip::tcp::socket *socket;
    
    asio::error_code ec;
    std::vector<int> buf;
    void wait_for_connection();

public:
    asio::io_context context;
    Server();
    ~Server();
    void grab_data();
    void send_data(std::vector<float> data);

};


#endif