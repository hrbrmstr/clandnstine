#include <Rcpp.h>
#include <getdns/getdns.h>
#include <getdns/getdns_extra.h>
#include <arpa/inet.h>
using namespace Rcpp;

extern void check_is_xptr(SEXP s);
//' Return gdns library version
//'
//' @export
// [[Rcpp::export]]
std::string gdns_lib_version() {
  return(std::string(getdns_get_version()));
}

//' Internal version of gdns_update_resolvers
//' @keywords internal
// [[Rcpp::export]]
SEXP int_gdns_update_resolvers(SEXP gctx, std::vector< std::string > resolvers) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;

  // TODO Validate we don't need to free these
  getdns_dict *resolver_dict = getdns_dict_create();
  getdns_list *resolver_list = getdns_list_create();

  for (int i = 0; i<resolvers.size(); i++) {
    r = getdns_str2dict(resolvers[i].c_str(), &resolver_dict);
    r = getdns_list_set_dict(resolver_list, i, resolver_dict);
  }

  if ((r = getdns_context_set_upstream_recursive_servers(ctxt, resolver_list))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);

}


//' Specify the number of milliseconds to wait for request to return
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @param timeout number of milliseconds (integer; i.e. not-fractional)
//' @export
// [[Rcpp::export]]
SEXP gdns_set_timeout(SEXP gctx, long timeout) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(CharacterVector());

  getdns_return_t r;

  if ((r = getdns_context_set_timeout(ctxt, (uint64_t)timeout))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);

}

//' Retreive the number of milliseconds to wait for request to return
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @export
// [[Rcpp::export]]
DoubleVector gdns_get_timeout(SEXP gctx) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;
  uint64_t timeout;

  if ((r = getdns_context_get_timeout(ctxt, &timeout))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  DoubleVector out(1);
  out[0] = (uint32_t)timeout;

  return(out);

}

//' Set/unset context to round robin queries over the available upstreams
//' when resolving with the stub resolution type.
//'
//' @md
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @param flag if `TRUE` (the default) round robin queries when using more than one stub resolver,
//' @export
// [[Rcpp::export]]
SEXP gdns_set_round_robin_upstreams(SEXP gctx, bool flag=true) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;

  if ((r = getdns_context_set_round_robin_upstreams(ctxt, flag ? 1 : 0))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);

}

//' Internal version of gdns_set_hosts()
//' @keywords internal
// [[Rcpp::export]]
SEXP int_gdns_set_hosts(SEXP gctx, std::string hosts) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;

  if ((r = getdns_context_set_hosts(ctxt, hosts.c_str()))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);

}

//' Internal version of set_transports()
//' @keywords internal
// [[Rcpp::export]]
SEXP int_gdns_set_transports(SEXP gctx, IntegerVector trans) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;

  getdns_transport_list_t tls_transport[trans.size()];
  for (int i=0; i<trans.size(); i++) {
    switch(trans[i]) {
    case 1200 : tls_transport[i] = GETDNS_TRANSPORT_UDP; break;
    case 1201 : tls_transport[i] = GETDNS_TRANSPORT_TCP; break;
    case 1202 : tls_transport[i] = GETDNS_TRANSPORT_TLS; break;
    }
  }

  if ((r = getdns_context_set_dns_transport_list(ctxt, trans.size(), tls_transport))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);
}


//' Internal version of gdns_set_resolution_type()
//' @keywords internal
// [[Rcpp::export]]
SEXP int_gdns_set_resolution_type(SEXP gctx, int res_type) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;

  if ((r = getdns_context_set_resolution_type(ctxt, res_type == 520 ? GETDNS_RESOLUTION_STUB : GETDNS_RESOLUTION_RECURSING))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);

}

//' Retreive what transports are used for DNS lookups.
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @export
// [[Rcpp::export]]
CharacterVector gdns_get_transports(SEXP gctx) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;
  size_t sz;
  getdns_transport_list_t *trans;

  if ((r = getdns_context_get_dns_transport_list(ctxt, &sz, &trans))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  CharacterVector out(sz);

  for (int i=0; i<sz; i++) {
    switch(trans[i]) {
    case GETDNS_TRANSPORT_UDP : out[i] = "udp"; break;
    case GETDNS_TRANSPORT_TCP : out[i] = "tcp"; break;
    case GETDNS_TRANSPORT_TLS : out[i] = "tls"; break;
    }
  }

  if (trans) free(trans);

  return(out);

}

//' Retreive the value of the localnames namespace
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @export
// [[Rcpp::export]]
CharacterVector gdns_get_hosts(SEXP gctx) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;
  const char *hosts;

  if ((r = getdns_context_get_hosts(ctxt, &hosts))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(std::string(hosts));

}

//' Retreive the value with which the context's upstream recursive servers and suffixes were initialized
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @export
// [[Rcpp::export]]
CharacterVector gdns_get_resolvconf(SEXP gctx) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;
  const char *resolv;

  if ((r = getdns_context_get_resolvconf(ctxt, &resolv))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(std::string(resolv));

}

//' Retreive the value with which the context's upstream recursive servers and suffixes were initialized
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @export
// [[Rcpp::export]]
StringVector gdns_get_tls_ca_path(SEXP gctx) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;
  const char *ca_path;

  if ((r = getdns_context_get_tls_ca_path(ctxt, &ca_path))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(ca_path ? std::string(ca_path) : CharacterVector());

}

//' Retreive the file location with CA certificates for verification purposes
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @export
// [[Rcpp::export]]
StringVector gdns_get_tls_ca_file(SEXP gctx) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;
  const char *ca_file;

  if ((r = getdns_context_get_tls_ca_path(ctxt, &ca_file))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(ca_file ? std::string(ca_file) : CharacterVector());

}

//' Specify where the location for CA certificates for verification purposes are located
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @param ca_path directory with Certificate Authority certificates
//' @export
// [[Rcpp::export]]
SEXP gdns_set_tls_ca_path(SEXP gctx, std::string ca_path) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;

  if ((r = getdns_context_set_tls_ca_path(ctxt, ca_path.c_str()))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);

}

//' Specify the file with CA certificates for verification purposes
//'
//' @param gctx gdns resolver context created with [gdns_resolver()]
//' @param ca_file file with Certificate Authority certificates
//' @export
// [[Rcpp::export]]
SEXP gdns_set_tls_ca_file(SEXP gctx, std::string ca_file) {

  check_is_xptr(gctx);

  getdns_context *ctxt = (getdns_context *)R_ExternalPtrAddr(gctx);

  if (gctx == NULL) return(R_NilValue);

  getdns_return_t r;

  if ((r = getdns_context_set_tls_ca_file(ctxt, ca_file.c_str()))) {
    Rf_error(getdns_get_errorstr_by_id(r));
  }

  return(gctx);

}
