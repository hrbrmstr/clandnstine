#include <Rcpp.h>

#include <getdns/getdns.h>
#include <getdns/getdns_extra.h>

#include <arpa/inet.h>

using namespace Rcpp;

// [[Rcpp::export]]
CharacterVector int_dns_wire_to_list(SEXP buf) {

  getdns_return_t r;
  bool ok = true;

  getdns_dict *resp;
  std::string out;

  r = getdns_wire2msg_dict(RAW(buf), LENGTH(buf), &resp);

  if (r == GETDNS_RETURN_GOOD) {

    char *charout = getdns_print_json_dict(resp, 0);

    if (charout) {
      out = std::string(charout);
      free(charout);
    } else {
      ok = false;
    }

  } else {
    ok = false;
  }

  if (resp) getdns_dict_destroy(resp);

  if (ok) return(wrap(out)); else return(CharacterVector());

}

// getdns_wire2rr_dict 	(	const uint8_t * 	wire,
//                        size_t 	wire_sz,
//                        getdns_dict ** 	rr_dict
// )
