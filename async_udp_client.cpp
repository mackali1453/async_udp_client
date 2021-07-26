//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

//constexpr short multicast_port = 30001;
//constexpr int max_message_count = 10;

//#pragma pack(push,r1,1)

struct PlatformData {
	unsigned char securityId = 0;
	unsigned char position = 0;
	unsigned char velocity = 0;
	unsigned char acceleration = 0;
//	float temperature = 5;
//	float current = 6;
//	float torque = 7;
//	char driver = 8;
//	float voltage = 9;
//	float encoder = 10;
//	char limitSensor1 = 11;
//	char limitSensor2 = 12;
};
//#pragma pack(pop,r1)


class sender
{
public:
  sender(boost::asio::io_context& io_context,const boost::asio::ip::udp::endpoint endpoint)
    : endpoint_(endpoint),socket_(io_context, endpoint.protocol())
//      timer_(io_context),
//      message_count_(0)
  {
    do_send();
  }

private:
  void do_send()
  {
//    std::ostringstream os;
//    os << "Message " << message_count_++;
//    message_ = os.str();

//	platform_data.acceleration = 15;
//	platform_data.position = 25;
	platform_data.securityId = 35;
	platform_data.velocity = 45;
	socket_.async_send_to(boost::asio::buffer(&platform_data,sizeof(platform_data)), endpoint_,
	          boost::bind(&sender::handle_receive, this,boost::asio::placeholders::error));
  }

  void handle_send()
  {
	  std::cout<<"async udp client receives:"
	  	  <<(int)platformData.acceleration<<std::endl
	  	  <<(int)platformData.position<<std::endl;
//	  	  <<platformData.securityId<<std::endl
//	  	  <<platformData.velocity<<std::endl;
  }
  void handle_receive(const boost::system::error_code& error)
    {
      if (!error)
      {

  	  std::cout<<"async udp client sends:"
//  	  <<platform_data.acceleration<<std::endl
//  	  <<platform_data.position<<std::endl
  	  <<(int)platform_data.securityId<<std::endl
  	  <<(int)platform_data.velocity<<std::endl;


        socket_.async_receive_from(boost::asio::buffer(&platformData,sizeof(platformData)), endpoint_,
            boost::bind(&sender::handle_send, this));

        do_send();
      }
    }
private:
  boost::asio::ip::udp::endpoint endpoint_;
  boost::asio::ip::udp::socket socket_;
  PlatformData platformData;
  PlatformData platform_data;
//  boost::asio::steady_timer timer_;
//  int message_count_;
//  std::string message_;
};

int main(int argc, char* argv[])
{
  try
  {
//    if (argc != 2)
//    {
//      std::cerr << "Usage: sender <multicast_address>\n";
//      std::cerr << "  For IPv4, try:\n";
//      std::cerr << "    sender 239.255.0.1\n";
//      std::cerr << "  For IPv6, try:\n";
//      std::cerr << "    sender ff31::8000:1234\n";
//      return 1;
//    }

    boost::asio::io_context io_context;
    boost::asio::ip::udp::endpoint endpoint(
            boost::asio::ip::address::from_string("127.0.0.1"), 13);
    sender s(io_context, endpoint);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
