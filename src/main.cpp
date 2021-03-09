#include <iostream>

#include <boost/asio/spawn.hpp>

int main() {
    std::cout << "Hello world!\n";

    boost::asio::io_context asyncContext;

    boost::asio::spawn(asyncContext, [](boost::asio::yield_context yield) {
        std::cout << "Hello world2!\n";
    });

    asyncContext.run();

    return 0;
}
