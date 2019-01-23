#' Perform Secure-by-default 'DNS' Queries
#'
#' Methods are provided to query 'Domain Name System' ('DNS') stub
#' and recursive resolvers for all 'DNS' resource record types using 'UDP',
#' TCP', and/or 'TLS' transport layers. 'DNS' query support is provided
#' by the 'getdns' (<getdnsapi.net>) C library.
#'
#'
#' - URL: <https://gitlab.com/hrbrmstr/clandnstine>
#' - BugReports: <https://gitlab.com/hrbrmstr/clandnstine/issues>
#'
#' @md
#' @name clandnstine
#' @docType package
#' @author Bob Rudis (bob@@rud.is)
#' @keywords internal
#' @importFrom jsonlite fromJSON
#' @useDynLib clandnstine, .registration = TRUE
#' @importFrom Rcpp sourceCpp
NULL