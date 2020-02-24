#' Perform Secure-by-default or Woefully Insecure 'DNS' Queries
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
#' @import httr R6
#' @importFrom glue glue_data
#' @importFrom jsonlite fromJSON
#' @useDynLib clandnstine, .registration = TRUE
#' @importFrom Rcpp sourceCpp
NULL