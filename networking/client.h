#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <asio.hpp>
#include <string>
#include <chrono>
#include <thread>
#include "threadsafe_queue.h"
// #include "message.h"

class Client
{
    
    asio::ip::tcp::endpoint *endpoint;
    asio::ip::tcp::socket *socket;
    asio::error_code ec;
    std::vector<float> buf;
    void grab_data();

public:
    
    tsQueue<GamestateMessage> ts_queue;
    asio::io_context context;   
    Client();
    ~Client();
    // void read_data();
    void start_connection();
    void send_data(Move controls);

};

#endif