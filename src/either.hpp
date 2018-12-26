#include <variant>

namespace Either {
  class Left_t{};
  static Left_t const Left{};
  class Right_t{};
  static Right_t const Right{};

  template<typename Left, typename Right>
  class Either {
    std::variant<Left, Right> body;
  public:
    bool is_left() { return body.index() == 0; }
    bool is_right() { return body.index() == 1; }
    Left& left() { return std::get<Left>(body); }
    Right& right() { return std::get<Right>(body); }
    Either() : body{Left{}} {}
    Either(Left_t, Left l) : body{l} {}
    Either(Right_t, Right r) : body{r} {}
  };
}
