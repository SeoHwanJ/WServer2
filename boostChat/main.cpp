#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>
#include "Session.h"
#include "Server.h"

using boost::asio::ip::tcp;






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
