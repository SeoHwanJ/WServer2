#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>

using boost::asio::ip::tcp;

constexpr int BUFF_SIZE = 32;

class Client
{
public:
    Client(boost::asio::io_context& io_context, tcp::resolver::results_type& endpoints): socket_(io_context)
    {
        connect(endpoints);
    };

    void close()
    {
        boost::asio::post(socket_.get_executor(), [this](){socket_.close();});
    };

    void write(const char* writeBuff)
    {
        boost::asio::async_write(socket_, boost::asio::buffer(writeBuff, std::strlen(writeBuff)),
         [this](boost::system::error_code ec, size_t byteTransferred)
         {
             if(!ec)
             {
                 std::cout<<"write success, transferred : "<<byteTransferred<<"bytes"<<std::endl;
             }
             else
             {
                 std::cerr<<"error in writing : "<<ec.message()<<std::endl;
                 socket_.close();
             }
         });
    };

    void read()
    {
        boost::asio::async_read(socket_, boost::asio::buffer(readBuff_, BUFF_SIZE),[this](boost::system::error_code ec, size_t byteTransferred)
        {
            if(!ec)
            {
                std::cout<<"read success, transferred : "<<byteTransferred<<"bytes"<<std::endl;
            }
            else
            {
                std::cerr<<"error in reading : "<<ec.message()<<std::endl;
                socket_.close();
            }
        });
    }

    void connect(tcp::resolver::results_type& endpoints)
    {
        boost::asio::async_connect(socket_, endpoints, [this](boost::system::error_code ec, const tcp::endpoint&){
            if(!ec)
            {
                std::cout<<"connection success! "<<std::endl;
                connected_.store(true);
                read();

            }
            else
            {
                std::cerr<<"error in connection : "<<ec.message()<<std::endl;
                socket_.close();
            }
        });
    };

    bool isConnected() const{
        return connected_.load();
    }
private:
    tcp::socket socket_;
    char* readBuff_;
    std::atomic<bool> connected_=false;
};


int main() {
    try{
        std::string port = "6000";
        std::string host = "localhost";
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host,port);
        Client client(io_context,endpoints);

        std::thread t([&io_context](){io_context.run();});

        while(!client.isConnected())
        {
            std::cout<<"wait for connection"<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds (100));
        }

        while(true)
        {
            std::cout<<"write msg"<<std::endl;
            char writeBuff[BUFF_SIZE];
            std::cin.getline(writeBuff, BUFF_SIZE);
            std::strcat(writeBuff, "\n");
            client.write(writeBuff);
        };

        client.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}
