#include <Rcpp.h>
#include <getdns/getdns.h>
#include <getdns/getdns_extra.h>
#include <arpa/inet.h>
using namespace Rcpp;

//' Test whether an object is an external pointer
//'
//' @param x object to test
//' @keywords internal
// [[Rcpp::export]]
void check_is_xptr(SEXP s) {
  if (TYPEOF(s) != EXTPTRSXP) {
    Rf_error("expected an externalptr");
  }
}

//' Test whether an external pointer is null
//'
//' @param x object to test
//' @keywords internal
// [[Rcpp::export]]
SEXP is_null_xptr_(SEXP s) {
  check_is_xptr(s);
  void *r = (void *)R_ExternalPtrAddr(s);
  return wrap(r == NULL);
}

static void gctx_finalizer(SEXP ptr) {
  if(!R_ExternalPtrAddr(ptr)) return;
  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(ptr);
  if (ptr) getdns_context_destroy(ctxt);
  R_ClearExternalPtr(ptr); /* not really needed */
}

//' Internal version of gdns_resolver
//' @keywords internal
// [[Rcpp::export]]
SEXP int_gdns_resolver(std::vector< std::string > resolvers) {

  bool ok = false;
  SEXP ptr;
  getdns_return_t r;
  getdns_context *ctxt = NULL;

  // TODO Validate we don't need to free these
  getdns_dict *resolver_dict = getdns_dict_create();
  getdns_list *resolver_list = getdns_list_create();

  for (int i = 0; i<resolvers.size(); i++) {
    r = getdns_str2dict(resolvers[i].c_str(), &resolver_dict);
    r = getdns_list_set_dict(resolver_list, i, resolver_dict);
  }

  getdns_transport_list_t tls_transport[] = { GETDNS_TRANSPORT_TLS };

  if ((r = getdns_context_create(&ctxt, 1))) {
  } else if ((r = getdns_context_set_dns_transport_list(ctxt, 1, tls_transport))) {
  } else if ((r = getdns_context_set_upstream_recursive_servers(ctxt, resolver_list))) {
  } else if ((r = getdns_context_set_resolution_type(ctxt, GETDNS_RESOLUTION_STUB))) {
  } else {
    ok = true;
  }

  if (ok) {
    ptr = R_MakeExternalPtr(ctxt, Rf_install("gctx"), R_NilValue);
    R_RegisterCFinalizerEx(ptr, gctx_finalizer, TRUE);
    Rf_setAttrib(ptr, Rf_install("class"), Rf_mkString("gctx"));
    return(ptr);
  } else {
    return(R_NilValue);
  }

}

//' Resolve a host to an addrss
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @param host to lookup
//' @export
//' @examples
//' x <- gdns_resolver()
//' gdns_get_address(x, "yahoo.com")
//' x %>% gdns_get_address("yahoo.com")
// [[Rcpp::export]]
CharacterVector gdns_get_address(SEXP gctx, std::string host) {

  uint32_t err;
  size_t sz;
  getdns_return_t r;
  getdns_dict *resp = NULL;
  getdns_list *addrs;
  std::vector< std::string > out;
  bool ok = false;

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(CharacterVector());

  if ((r = getdns_address_sync(ctxt, host.c_str(), NULL, &resp))) {
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

      // TODO Validate we don't need to free these
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

  if (ok) return(wrap(out)); else return(CharacterVector());

}

// [[Rcpp::export]]
CharacterVector int_get_resolvers(SEXP gctx) {

  bool ok = false;
  size_t sz;
  getdns_list *addrs;
  std::vector< std::string > out;

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);
  if (gctx == NULL) return(CharacterVector());

  getdns_return_t r;

  if ((r = getdns_context_get_upstream_recursive_servers(ctxt, &addrs))) {
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

      // TODO Validate we don't need to free these
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

  if (addrs) getdns_list_destroy(addrs);

  if (ok) return(wrap(out)); else return(CharacterVector());

}


// [[Rcpp::export]]
CharacterVector int_gdns_query(SEXP gctx, std::string name, uint16_t rr) {

  uint32_t err;
  // size_t sz;
  getdns_return_t r;
  getdns_dict *resp = NULL;
  // getdns_list *results;
  std::string out;
  bool ok = false;

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);
  if (gctx == NULL) return(CharacterVector());

  if ((r = getdns_general_sync(ctxt, name.c_str(), rr, NULL, &resp))) {
  } else if ((r = getdns_dict_get_int(resp, "status", &err))) {
  } else if (err != GETDNS_RESPSTATUS_GOOD) {
  } else {
    ok = true;
  }

  if (ok) {

    char *charout = getdns_print_json_dict(resp, 0);
    if (charout) {
      out = std::string(charout);
      free(charout);
    } else {
      ok = false;
    }

  }

  if (resp) getdns_dict_destroy(resp);

  if (ok) return(wrap(out)); else return(CharacterVector());

}
