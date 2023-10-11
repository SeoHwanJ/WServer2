//
// Created by SeoHwan Jin on 2023/10/11.
//

#ifndef BOOSTCHAT_SESSION_H
#define BOOSTCHAT_SESSION_H

#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:

    Session(tcp::socket socket);
    void start();
    void read();

private:
    tcp::socket socket_;
    boost::asio::streambuf buff_;
    static constexpr int BUFF_SIZE = 32;
};


#endif //BOOSTCHAT_SESSION_H
