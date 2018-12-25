#include <optional>
#include <string>
#include <utility>

namespace http {
  struct Error {
    std::string error;
  };
  struct Response {
    int status_code;
    std::string body;
  };
  using Result = std::pair<std::optional<Response>, std::optional<Error>>;

  Result get(std::string_view uri);
}
