//
// Created by SeoHwan Jin on 2023/10/11.
//

#include "Session.h"
#include <boost/hana.hpp>
#include <cstdlib>
#include <iostream>


Session::Session(tcp::socket socket): socket_(std::move(socket)), buff_(BUFF_SIZE){};
void Session::start()
{
    std::cout<<"Sesiion Start"<<std::endl;
    read();
};

void Session::read()
{
    auto self(shared_from_this());
    boost::asio::async_read_until(socket_, buff_, '\n',[this, self](boost::system::error_code ec, size_t bytesRead)
    {
        if(!ec)
        {
            std::istream is(&buff_);
            std::string line;
            std::getline(is, line);
            std::cout<<"read success : "<<line<<std::endl;
            read();
            // std::cout<<"read success : "<<std::string(buff_.begin(), buff_.begin() + BUFF_SIZE)<<std::endl;
        }
        else
        {
            std::cerr<<"error in reading :"<<ec.message()<<std::endl;
            socket_.close();
        }
    });
};
