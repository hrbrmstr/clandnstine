.res_types <- c("stub" = 520L, "recursive" = 521L)

#' Specify whether DNS queries are performed with recursive lookups or as a stub resolver
#'
#' @param gctx gdns resolver context created with [gdns_resolver()]
#' @param res_type length 1 character vector of either "`stub`" or "`recursive`"
#' @family context functions
#' @export
#' @examples
#' x <- gdns_context()
#' x <- gdns_set_resolution_type(x, "stub")
gdns_set_resolution_type <- function(gctx, res_type = c("stub", "recursive")) {

  match.arg(
    unique(tolower(trimws(res_type))), c("stub", "recursive")
  ) -> transports

  res_type <- unname(.res_types[res_type])

  int_gdns_set_resolution_type(gctx, res_type)

}
