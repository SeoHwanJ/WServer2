//
// Created by SeoHwan Jin on 2023/10/11.
//

#ifndef BOOSTCHAT_SERVER_H
#define BOOSTCHAT_SERVER_H


#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>

using boost::asio::ip::tcp;

class Server  //서버 안에 room, room 안에 세
{
public:
    Server(boost::asio::io_context& io_context, tcp::endpoint& endpoint );
    void accept();

private:
    tcp::acceptor acceptor_;

};

#endif //BOOSTCHAT_SERVER_H
