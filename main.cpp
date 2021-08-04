#include <iostream>
#include <boost/asio.hpp>
#include "Apple.h"

int main() {
  boost::asio::io_context io;
  std::cout << "Hello world\n";

  std::cout << "Waiting one boosted second\n";
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));

  t.wait();
  Apple().apple();
  return 0;
}
