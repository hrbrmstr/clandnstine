#' Test whether an object is a `gctx` context
#'
#' @param x object
#' @export
is_gctx <- function(x) {
   inherits(x, "gctx")
}
