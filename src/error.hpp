#pragma once

#include <string>
#include <memory>

namespace Error {
  class BasicError {
    std::string const err;
  public:
    BasicError(std::string_view err_str) : err{err_str} {}
    std::string error() { return err; }
  };

  using Error = std::shared_ptr<BasicError>;

  inline Error error(std::string_view err_str) {
    return std::make_shared<BasicError>(err_str);
  }
}
