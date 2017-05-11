#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE FakeUnitTest

#include <boost/test/unit_test.hpp>

#include <thread>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>
#include <map>
#include "currency.h"

// just logging something ( --log_level=message )

// using fake Fixer.io with one second of refresh
struct GlobalInit {

  using Param = std::map<std::string, std::string>;

  GlobalInit() : argc(boost::unit_test_framework::framework::master_test_suite().argc),
		 argv(boost::unit_test_framework::framework::master_test_suite().argv)
  {
    Param param {commandline(argc, argv)};

    if(param["help"] == "help") { std::cout << "\n\tUsage " << param["PROGRAM"] <<
    R"( [--log_level=message] -- [--help] [--host=fake host to query] [--port=fake port to query]

	    All those commandline arguments are optional:

	      By default, --host=localhost

	      By default, --port=8080

)"; exit(0); }

    if( param.cend() != param.find("host") ) { if( not param["host"].empty() ) { host = param["host"]; } }
    if( param.cend() != param.find("port") ) { if( not param["port"].empty() ) { port = param["port"]; } }

    std::string mock {MOCK};
    std::string binary{param["PROGRAM"]};
    size_t pos = binary.find_last_of("/\\");
    if( pos > 0 ) {
	mock = binary.substr(0,pos+1) + relative_path;
    }
    BOOST_TEST_MESSAGE( "Mock binary: " << mock << "\n" );

     std::string found = exec(std::string{"ls -larth  " + mock}.c_str());
     if( std::string::npos == found.find(mock) ) {
	BOOST_TEST_MESSAGE( "Not found " << mock << ". Resorting to hardcoded value 1.0 as rate.\n" );
     } else {
        BOOST_TEST_MESSAGE( found );
	if( 0 != std::system(std::string{mock + " " + host + " " + port + " &"}.c_str())) {
	  BOOST_TEST_MESSAGE( "Unable to launch " << mock << " in the backgroud. Resorting to hardcoded value 1.0 as rate.\n" );
        } else {
           std::this_thread::sleep_for(std::chrono::milliseconds(1)); // give some time to start 
	   pid = exec("ps -edf | grep mock/Currency_mock | grep -v grep | awk '{print $2}'");
           pid.erase(pid.find_last_not_of(" \n\r\t")+1);
	   BOOST_TEST_MESSAGE( "Using mock/Currency_mock [" << pid << "]. Expect random values as rate.\n" );
 	}
     }
     assert(CURRENCY_IN_SYNC(CURRENCY_VERSION));
     currency_global_init(1, std::string{host + ":" + port}.c_str());
  }

  ~GlobalInit() {
     if( not pid.empty() ) {
	std::string cmd = "kill -9 " + pid;
	std::string kill = exec(cmd.c_str());
	BOOST_TEST_MESSAGE( "\nKilled mock/Currency_mock process " << pid << "\n");
     }
  }

private:

  const std::string MOCK {"mock/Currency_mock"};
  const std::string relative_path {"../mock/Currency_mock"};
  std::string host {"localhost"};
  std::string port {"8080"};

  std::string pid {""};
  int argc {};
  char **argv {nullptr};

  std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return result;
  }

  Param commandline(const int argc = 0, char** argv = nullptr) const
  {
	  Param result{};
	  if(argc > 0) { result.emplace("PROGRAM", argv[0]); }

	  static const std::regex param_pattern{"^-[-]?(.*)[ ]*=[ ]*(.*)$"};
	  static const std::regex help_pattern{"^-[-]?help$"};
	  for(int i=1; i<argc; ++i) {
		 std::string candidate{argv[i]};
		 std::smatch param_match;
		 if(std::regex_match(candidate, param_match, help_pattern)) {
			 result.emplace("help", "help");
			 continue;
		 }
		 if(std::regex_match(candidate, param_match, param_pattern)) {
			 if( param_match.size() == 3) {
				 result.emplace(param_match[1].str(), param_match[2].str());
			 }
		 }
	  }

	  return result;
  }

};
BOOST_GLOBAL_FIXTURE( GlobalInit );

BOOST_AUTO_TEST_CASE( test000 ) {
   BOOST_TEST_MESSAGE( "\ntest000" );
   for(double eur=1.0; eur<5; ++eur) {
      std::this_thread::sleep_for(std::chrono::milliseconds(2)); // sleep for two seconds
      double conversion { eur * currency_USD() };
      BOOST_TEST_MESSAGE( " Fake " << eur << " EUR = " << conversion << " USD" );
      BOOST_CHECK( conversion > 0.0 );
   }
}

BOOST_AUTO_TEST_CASE( test001 ) {
   BOOST_TEST_MESSAGE( "\ntest001" );
   for(double eur=1.0; eur<5; ++eur) {
      std::this_thread::sleep_for(std::chrono::milliseconds(2)); // sleep for two seconds
      double conversion { eur * currency_HKD() };
      BOOST_TEST_MESSAGE( " Fake " << eur << " EUR = " << conversion << " HKD" );
      BOOST_CHECK( conversion > 0.0 );
   }
}
