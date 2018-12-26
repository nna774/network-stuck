#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
// #include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "http.hpp"

namespace http {
  Result error(std::string_view err_str) {
    Error err;
    err.error = err_str;
    return Result{Either::Left, err};
  }

  Result get(std::string_view uri_str) {
    URI /* const */ uri = parseURI(uri_str);
    uri.host = "example.com";
    uri.port = 80;
    uri.path = "/";
    struct addrinfo hints{}, *res;

    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_TCP;

    int err = getaddrinfo(uri.host.c_str(), std::to_string(uri.port).c_str(), &hints, &res);
    if(err != 0) {
      return error(gai_strerror(err));
    }

    int sockfd;
    auto* r = res;
    for(; r != nullptr; r = r->ai_next) {
      sockfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
      if(sockfd == -1) { continue; }

      if(connect(sockfd, r->ai_addr, r->ai_addrlen) != -1) {
        break; // success
      }
      close(sockfd);
    }
    if(r == nullptr) {
      return error("no addr succeeded.");
    }
    freeaddrinfo(res);

    std::stringstream req;
    req << "GET " << uri.path << " HTTP/1.1\r\nHOST: " << uri.host << "\r\n\r\n";

    std::string const& req_str = req.str();
    write(sockfd, req_str.c_str(), req_str.size());

    int const BUF_SIZE{10000};
    char buf[BUF_SIZE];
    int read_size = read(sockfd, buf, BUF_SIZE);

    std::cout << read_size << " bytes read." << std::endl;
    std::cout << buf;

    return error("success!");
  }

  URI parseURI(std::string_view uri_str) {
    URI uri;
    return uri;
  }
}
