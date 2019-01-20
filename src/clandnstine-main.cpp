#include <Rcpp.h>
#include <getdns/getdns.h>
#include <getdns/getdns_extra.h>
#include <arpa/inet.h>
using namespace Rcpp;


//' Return gdns library version
//'
//' @export
// [[Rcpp::export]]
std::string gdns_lib_version() {
  return(std::string(getdns_get_version()));
}


// CharacterVector int_gdns_list_to_r() {
//
//   getdns_list *gl;
//
//   std::string out;
//
//   // if (!lst) return(CharacterVector());
//   //
//   // char *res = getdns_print_json_list(lst, 0);
//   // if (res) {
//   //   out = std::string(res);
//   //   free(res);
//   // } else {
//   //   return(CharacterVector());
//   // }
//
//   return(wrap(out));
//
// }
//
