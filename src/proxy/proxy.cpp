#include "proxy.hpp"
#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

void handle_session(tcp::socket socket) {
    try {
        if (!cb.try_request()) {
            std::string response = "HTTP/1.1 502 Bad Gateway\r\nContent-Length: 0\r\n\r\n";
            asio::write(socket, asio::buffer(response));
            return;
        }

        char data[4096];
        asio::error_code error;
        size_t length = socket.read_some(asio::buffer(data), error);
        if (error) return;

        std::string body(data, length);
        std::string err;
        if (!is_valid_json(body, err)) {
            cb.record_failure();
            std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
            asio::write(socket, asio::buffer(response));
        } else {
            cb.record_success();
            std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
            asio::write(socket, asio::buffer(response));
        }
    } catch (...) {}
}

int main(int argc, char* argv[]) {
    unsigned short port = 8080;
    if (argc == 2) port = static_cast<unsigned short>(std::stoi(argv[1]));

    asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
    std::cout << "Server running on port " << port << std::endl;

    while (true) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        handle_session(std::move(socket));
    }
}
