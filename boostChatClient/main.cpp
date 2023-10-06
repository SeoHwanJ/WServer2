#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>

using boost::asio::ip::tcp;

constexpr int BUFF_SIZE = 32;
int main() {
    try{
        std::string port = "6000";
        std::string host = "localhost";
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host,port);
        tcp::socket socket(io_context);
        boost::asio::async_connect(socket, endpoints, [&socket](boost::system::error_code ec, const tcp::endpoint&){
            if(!ec)
            {
                std::cout<<"connection success! "<<std::endl;
                std::cout<<"write msg"<<std::endl;
                char writeBuff[BUFF_SIZE];
                std::cin.getline(writeBuff, BUFF_SIZE);
                boost::asio::async_write(socket, boost::asio::buffer(writeBuff, std::strlen(writeBuff)),[](boost::system::error_code ec,
                        size_t byteTransferred)
                {
                    if(!ec)
                    {
                        std::cout<<"write success, transferred : "<<byteTransferred<<"bytes"<<std::endl;
                    }
                    else
                    {
                        std::cerr<<"error in writing"<<std::endl;
                    }
                });
            }
            else
            {
                std::cerr<<"error in connection : "<<ec.message()<<std::endl;
            }
        });

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}
