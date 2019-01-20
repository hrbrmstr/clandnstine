#include <Rcpp.h>
#include <getdns/getdns.h>
#include <getdns/getdns_extra.h>
#include <arpa/inet.h>
using namespace Rcpp;

//' Lookup IP Address(es) for a Given Host
//'
//' @param host host (length 1 <chr>)
//' @param resolver resolver address. defaults to Quad9; (length 1 <chr>)
//' @export
//' @examples
//' get_address("r-project.org")
//' get_address("yahoo.com", "1.1.1.1")
//' get_address("microsoft.com", "8.8.8.8")
// [[Rcpp::export]]
CharacterVector get_address(std::string host, std::string resolver = "9.9.9.9") {

  uint32_t err;
  size_t sz;
  getdns_return_t r;
  getdns_context *ctxt = NULL;
  getdns_dict *resp = NULL;
  getdns_list *addrs;
  std::vector< std::string > out;
  bool ok = false;

  getdns_dict *resolver_dict = getdns_dict_create();
  r = getdns_str2dict(resolver.c_str(), &resolver_dict);

  getdns_list *resolver_list = getdns_list_create();
  r = getdns_list_set_dict(resolver_list, 0, resolver_dict);

  getdns_transport_list_t tls_transport[] = { GETDNS_TRANSPORT_TLS };

  if ((r = getdns_context_create(&ctxt, 1))) {
  } else if ((r = getdns_context_set_dns_transport_list(ctxt, 1, tls_transport))) {
  } else if ((r = getdns_context_set_upstream_recursive_servers(ctxt, resolver_list))) {
  } else if ((r = getdns_context_set_resolution_type(ctxt, GETDNS_RESOLUTION_STUB))) {
  } else if ((r = getdns_address_sync(ctxt, host.c_str(), NULL, &resp))) {
  } else if ((r = getdns_dict_get_int(resp, "status", &err))) {
  } else if (err != GETDNS_RESPSTATUS_GOOD) {
  } else if ((r = getdns_dict_get_list(resp, "just_address_answers", &addrs))) {
  } else if (r != GETDNS_RETURN_GOOD) {
  } else if ((r = getdns_list_get_length(addrs, &sz))) {
  } else {
    ok = true;
  }

  if (ok) {

    out.reserve(sz);

    for (size_t i = 0; i < sz; ++i) {

      getdns_dict *cur_addr;
      getdns_bindata *address;

      r = getdns_list_get_dict(addrs, i, &cur_addr);
      r = getdns_dict_get_bindata(cur_addr, "address_data", &address);

      if (address->size == 4 || address->size == 16) { // this is unlikely to be bad
        char *addr_str = getdns_display_ip_address(address);
        out.push_back(addr_str);
        if (addr_str) free(addr_str);
      }

    }

    out.shrink_to_fit();

  }

  if (resp) getdns_dict_destroy(resp);
  if (ctxt) getdns_context_destroy(ctxt);

  if (ok) return(wrap(out)); else return(CharacterVector());

}
