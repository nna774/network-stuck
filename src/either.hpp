#include <variant>

namespace Either {
  class Left_t{};
  static Left_t const Left{};
  class Right_t{};
  static Right_t const Right{};

  template<typename Left, typename Right>
  class Either {
    bool const is_right_;
    std::variant<Left, Right> body;
  public:
    bool is_right() { return is_right_; }
    bool is_left() { return !is_right_; }
    Left& left() { return std::get<Left>(body); }
    Right& right() { return std::get<Right>(body); }
    Either() : is_right_{false}, body{Left{}} {}
    Either(Left_t, Left l) : is_right_{false}, body{l} {}
    Either(Right_t, Right r) : is_right_{true}, body{r} {}
  };
}
