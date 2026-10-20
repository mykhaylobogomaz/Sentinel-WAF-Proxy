#include <asio.hpp>
#include <iostream>

using asio::ip::tcp;

int main() {
    asio::io_context ctx;
    tcp::acceptor acceptor(ctx, tcp::endpoint(tcp::v4(), 8081));
    std::cout << "Backend running on 8081" << std::endl;
    for (;;) {
        tcp::socket socket(ctx);
        acceptor.accept(socket);
        asio::write(socket, asio::buffer("HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK"));
    }
}
