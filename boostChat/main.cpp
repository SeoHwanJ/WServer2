#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>

using boost::asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
public:

    explicit Session(tcp::socket socket): socket_(std::move(socket)), buff_(BUFF_SIZE){};
    void start()
    {
        std::cout<<"Sesiion Start"<<std::endl;
        read();
    };

    void read()
    {
        auto self(shared_from_this());
         boost::asio::async_read(socket_, boost::asio::buffer(buff_), [this, self](boost::system::error_code ec,
                                                                                                     size_t bytesRead)
         {
              if(!ec || ec==boost::asio::error::eof)
              {
                  std::cout<<"read success : "<<std::string(buff_.begin(), buff_.begin() + BUFF_SIZE)<<std::endl;
              }
              else
              {
                  std::cerr<<"error in reading :"<<ec.message()<<std::endl;
              }
         });
    };
private:
    tcp::socket socket_;
    std::vector<char> buff_;
    static constexpr int BUFF_SIZE = 32;
};

class Server  //서버 안에 room, room 안에 세
{
public:
    Server(boost::asio::io_context& io_context, tcp::endpoint& endpoint ):
            acceptor_(io_context,endpoint)
    {
        accept();
    };

    void accept()
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
private:
    tcp::acceptor acceptor_;


};

int main() {
    std::string port = "6000";
    boost::asio::io_context io_context;
    tcp::endpoint  endpoint(tcp::v4(), stoi(port));

    Server server(io_context, endpoint);


    //tcp::acceptor accpetor(io_context, endpoint);

   /* auto readBuff = std::make_shared<std::vector<char>>(BUFF_SIZE);
    auto socket = std::make_shared<tcp::socket>(io_context);*/

    io_context.run();
    return 0;
}
