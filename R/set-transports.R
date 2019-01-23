.transport_trans <- c("tls" = 1202L, "tcp" = 1201L, "udp" = 1200L)

#' Specifies what transport(s) is/ar used for DNS lookups
#'
#' @param gctx gdns resolver context created with [gdns_resolver()]
#' @param transports character vector of any/all of "`udp`", "`tcp`" or "`tls`".
#'        Order matters as it specifies that the library will use to try to
#'        perform the lookups.
#' @export
#' @examples
#' x <- gdns_context()
#' x <- gdns_set_transports(x, "tls")
gdns_set_transports <- function(gctx, transports = c("tls", "udp", "tcp")) {

  match.arg(
    unique(tolower(trimws(transports))), c("tls", "udp", "tcp"),
    several.ok = TRUE
  ) -> transports

  transports <- unname(.transport_trans[transports])

  int_gdns_set_transports(gctx, transports)

}
