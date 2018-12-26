#pragma once

#include <variant>

// Either<T, T> と作ると困るが、それを望むことは無いだろうし、一旦無視する(必要であれば特殊化すれば良い)。
namespace Either {
  class Left_t{};
  static Left_t const Left{};
  class Right_t{};
  static Right_t const Right{};

  template<typename Left, typename Right>
  class Either {
    std::variant<Left, Right> body;
    using this_t = Either<Left, Right>*;
  public:
    bool is_left() const { return body.index() == 0; }
    bool is_right() const { return body.index() == 1; }
    Left const& left() const { return std::get<Left>(body); }
    Right const& right() const { return std::get<Right>(body); }
    Left& left() { return std::get<Left>(body); }
    Right& right() { return std::get<Right>(body); }
    Either() : body{Left{}} {}
    Either(Left_t, Left l) : body{l} {}
    Either(Right_t, Right r) : body{r} {}
  };
}
