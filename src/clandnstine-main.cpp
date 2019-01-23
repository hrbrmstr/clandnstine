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