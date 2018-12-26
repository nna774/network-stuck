#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include "tcp.hpp"

namespace TCP {
  Either::Either<Error::Error, Connection> error(std::string_view err) {
    return {Either::Left, Error::error(err)};
  } 

  Connection::~Connection() {
  }

  size_t Connection::write(std::string const& input) {
    if(!fd_) {
      // !!!
      return -1;
    }
    return ::write(*fd_, input.c_str(), input.size());
  }

  std::string Connection::read() {
    if(!fd_) {
      // !!
      return "";
    }
    int const BUF_SIZE{10000};
    char buf[BUF_SIZE];
    int read_size = ::read(*fd_, buf, BUF_SIZE);
    return buf;
  }

  Either::Either<Error::Error, Connection> make_connection(std::string const& host, int port) {
    struct addrinfo hints{}, *res;

    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_TCP;

    int const err = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res);
    if(err != 0) {
      return error(gai_strerror(err));
    }

    int sockfd{};
    auto* r = res;
    for(; r != nullptr; r = r->ai_next) {
      sockfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
      if(sockfd == -1) { continue; }

      if(connect(sockfd, r->ai_addr, r->ai_addrlen) != -1) {
        break; // success
      }
      ::close(sockfd);
    }
    if(r == nullptr) {
      return error("no addr succeeded.");
    }
    freeaddrinfo(res);

    Connection conn{host, port, sockfd};
    return {Either::Right, conn};
  }
}
