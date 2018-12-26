#pragma once

#include <string>
#include <optional>

#include "either.hpp"
#include "error.hpp"

namespace TCP {
  class Connection {
    std::string const host_;
    int const port_;
    std::optional<int> fd_;
    Connection(std::string_view host, int port, int fd) : host_{host}, port_{port}, fd_{fd} {}
    friend Either::Either<Error::Error, Connection> make_connection(std::string const& host, int port);
  public:
    ~Connection();
    size_t write(std::string const& input);
    std::string read();
    std::string read(size_t size);
    void close();
  };

  Either::Either<Error::Error, Connection> make_connection(std::string const& host, int port);
}
