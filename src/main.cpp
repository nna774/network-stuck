#include <iostream>

#include "http.hpp"

int main(int, char**) {
  http::Result res = http::get("http://example.com/");

  if(res.second) {
    std::cerr << res.second->error << std::endl;
    return -1;
  }

  http::Response const& resp = *res.first;

  if(resp.status_code != 200) {
    std::cerr << "status code not 200. got: " << resp.status_code << std::endl;
    return -1;
  }

  std::cout << resp.body;

  return 0;
}
