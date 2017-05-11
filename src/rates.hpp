#pragma once

#include <atomic>
#include <array>
#include <string>
#include <cstdio>

// debug
#include <iostream>

// checks
static_assert(sizeof(float) == sizeof(uint32_t), "Float should be as big as uint32_t for casts to properly work");

// useful for testing

// typical intial values for Rates objects from http://api.fixer.io/latest
static constexpr const char* const FIXER_IO_DEFAULT {R"(
{"base":"EUR","date":"2017-05-03","rates":{"AUD":1.4615,"BGN":1.9558,"BRL":3.4424,"CAD":1.499,"CHF":1.0812,"CNY":7.5267,"CZK":26.871,"DKK":7.4372,"GBP":0.8444,"HKD":8.4967,"HRK":7.4493,"HUF":312.15,"IDR":14528.0,"ILS":3.9495,"INR":70.054,"JPY":122.47,"KRW":1235.5,"MXN":20.536,"MYR":4.7159,"NOK":9.3878,"NZD":1.5768,"PHP":54.583,"PLN":4.1913,"RON":4.5485,"RUB":62.546,"SEK":9.6273,"SGD":1.5229,"THB":37.654,"TRY":3.8603,"USD":1.0919,"ZAR":14.573}}
)"};

// typical intial values for Rates objects from http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml
static constexpr const char* const ECB_EU_DEFAULT {R"(
<?xml version="1.0" encoding="UTF-8"?>
<gesmes:Envelope xmlns:gesmes="http://www.gesmes.org/xml/2002-08-01" xmlns="http://www.ecb.int/vocabulary/2002-08-01/eurofxref">
   <gesmes:subject>Reference rates</gesmes:subject>
   <gesmes:Sender>
   <gesmes:name>European Central Bank</gesmes:name>
   </gesmes:Sender>
   <Cube>
           <Cube time='2017-05-03'>
                   <Cube currency='USD' rate='1.0919'/>
                   <Cube currency='JPY' rate='122.47'/>
                   <Cube currency='BGN' rate='1.9558'/>
                   <Cube currency='CZK' rate='26.871'/>
                   <Cube currency='DKK' rate='7.4372'/>
                   <Cube currency='GBP' rate='0.84440'/>
                   <Cube currency='HUF' rate='312.15'/>
                   <Cube currency='PLN' rate='4.1913'/>
                   <Cube currency='RON' rate='4.5485'/>
                   <Cube currency='SEK' rate='9.6273'/>
                   <Cube currency='CHF' rate='1.0812'/>
                   <Cube currency='NOK' rate='9.3878'/>
                   <Cube currency='HRK' rate='7.4493'/>
                   <Cube currency='RUB' rate='62.5464'/>
                   <Cube currency='TRY' rate='3.8603'/>
                   <Cube currency='AUD' rate='1.4615'/>
                   <Cube currency='BRL' rate='3.4424'/>
                   <Cube currency='CAD' rate='1.4990'/>
                   <Cube currency='CNY' rate='7.5267'/>
                   <Cube currency='HKD' rate='8.4967'/>
                   <Cube currency='IDR' rate='14528.28'/>
                   <Cube currency='ILS' rate='3.9495'/>
                   <Cube currency='INR' rate='70.0540'/>
                   <Cube currency='KRW' rate='1235.52'/>
                   <Cube currency='MXN' rate='20.5365'/>
                   <Cube currency='MYR' rate='4.7159'/>
                   <Cube currency='NZD' rate='1.5768'/>
                   <Cube currency='PHP' rate='54.583'/>
                   <Cube currency='SGD' rate='1.5229'/>
                   <Cube currency='THB' rate='37.654'/>
                   <Cube currency='ZAR' rate='14.5730'/>
           </Cube>
   </Cube>
</gesmes:Envelope>
)"};

// only that couple of sites supported
enum class SITE : size_t { UNKNOWN = 0, ECB_EU = 1, FIXER_IO = 2 };

enum class CURRENCIES : size_t {
	AUD=0
	,BGN
	,BRL
	,CAD
	,CHF
	,CNY
	,CZK
	,DKK
	,GBP
	,HKD
	,HRK
	,HUF
	,IDR
	,ILS
	,INR
	,JPY
	,KRW
	,MXN
	,MYR
	,NOK
	,NZD
	,PHP
	,PLN
	,RON
	,RUB
	,SEK
	,SGD
	,THB
	,TRY
	,USD
	,ZAR
	,SIZE };

struct Rates final : std::array<std::atomic<uint32_t>, static_cast<size_t>(CURRENCIES::SIZE)> {

    using Values = std::array<float, static_cast<size_t>(CURRENCIES::SIZE)>;

    inline const unsigned year() const { return year_.load(); }
    inline const unsigned month() const { return month_.load(); }
    inline const unsigned day() const { return day_.load(); }

    inline const float AUD() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::AUD)).load()}; return *((float*)(&value)); }
    inline const float BGN() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::BGN)).load()}; return *((float*)(&value)); }
    inline const float BRL() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::BRL)).load()}; return *((float*)(&value)); }
    inline const float CAD() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::CAD)).load()}; return *((float*)(&value)); }
    inline const float CHF() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::CHF)).load()}; return *((float*)(&value)); }
    inline const float CNY() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::CNY)).load()}; return *((float*)(&value)); }
    inline const float CZK() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::CZK)).load()}; return *((float*)(&value)); }
    inline const float DKK() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::DKK)).load()}; return *((float*)(&value)); }
    inline const float GBP() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::GBP)).load()}; return *((float*)(&value)); }
    inline const float HKD() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::HKD)).load()}; return *((float*)(&value)); }
    inline const float HRK() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::HRK)).load()}; return *((float*)(&value)); }
    inline const float HUF() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::HUF)).load()}; return *((float*)(&value)); }
    inline const float IDR() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::IDR)).load()}; return *((float*)(&value)); }
    inline const float ILS() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::ILS)).load()}; return *((float*)(&value)); }
    inline const float INR() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::INR)).load()}; return *((float*)(&value)); }
    inline const float JPY() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::JPY)).load()}; return *((float*)(&value)); }
    inline const float KRW() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::KRW)).load()}; return *((float*)(&value)); }
    inline const float MXN() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::MXN)).load()}; return *((float*)(&value)); }
    inline const float MYR() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::MYR)).load()}; return *((float*)(&value)); }
    inline const float NOK() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::NOK)).load()}; return *((float*)(&value)); }
    inline const float NZD() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::NZD)).load()}; return *((float*)(&value)); }
    inline const float PHP() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::PHP)).load()}; return *((float*)(&value)); }
    inline const float PLN() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::PLN)).load()}; return *((float*)(&value)); }
    inline const float RON() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::RON)).load()}; return *((float*)(&value)); }
    inline const float RUB() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::RUB)).load()}; return *((float*)(&value)); }
    inline const float SEK() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::SEK)).load()}; return *((float*)(&value)); }
    inline const float SGD() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::SGD)).load()}; return *((float*)(&value)); }
    inline const float THB() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::THB)).load()}; return *((float*)(&value)); }
    inline const float TRY() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::TRY)).load()}; return *((float*)(&value)); }
    inline const float USD() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::USD)).load()}; return *((float*)(&value)); }
    inline const float ZAR() const { const uint32_t value {at(static_cast<size_t>(CURRENCIES::ZAR)).load()}; return *((float*)(&value)); }

    Rates() {
	// init to zero
	year_.store(0); month_.store(0); day_.store(0);
	for( auto&& i : *this ) { i.store(0); }
    }

    bool update(const char* const input = nullptr) {

	if(not input) { return false; }

	unsigned y{}, m{}, d{};
	Values values {};
	switch( whatSite(input, y, m, d, values) ) {

		// do nothing
		default: return false;

		case SITE::FIXER_IO:
		case SITE::ECB_EU:
		    year_.store(y); month_.store(m); day_.store(d);
		    // Roy, don't cry victory; I'm keeping on raising an eyebrow about these c-style casts
		    for( size_t i = 0; i < values.size(); ++i ) { at(i).store(*((uint32_t*)(&values[i]))); }
		    return true;
	}
    }

private:

    std::atomic<unsigned> year_{};
    std::atomic<unsigned> month_{};
    std::atomic<unsigned> day_{};

    // EUR2017-05-03AUD1.4615BGN1.9558BRL3.4424CAD1.499CHF1.0812CNY7.5267CZK26.871DKK7.4372GBP0.8444HKD8.4967HRK7.4493HUF312.15IDR14528.0ILS3.9495INR70.054JPY122.47KRW1235.5MXN20.536MYR4.7159NOK9.3878NZD1.5768PHP54.583PLN4.1913RON4.5485RUB62.546SEK9.6273SGD1.5229THB37.654TRY3.8603USD1.0919ZAR14.5731.0UTF-8E..
    // 1.0UTF-8E..2002-08-01..2002-08-01RSECBSCC2017-05-03CUSD1.0919CJPY122.47CBGN1.9558CCZK26.871CDKK7.4372CGBP0.84440CHUF312.15CPLN4.1913CRON4.5485CSEK9.6273CCHF1.0812CNOK9.3878CHRK7.4493CRUB62.5464CTRY3.8603CAUD1.4615CBRL3.4424CCAD1.4990CCNY7.5267CHKD8.4967CIDR14528.28CILS3.9495CINR70.0540CKRW1235.52CMXN20.5365CMYR4.7159CNZD1.5768CPHP54.583CSGD1.5229CTHB37.654CZAR14.5730CCE
    static inline std::string reduce(const char* const input) {
	if(not input) { return std::string{}; }
	std::string result;
	result.reserve(strlen(input));
	for(size_t i=0; i<strlen(input); ++i) {
		if( iscntrl(input[i]) || not isprint(input[i]) || input[i] == '\n' || input[i] == '\r') { continue; }
		if( isdigit(input[i]) || input[i] == '.' || input[i] == '-' ) { result += input[i]; continue; }
		if( isalnum(input[i]) && isupper(input[i]) ) { result += input[i]; continue; }
	}
	return result;
    }

    /** very dependent on the exact match from sites **/
    /** if they changes its replies, some recoding will be needed **/
    static inline SITE whatSite(const char* const input, unsigned& y, unsigned& m, unsigned&d, Values& v) {

	// year, month, day + all the currencies
	static constexpr const size_t SUCCESS {3 + static_cast<size_t>(CURRENCIES::SIZE)};
	size_t matches {};

	// EUR2017-05-03AUD1.4615BGN1.9558BRL3.4424CAD1.499CHF1.0812CNY7.5267CZK26.871DKK7.4372GBP0.8444HKD8.4967HRK7.4493HUF312.15IDR14528.0ILS3.9495INR70.054JPY122.47KRW1235.5MXN20.536MYR4.7159NOK9.3878NZD1.5768PHP54.583PLN4.1913RON4.5485RUB62.546SEK9.6273SGD1.5229THB37.654TRY3.8603USD1.0919ZAR14.5731.0UTF-8E..
	matches = sscanf(reduce(input).c_str(),
				"EUR%u-%u-%uAUD%fBGN%fBRL%fCAD%fCHF%fCNY%fCZK%fDKK%fGBP%fHKD%fHRK%fHUF%fIDR%fILS%fINR%fJPY%fKRW%fMXN%fMYR%fNOK%fNZD%fPHP%fPLN%fRON%fRUB%fSEK%fSGD%fTHB%fTRY%fUSD%fZAR%f",
				&y, &m, &d,
				&v[static_cast<size_t>(CURRENCIES::AUD)],
				&v[static_cast<size_t>(CURRENCIES::BGN)],
				&v[static_cast<size_t>(CURRENCIES::BRL)],
				&v[static_cast<size_t>(CURRENCIES::CAD)],
				&v[static_cast<size_t>(CURRENCIES::CHF)],
				&v[static_cast<size_t>(CURRENCIES::CNY)],
				&v[static_cast<size_t>(CURRENCIES::CZK)],
				&v[static_cast<size_t>(CURRENCIES::DKK)],
				&v[static_cast<size_t>(CURRENCIES::GBP)],
				&v[static_cast<size_t>(CURRENCIES::HKD)],
				&v[static_cast<size_t>(CURRENCIES::HRK)],
				&v[static_cast<size_t>(CURRENCIES::HUF)],
				&v[static_cast<size_t>(CURRENCIES::IDR)],
				&v[static_cast<size_t>(CURRENCIES::ILS)],
				&v[static_cast<size_t>(CURRENCIES::INR)],
				&v[static_cast<size_t>(CURRENCIES::JPY)],
				&v[static_cast<size_t>(CURRENCIES::KRW)],
				&v[static_cast<size_t>(CURRENCIES::MXN)],
				&v[static_cast<size_t>(CURRENCIES::MYR)],
				&v[static_cast<size_t>(CURRENCIES::NOK)],
				&v[static_cast<size_t>(CURRENCIES::NZD)],
				&v[static_cast<size_t>(CURRENCIES::PHP)],
				&v[static_cast<size_t>(CURRENCIES::PLN)],
				&v[static_cast<size_t>(CURRENCIES::RON)],
				&v[static_cast<size_t>(CURRENCIES::RUB)],
				&v[static_cast<size_t>(CURRENCIES::SEK)],
				&v[static_cast<size_t>(CURRENCIES::SGD)],
				&v[static_cast<size_t>(CURRENCIES::THB)],
				&v[static_cast<size_t>(CURRENCIES::TRY)],
				&v[static_cast<size_t>(CURRENCIES::USD)],
				&v[static_cast<size_t>(CURRENCIES::ZAR)]
				);

	if( matches == SUCCESS ) { return SITE::FIXER_IO; }

	/*** PAY ATTENTION to the ORDER: ECB returns currencies in its own 'european' order ***/

	// 1.0UTF-8E..2002-08-01..2002-08-01RSECBSCC2017-05-03CUSD1.0919CJPY122.47CBGN1.9558CCZK26.871CDKK7.4372CGBP0.84440CHUF312.15CPLN4.1913CRON4.5485CSEK9.6273CCHF1.0812CNOK9.3878CHRK7.4493CRUB62.5464CTRY3.8603CAUD1.4615CBRL3.4424CCAD1.4990CCNY7.5267CHKD8.4967CIDR14528.28CILS3.9495CINR70.0540CKRW1235.52CMXN20.5365CMYR4.7159CNZD1.5768CPHP54.583CSGD1.5229CTHB37.654CZAR14.5730CCE
	matches = sscanf(reduce(input).c_str(),
				"1.0UTF-8E..2002-08-01..2002-08-01RSECBSCC%u-%u-%uCUSD%fCJPY%fCBGN%fCCZK%fCDKK%fCGBP%fCHUF%fCPLN%fCRON%fCSEK%fCCHF%fCNOK%fCHRK%fCRUB%fCTRY%fCAUD%fCBRL%fCCAD%fCCNY%fCHKD%fCIDR%fCILS%fCINR%fCKRW%fCMXN2%fCMYR%fCNZD%fCPHP%fCSGD%fCTHB%fCZAR%fCCE",
				&y, &m, &d,
				&v[static_cast<size_t>(CURRENCIES::USD)],
				&v[static_cast<size_t>(CURRENCIES::JPY)],
				&v[static_cast<size_t>(CURRENCIES::BGN)],
				&v[static_cast<size_t>(CURRENCIES::CZK)],
				&v[static_cast<size_t>(CURRENCIES::DKK)],
				&v[static_cast<size_t>(CURRENCIES::GBP)],
				&v[static_cast<size_t>(CURRENCIES::HUF)],
				&v[static_cast<size_t>(CURRENCIES::PLN)],
				&v[static_cast<size_t>(CURRENCIES::RON)],
				&v[static_cast<size_t>(CURRENCIES::SEK)],
				&v[static_cast<size_t>(CURRENCIES::CHF)],
				&v[static_cast<size_t>(CURRENCIES::NOK)],
				&v[static_cast<size_t>(CURRENCIES::HRK)],
				&v[static_cast<size_t>(CURRENCIES::RUB)],
				&v[static_cast<size_t>(CURRENCIES::TRY)],
				&v[static_cast<size_t>(CURRENCIES::AUD)],
				&v[static_cast<size_t>(CURRENCIES::BRL)],
				&v[static_cast<size_t>(CURRENCIES::CAD)],
				&v[static_cast<size_t>(CURRENCIES::CNY)],
				&v[static_cast<size_t>(CURRENCIES::HKD)],
				&v[static_cast<size_t>(CURRENCIES::IDR)],
				&v[static_cast<size_t>(CURRENCIES::ILS)],
				&v[static_cast<size_t>(CURRENCIES::INR)],
				&v[static_cast<size_t>(CURRENCIES::KRW)],
				&v[static_cast<size_t>(CURRENCIES::MXN)],
				&v[static_cast<size_t>(CURRENCIES::MYR)],
				&v[static_cast<size_t>(CURRENCIES::NZD)],
				&v[static_cast<size_t>(CURRENCIES::PHP)],
				&v[static_cast<size_t>(CURRENCIES::SGD)],
				&v[static_cast<size_t>(CURRENCIES::THB)],
				&v[static_cast<size_t>(CURRENCIES::ZAR)]
				);


	if( matches == SUCCESS ) { return SITE::ECB_EU; }

	// FAILED
	y = m = d = 0; for(auto&& i : v) { i=0.0; }; return SITE::UNKNOWN;
    }

};

