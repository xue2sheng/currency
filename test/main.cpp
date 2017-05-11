#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE UnitTest

#include <boost/test/unit_test.hpp>

#include <thread>
#include <chrono>
#include <limits>
#include <cmath>
#include "currency.h"
#include "../src/rates.hpp"

// just logging something ( --log_level=message )

struct GlobalInit {
  GlobalInit() {
	assert(CURRENCY_IN_SYNC(CURRENCY_VERSION));
	currency_global_init();
  }
  ~GlobalInit() {}
};
BOOST_GLOBAL_FIXTURE( GlobalInit );

BOOST_AUTO_TEST_CASE( test000 ) {
   BOOST_TEST_MESSAGE( "\ntest0000" );
   Rates rates;

   rates.update(FIXER_IO_DEFAULT);
   BOOST_TEST_MESSAGE( "Fixer date:\t " << rates.year() << '-' << rates.month() << '-' << rates.day() << "\t USD rate: " << rates.USD() );
   BOOST_CHECK(rates.year() == 2017 );
   BOOST_CHECK( std::abs(rates.USD() - 1.0919) <= std::numeric_limits<float>::epsilon() );

   rates.update(ECB_EU_DEFAULT);
   BOOST_TEST_MESSAGE( "ECB date:\t " << rates.year() << '-' << rates.month() << '-' << rates.day() << "\t USD rate: " << rates.USD() );
   BOOST_CHECK(rates.year() == 2017 );
   BOOST_CHECK( std::abs(rates.USD() - 1.0919) <= std::numeric_limits<float>::epsilon() );
}


BOOST_AUTO_TEST_CASE( test001 ) {
   BOOST_TEST_MESSAGE( "\ntest0001" );
   double rate {currency_USD()};
   BOOST_TEST_MESSAGE( " USD Exchange Rate: " << rate );
   BOOST_CHECK( rate > 0.0 );
}

BOOST_AUTO_TEST_CASE( test002 ) {
   BOOST_TEST_MESSAGE( "\ntest0002" );
   for(double usd=1.0; usd<5; ++usd) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      double conversion { usd / currency_USD() };
      BOOST_TEST_MESSAGE( " " << usd << " USD = " << conversion << " EUR" );
      BOOST_CHECK( conversion > 0.0 );
   }
}

BOOST_AUTO_TEST_CASE( test003 ) {
   BOOST_TEST_MESSAGE( "\ntest0003" );
   for(double eur=1.0; eur<5; ++eur) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      double conversion { eur * currency_USD() };
      BOOST_TEST_MESSAGE( " " << eur << " EUR = " << conversion << " USD" );
      BOOST_CHECK( conversion > 0.0 );
   }
}

BOOST_AUTO_TEST_CASE( test004 ) {
   BOOST_TEST_MESSAGE( "\ntest0004" );
   for(double eur=1.0; eur<5; ++eur) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      double conversion { eur * currency_HKD() };
      BOOST_TEST_MESSAGE( " " << eur << " EUR = " << conversion << " HKD <-- " << (currency_last_query()?"crisp data":"stale data") );
      BOOST_CHECK( conversion > 0.0 );
   }
}
