ipv4_regex <-
  "^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"

#' Convert a vector of IPv4 addresses to in-addr.arpa format
#'
#' @md
#' @param ipv4 vector of ipv4 addresses
#' @export
to_inaddr_arpa <- function(ipv4) {

  ifelse(
    test = grepl(ipv4_regex, ipv4),
    yes =  paste0(
      c(
        rev(unlist(strsplit(ipv4, ".", 4), use.names = FALSE)),
        "in-addr.arpa."
      ),
      sep = "",
      collapse = "."
    ),
    no = ipv4
  )

}
