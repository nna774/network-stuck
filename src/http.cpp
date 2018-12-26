#include <iostream>
#include <sstream>

#include "http.hpp"
#include "tcp.hpp"

namespace http {
  Result error(std::string_view err_str) {
    return Result{Either::Left, Error::error(err_str)};
  }
  Result error(Error::Error err) {
    return Result{Either::Left, err};
  }

  Result get(std::string_view uri_str) {
    URI /* const */ uri = parseURI(uri_str);
    uri.host = "example.com";
    uri.port = 80;
    uri.path = "/";
    auto conn_ = TCP::make_connection(uri.host, uri.port);
    if(conn_.is_left()) {
      return error(conn_.left());
    }
    auto conn = conn_.right();

    std::stringstream req;
    req << "GET " << uri.path << " HTTP/1.1\r\nHOST: " << uri.host << "\r\n\r\n";

    std::string const& req_str = req.str();
    conn.write(req_str);
    std::string buf{conn.read()};
    std::cout << buf;

    return error("success!");
  }

  URI parseURI(std::string_view uri_str) {
    URI uri;
    return uri;
  }
}
