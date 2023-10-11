//
// Created by SeoHwan Jin on 2023/10/11.
//

#include "Server.h"
#include "Session.h"

Server::Server(boost::asio::io_context& io_context, tcp::endpoint& endpoint ):
        acceptor_(io_context,endpoint)
{
    accept();
};

void Server::accept()
{
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket){
        if(!ec)
        {
            std::cout<<"client accpeted!"<<std::endl;
            std::make_shared<Session>(std::move(socket))->start();
            accept();
        }
        else
        {
            std::cerr<<"error in accpetion"<<ec.what()<<std::endl;
        }
    });
}