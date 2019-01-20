#' Printer for gdns contexts
#'
#' @param x gdns context object
#' @param ... unused
#' @keywords internal
#' @export
print.gctx <- function(x, ...) {
  if (is_null_xptr_(x)) {
    cat("<gdns resolver context (INVALID)>\n")
  } else {
    cat("<gdns resolver context; resolvers: ", int_get_resolvers(x) ,">\n", sep="")
  }
}