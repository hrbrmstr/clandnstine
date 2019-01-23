#' Printer for gdns contexts
#'
#' @param x gdns context object
#' @param ... unused
#' @keywords internal
#' @export
print.gctx <- function(x, ...) {
  if (is_null_xptr_(x)) {
    cat("<gdns v", gdns_lib_version(), " resolver context (INVALID)>\n")
  } else {
    cat(
      "<gdns v", gdns_lib_version(),
      " resolver context; resolvers: [",
      paste0(int_get_resolvers(x), collapse=", "),
      "]; timeout: ", prettyNum(gdns_get_timeout(x), big.mark=","),
      " ms; lookup transport(s): [", paste0(gdns_get_transports(x), collapse=", "),
      "]; resolution type: ", gdns_get_resolution_type(x),
      ">", "\n", sep = ""
    )
  }
}