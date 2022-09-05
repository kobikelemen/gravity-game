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
// #include "message.h"

class Server
{
    
    asio::ip::tcp::acceptor *acceptor;
    asio::ip::tcp::socket *socket;
    asio::error_code ec;
    std::vector<int> buf;
    void wait_for_connection();

public:
    tsQueue<ControlMessage> ts_queue;
    asio::io_context context;
    Server();
    ~Server();
    void grab_data();
    void send_data(game_state state);
    void start_connection();

};


#endif