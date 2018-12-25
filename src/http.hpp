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
  struct URI {
    std::string host;
    int port;
    std::string path;
  };
  using Result = std::pair<std::optional<Response>, std::optional<Error>>;

  Result get(std::string_view uri);
  URI parseURI(std::string_view uri);
}
