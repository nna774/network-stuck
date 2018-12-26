#pragma once

#include <string>

#include "either.hpp"
#include "error.hpp"

namespace http {
  struct Response {
    int status_code;
    std::string body;
  };
  struct URI {
    std::string host;
    int port;
    std::string path;
  };
  using Result = Either::Either<Error::Error, Response>;

  Result get(std::string_view uri);
  URI parseURI(std::string_view uri);
}
