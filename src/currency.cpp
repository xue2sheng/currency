/** @file currency.cpp
 * @brief Basic funcionality to access to the remoto site.
 *
 */

#include <iostream>
#include <thread>
#include <chrono> 
#include <cstring>
#include <mutex>
#include <string>
#include <cstdio>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <atomic>
#include <curl/curl.h>

#include "currency.h"
#include "version.h"
#include "rates.hpp"

/********** Internal implementation ***************/

/// @brief Currency Namespace in order to avoid interferencies.
namespace currency
{
    /// @brief fixer.io site plus conversion paremeters.
    static constexpr const char * const FIXER_URL {CURRENCY_FIXER_URL};

    /// @brief ecb.eu site plus conversion paremeters.
    static constexpr const char * const ECB_URL {CURRENCY_ECB_URL};

    /// @brief internal flag & mutex.
    static std::once_flag INIT_FLAG {};

    /// @brief internal rates.
    static Rates RATES {};

    /// @brief flag about last query to external sites
    static std::atomic<bool> LAST_QUERY_SUCCESS {false};

    /// @brief specific string.
    struct curl_string {
          char *ptr {nullptr};
          size_t len {0};
    };

/* 
@startuml{conversion.png}

skinparam state { 
BackgroundColor White 
}

[*] --> Init 
Init --> AtomicIntegers : Only once 
AtomicIntegers : No need for mutexes

[*] --> WakeUp : Only one\nDetached Thread
Sleep --> WakeUp
Init : Initial values for rate atomic integers
Sleep : Wait X minutes before waking up detached thread
WakeUp: Grab rate exchanges from a couple of external sites
WakeUp: Store rate exchanges into static atomic integers
WakeUp --> Sleep 
WakeUp -left-> AtomicIntegers
  
[*] --> NormalExecution : Usual Multitheaded\nJoinable Threads
NormalExecution -down-> ReadRateExchange
NormalExecution : Multithreaded code
ReadRateExchange : Load rate exchange integer and transform it into float
ReadRateExchange -up-> NormalExecution
AtomicIntegers -left-> ReadRateExchange
NormalExecution -left-> [*]

@enduml
*/
  
    /** 
     * @brief Utility to access external site and update internal cache exchange rate value. 
     * 
     *
     * @image html conversion.png     
     */
    struct Conversion {
	    Conversion(const unsigned int minutes = CURRENCY_MINUTES, const std::string fake_url = std::string{})
		    : minutes_{minutes}, fake_url_{fake_url} {
            curl_global_init(CURL_GLOBAL_ALL);
            updateRate();
          }
          inline void operator()() {
              while(true) {
                // for unit testing consider minutes as seconds.
		if(not fake_url_.empty()) { std::this_thread::sleep_for(std::chrono::seconds(minutes_)); }
                else { std::this_thread::sleep_for(std::chrono::minutes(minutes_)); }
		updateRate();
              }
	  }
      private:
	  unsigned int minutes_;
	  std::string fake_url_;
          inline static void init_string(struct curl_string *s) {
                s->len = 0;
                s->ptr = static_cast<char*>(malloc(s->len+1));
                if (s->ptr == nullptr) { return; }
                s->ptr[0] = '\0';
          }
          static size_t writefunc(void *ptr, size_t size, size_t nmemb, struct curl_string *s)
          {
               size_t new_len = s->len + size*nmemb;
               s->ptr =static_cast<char*>(realloc(s->ptr, new_len+1));
               if (s->ptr == nullptr) { return 0; }
               memcpy(s->ptr+s->len, ptr, size*nmemb);
               s->ptr[new_len] = '\0';
               s->len = new_len;
               return size*nmemb;
	  }
	  bool updateRateFrom(const char* const url) {
	     bool success {false};
	     CURL *curl {nullptr};
	     curl_string s;
	     currency::Conversion::init_string(&s);
	     if(s.ptr) {
	      try {
	       curl = curl_easy_init();
	       if(curl) {
		  curl_easy_setopt(curl, CURLOPT_URL, url);
		  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5); // 5 seconds
		  if(CURLE_OK == curl_easy_perform(curl)) { if( s.len > 0 ) { success = RATES.update(s.ptr); } }
		}
		if(s.ptr) { free(s.ptr); s.ptr = nullptr; }
		if(curl) { curl_easy_cleanup(curl);  curl = nullptr; }
		return success;
	      } catch(...) {
		  if(s.ptr) { free(s.ptr); }
		  if(curl) { curl_easy_cleanup(curl); }
	      }
	  }
	  return false;
	}

	  /*** supposed there will be just one (detached) thread calling this function --> avoid using mutex or similar ***/
	  void updateRate() {

        // in order to use the mock
        if( not fake_url_.empty() ) { LAST_QUERY_SUCCESS.store(updateRateFrom(fake_url_.c_str())); return; }
            
	    if( not updateRateFrom(FIXER_URL) ) {

		if( not updateRateFrom(ECB_URL) ) {

			LAST_QUERY_SUCCESS.store(false);

		} else { LAST_QUERY_SUCCESS.store(true); }

	    } else { LAST_QUERY_SUCCESS.store(true); }
          }
    };
}

/************** Public C API for clients ******************/

/**
 * @brief Check header & library version.
 * @param [in] version from header info.
 * @return true if success, false otherwise
 *
 * @remark Try to use with the pattern: assert(CURRENCY_IN_SYNC(CURRENCY_VERSION));
 */
bool CURRENCY_IN_SYNC(const unsigned long long int version) { return version == CURRENCY_VERSION; }

/**
 * @brief Helper to initialise CURL library and internal global structures.
 * @param [in] minutes: Sleep time in minutes between calls to the external site.
 * @param [in] fake_url: Fake external site query used by UNIT TEST code.
 *
 * @remark Only provided a new url for unit testing. On that scenario, 'minutes' will be applied as 'seconds'.
 */
void currency_global_init(const unsigned int minutes, const char* const fake_url) {
    std::call_once(currency::INIT_FLAG, [minutes, fake_url](){
	if(fake_url) { std::thread{currency::Conversion{minutes, std::string{fake_url}}}.detach(); }
	else { std::thread{currency::Conversion{minutes}}.detach(); }

    });
}

/**
 * @brief Helper to check it out that last query to some of the servers went successfully
 * @return true if success, false otherwise
 *
 * @remark before the very first query, it returns false
 */
bool currency_last_query() { return currency::LAST_QUERY_SUCCESS.load(); }

/**
 * @brief Helper to check it out that last query to some of the servers went successfully
 * @param [out] year read for the last time.
 * @param [out] month read for the last time.
 * @param [out] day read for the last time.
 * @return true if success, false otherwise
 *
 * @remark before the very first query, it returns false and year, month & day probably will be zero.
 */
bool currency_last_query_date(unsigned& year, unsigned& month, unsigned& day) {
	year = currency::RATES.year(); month = currency::RATES.month(); day = currency::RATES.day();
	return currency::LAST_QUERY_SUCCESS.load();
}

/**
* @brief Helper to USD (US dollar)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_USD() { return currency::RATES.USD(); }

/**
* @brief Helper to JPY (Japanese yen)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_JPY() { return currency::RATES.JPY(); }

/**
* @brief Helper to BGN (Bulgarian lev)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_BGN() { return currency::RATES.BGN(); }

/**
* @brief Helper to CZK (Czech koruna)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_CZK() { return currency::RATES.CZK(); }

/**
* @brief Helper to DKK (Danish krone)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_DKK() { return currency::RATES.DKK(); }

/**
* @brief Helper to GBP (Pound sterling)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_GBP() { return currency::RATES.GBP(); }

/**
* @brief Helper to HUF (Hungarian forint)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_HUF() { return currency::RATES.HUF(); }

/**
* @brief Helper to PLN (Polish zloty)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_PLN() { return currency::RATES.PLN(); }

/**
* @brief Helper to RON (Romanian leu)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_RON() { return currency::RATES.RON(); }

/**
* @brief Helper to SEK (Swedish krona)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_SEK() { return currency::RATES.SEK(); }

/**
* @brief Helper to CHF (Swiss franc)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_CHF() { return currency::RATES.CHF(); }

/**
* @brief Helper to NOK (Norwegian krone)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_NOK() { return currency::RATES.NOK(); }

/**
* @brief Helper to HRK (Croatian kuna)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_HRK() { return currency::RATES.HRK(); }

/**
* @brief Helper to RUB (Russian rouble)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_RUB() { return currency::RATES.RUB(); }

/**
* @brief Helper to TRY (Turkish lira)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_TRY() { return currency::RATES.TRY(); }

/**
* @brief Helper to AUD (Australian dollar)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_AUD() { return currency::RATES.AUD(); }

/**
* @brief Helper to BRL (Brazilian real)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_BRL() { return currency::RATES.BRL(); }

/**
* @brief Helper to CAD (Canadian dollar)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_CAD() { return currency::RATES.CAD(); }

/**
* @brief Helper to CNY (Chinese yuan renminbi)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_CNY() { return currency::RATES.CNY(); }

/**
* @brief Helper to HKD (Hong Kong dollar)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_HKD() { return currency::RATES.HKD(); }

/**
* @brief Helper to IDR (Indonesian rupiah)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_IDR() { return currency::RATES.IDR(); }

/**
* @brief Helper to ILS (Israeli shekel)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_ILS() { return currency::RATES.ILS(); }

/**
* @brief Helper to INR (Indian rupee)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_INR() { return currency::RATES.INR(); }

/**
* @brief Helper to KRW (South Korean won)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_KRW() { return currency::RATES.KRW(); }

/**
* @brief Helper to MXN (Mexican peso)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_MXN() { return currency::RATES.MXN(); }

/**
* @brief Helper to MYR (Malaysian ringgit)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_MYR() { return currency::RATES.MYR(); }

/**
* @brief Helper to NZD (New Zealand dollar)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_NZD() { return currency::RATES.NZD(); }

/**
* @brief Helper to PHP (Philippine peso)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_PHP() { return currency::RATES.PHP(); }

/**
* @brief Helper to SGD (Singapore dollar)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_SGD() { return currency::RATES.SGD(); }

/**
* @brief Helper to THB (Thai baht)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_THB() { return currency::RATES.THB(); }

/**
* @brief Helper to ZAR (South African rand)
* @return rate exchange with EUR (Euro) as base.
*
* @remark check last query status to know whether data is stale or not.
*/
float currency_ZAR() { return currency::RATES.ZAR(); }

