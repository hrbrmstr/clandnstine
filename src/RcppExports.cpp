// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// gdns_lib_version
std::string gdns_lib_version();
RcppExport SEXP _clandnstine_gdns_lib_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(gdns_lib_version());
    return rcpp_result_gen;
END_RCPP
}
// int_gdns_update_resolvers
SEXP int_gdns_update_resolvers(SEXP gctx, std::vector< std::string > resolvers);
RcppExport SEXP _clandnstine_int_gdns_update_resolvers(SEXP gctxSEXP, SEXP resolversSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    Rcpp::traits::input_parameter< std::vector< std::string > >::type resolvers(resolversSEXP);
    rcpp_result_gen = Rcpp::wrap(int_gdns_update_resolvers(gctx, resolvers));
    return rcpp_result_gen;
END_RCPP
}
// gdns_set_timeout
SEXP gdns_set_timeout(SEXP gctx, long timeout);
RcppExport SEXP _clandnstine_gdns_set_timeout(SEXP gctxSEXP, SEXP timeoutSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    Rcpp::traits::input_parameter< long >::type timeout(timeoutSEXP);
    rcpp_result_gen = Rcpp::wrap(gdns_set_timeout(gctx, timeout));
    return rcpp_result_gen;
END_RCPP
}
// gdns_get_timeout
DoubleVector gdns_get_timeout(SEXP gctx);
RcppExport SEXP _clandnstine_gdns_get_timeout(SEXP gctxSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    rcpp_result_gen = Rcpp::wrap(gdns_get_timeout(gctx));
    return rcpp_result_gen;
END_RCPP
}
// gdns_set_round_robin_upstreams
SEXP gdns_set_round_robin_upstreams(SEXP gctx, bool flag);
RcppExport SEXP _clandnstine_gdns_set_round_robin_upstreams(SEXP gctxSEXP, SEXP flagSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    Rcpp::traits::input_parameter< bool >::type flag(flagSEXP);
    rcpp_result_gen = Rcpp::wrap(gdns_set_round_robin_upstreams(gctx, flag));
    return rcpp_result_gen;
END_RCPP
}
// int_gdns_set_hosts
SEXP int_gdns_set_hosts(SEXP gctx, std::string hosts);
RcppExport SEXP _clandnstine_int_gdns_set_hosts(SEXP gctxSEXP, SEXP hostsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    Rcpp::traits::input_parameter< std::string >::type hosts(hostsSEXP);
    rcpp_result_gen = Rcpp::wrap(int_gdns_set_hosts(gctx, hosts));
    return rcpp_result_gen;
END_RCPP
}
// check_is_xptr
void check_is_xptr(SEXP s);
RcppExport SEXP _clandnstine_check_is_xptr(SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type s(sSEXP);
    check_is_xptr(s);
    return R_NilValue;
END_RCPP
}
// is_null_xptr_
SEXP is_null_xptr_(SEXP s);
RcppExport SEXP _clandnstine_is_null_xptr_(SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type s(sSEXP);
    rcpp_result_gen = Rcpp::wrap(is_null_xptr_(s));
    return rcpp_result_gen;
END_RCPP
}
// int_gdns_resolver
SEXP int_gdns_resolver(std::vector< std::string > resolvers);
RcppExport SEXP _clandnstine_int_gdns_resolver(SEXP resolversSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector< std::string > >::type resolvers(resolversSEXP);
    rcpp_result_gen = Rcpp::wrap(int_gdns_resolver(resolvers));
    return rcpp_result_gen;
END_RCPP
}
// gdns_get_address
CharacterVector gdns_get_address(SEXP gctx, std::string host);
RcppExport SEXP _clandnstine_gdns_get_address(SEXP gctxSEXP, SEXP hostSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    Rcpp::traits::input_parameter< std::string >::type host(hostSEXP);
    rcpp_result_gen = Rcpp::wrap(gdns_get_address(gctx, host));
    return rcpp_result_gen;
END_RCPP
}
// int_get_resolvers
CharacterVector int_get_resolvers(SEXP gctx);
RcppExport SEXP _clandnstine_int_get_resolvers(SEXP gctxSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    rcpp_result_gen = Rcpp::wrap(int_get_resolvers(gctx));
    return rcpp_result_gen;
END_RCPP
}
// int_gdns_query
CharacterVector int_gdns_query(SEXP gctx, std::string name, uint16_t rr, bool include_reporting);
RcppExport SEXP _clandnstine_int_gdns_query(SEXP gctxSEXP, SEXP nameSEXP, SEXP rrSEXP, SEXP include_reportingSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type gctx(gctxSEXP);
    Rcpp::traits::input_parameter< std::string >::type name(nameSEXP);
    Rcpp::traits::input_parameter< uint16_t >::type rr(rrSEXP);
    Rcpp::traits::input_parameter< bool >::type include_reporting(include_reportingSEXP);
    rcpp_result_gen = Rcpp::wrap(int_gdns_query(gctx, name, rr, include_reporting));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_clandnstine_gdns_lib_version", (DL_FUNC) &_clandnstine_gdns_lib_version, 0},
    {"_clandnstine_int_gdns_update_resolvers", (DL_FUNC) &_clandnstine_int_gdns_update_resolvers, 2},
    {"_clandnstine_gdns_set_timeout", (DL_FUNC) &_clandnstine_gdns_set_timeout, 2},
    {"_clandnstine_gdns_get_timeout", (DL_FUNC) &_clandnstine_gdns_get_timeout, 1},
    {"_clandnstine_gdns_set_round_robin_upstreams", (DL_FUNC) &_clandnstine_gdns_set_round_robin_upstreams, 2},
    {"_clandnstine_int_gdns_set_hosts", (DL_FUNC) &_clandnstine_int_gdns_set_hosts, 2},
    {"_clandnstine_check_is_xptr", (DL_FUNC) &_clandnstine_check_is_xptr, 1},
    {"_clandnstine_is_null_xptr_", (DL_FUNC) &_clandnstine_is_null_xptr_, 1},
    {"_clandnstine_int_gdns_resolver", (DL_FUNC) &_clandnstine_int_gdns_resolver, 1},
    {"_clandnstine_gdns_get_address", (DL_FUNC) &_clandnstine_gdns_get_address, 2},
    {"_clandnstine_int_get_resolvers", (DL_FUNC) &_clandnstine_int_get_resolvers, 1},
    {"_clandnstine_int_gdns_query", (DL_FUNC) &_clandnstine_int_gdns_query, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_clandnstine(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
