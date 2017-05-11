package main

import (
	"fmt"
	"log"
	"math/rand"
	"net/http"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	host, port := cmdLine()
	fmt.Println("Fake Fixer.io at " + host + ":" + port)
	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe(host+":"+port, nil))
}

func cmdLine() (string, string) {

	// TODO: choose a better & fast seed
	rand.Seed(time.Now().UTC().UnixNano())

	host := "0.0.0.0"
	port := "8080"
	cmd := strings.Join(os.Args, " ")
	if strings.Contains(cmd, " help") || strings.Contains(cmd, " -help") || strings.Contains(cmd, " --help") ||
		strings.Contains(cmd, " -h") || strings.Contains(cmd, " /?") {
		fmt.Println("\nUsage: " + os.Args[0] + " <host> <port>\n")
		fmt.Println(" default host: " + host)
		fmt.Println(" default port: " + port)
		fmt.Println()
		os.Exit(0)
	}
	if len(os.Args) > 1 {
		host = os.Args[1]
	}
	if len(os.Args) > 2 {
		port = os.Args[2]
	}
	return host, port
}

func handler(w http.ResponseWriter, r *http.Request) {

	aud := 1.0 + rand.Float64()
	bgn := 1.0 + rand.Float64()
	brl := 3.0 + rand.Float64()
	cad := 1.0 + rand.Float64()
	chf := 1.0 + rand.Float64()
	cny := 7.0 + rand.Float64()
	czk := 26.0 + rand.Float64()
	dkk := 7.0 + rand.Float64()
	gbp := 0.0 + rand.Float64()
	hkd := 8.0 + rand.Float64()
	hrk := 7.0 + rand.Float64()
	huf := 312.0 + rand.Float64()
	idr := 14528.0 + rand.Float64()
	ils := 3.0 + rand.Float64()
	inr := 70.0 + rand.Float64()
	jpy := 122.0 + rand.Float64()
	krw := 1235.0 + rand.Float64()
	mxn := 20.0 + rand.Float64()
	myr := 4.0 + rand.Float64()
	nok := 9.0 + rand.Float64()
	nzd := 1.0 + rand.Float64()
	php := 54.0 + rand.Float64()
	pln := 4.0 + rand.Float64()
	ron := 4.0 + rand.Float64()
	rub := 62.0 + rand.Float64()
	sek := 9.0 + rand.Float64()
	sgd := 1.0 + rand.Float64()
	thb := 37.0 + rand.Float64()
	try := 3.0 + rand.Float64()
	usd := 1.0 + rand.Float64() // supposed EUR > USD := 1.0 + rand.Float64()
	zar := 14.0 + rand.Float64()

	year, month, day := time.Now().Date()

	w.Header().Set("Content-Type", "application/json")
	fmt.Fprintf(w, fmt.Sprintf("{\"base\":\"EUR\",\"date\":\"%d-%02d-%02d\",\"rates\":{\"AUD\":%s,\"BGN\":%s,\"BRL\":%s,\"CAD\":%s,\"CHF\":%s,\"CNY\":%s,\"CZK\":%s,\"DKK\":%s,\"GBP\":%s,\"HKD\":%s,\"HRK\":%s,\"HUF\":%s,\"IDR\":%s,\"ILS\":%s,\"INR\":%s,\"JPY\":%s,\"KRW\":%s,\"MXN\":%s,\"MYR\":%s,\"NOK\":%s,\"NZD\":%s,\"PHP\":%s,\"PLN\":%s,\"RON\":%s,\"RUB\":%s,\"SEK\":%s,\"SGD\":%s,\"THB\":%s,\"TRY\":%s,\"USD\":%s,\"ZAR\":%s}}",
		year, month, day,
		strconv.FormatFloat(aud, 'f', 4, 64),
		strconv.FormatFloat(bgn, 'f', 4, 64),
		strconv.FormatFloat(brl, 'f', 4, 64),
		strconv.FormatFloat(cad, 'f', 4, 64),
		strconv.FormatFloat(chf, 'f', 4, 64),
		strconv.FormatFloat(cny, 'f', 4, 64),
		strconv.FormatFloat(czk, 'f', 4, 64),
		strconv.FormatFloat(dkk, 'f', 4, 64),
		strconv.FormatFloat(gbp, 'f', 4, 64),
		strconv.FormatFloat(hkd, 'f', 4, 64),
		strconv.FormatFloat(hrk, 'f', 4, 64),
		strconv.FormatFloat(huf, 'f', 4, 64),
		strconv.FormatFloat(idr, 'f', 4, 64),
		strconv.FormatFloat(ils, 'f', 4, 64),
		strconv.FormatFloat(inr, 'f', 4, 64),
		strconv.FormatFloat(jpy, 'f', 4, 64),
		strconv.FormatFloat(krw, 'f', 4, 64),
		strconv.FormatFloat(mxn, 'f', 4, 64),
		strconv.FormatFloat(myr, 'f', 4, 64),
		strconv.FormatFloat(nok, 'f', 4, 64),
		strconv.FormatFloat(nzd, 'f', 4, 64),
		strconv.FormatFloat(php, 'f', 4, 64),
		strconv.FormatFloat(pln, 'f', 4, 64),
		strconv.FormatFloat(ron, 'f', 4, 64),
		strconv.FormatFloat(rub, 'f', 4, 64),
		strconv.FormatFloat(sek, 'f', 4, 64),
		strconv.FormatFloat(sgd, 'f', 4, 64),
		strconv.FormatFloat(thb, 'f', 4, 64),
		strconv.FormatFloat(try, 'f', 4, 64),
		strconv.FormatFloat(usd, 'f', 4, 64),
		strconv.FormatFloat(zar, 'f', 4, 64)))
}
