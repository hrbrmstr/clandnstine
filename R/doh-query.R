#' Make a DoH Request (POST/wireformat)
#'
#' Issue a `POST` wireformat query of type `type` for `name` to
#' the DoH endpoint specified at `server_path`.
#'
#' @param name name to query for
#' @param type DNS query type (defaults to "`A`")
#' @param server_path full URL path to the DoH server quer endpoint (defaults to Quad9).
#' @return `NULL` (if the query failed) or a `data.frame` (tibble)
#' @references <https://tools.ietf.org/id/draft-ietf-doh-dns-over-https-05.html>
#' @export
#' @examples
#' doh_post("rud.is", "A")
doh_post <- function(name, type = "A", server_path = "https://dns.quad9.net/dns-query") {

  DNSRecord$new()$question(
    qname = tolower(name[1]),
    qtype = toupper(type[1]),
    qclass = "IN"
  ) -> q

  # now, send it off to the server

  httr::POST(
    url = server_path[1],
    httr::add_headers(
      `Content-Type` = "application/dns-message",
      `Accept` = "application/dns-message"
    ),
    .CLANDNSTINE_UA,
    encode = "raw",
    body = q$pack()
  ) -> res

  httr::stop_for_status(res)

  res <- int_dns_wire_to_list(httr::content(res, as = "raw"))

  if (length(res)) {
    out <- jsonlite::fromJSON(res)
    class(out) <- c("gdns_doh_response", "list")
    out
  } else {
    NULL
  }

}

#' Tidy generic
#'
#' @keywords internal
#' @export
#' @param x an object
#' @param ... unused
tidy <- function (x, ...) {
  UseMethod("tidy")
}

#' Tidy a DoH POST response
#'
#' @param x a DoH POST response
#' @param ... unused
#' @export
tidy.gdns_doh_response <- function(x, ...) {

  rawdat <- x$answer[, c("rdata")]

  nr <- colnames(rawdat)
  if ("txt_strings" %in% nr) {
    vapply(rawdat[["txt_strings"]], function(.x) {
      .x
    }, FUN.VALUE = character(1)) -> rawdat[["txt_strings"]]
  }

  lapply(rawdat[["rdata_raw"]], function(.x) {

    if (x$question$qtype %in% c(2, 5, 12)) {
      charToRaw(.x)
    } else {
      as.raw(.x)
    }

  }) -> rawdat[["rdata_raw"]]

  cbind.data.frame(
    x$answer[, c("name", "class", "type", "ttl")],
    rawdat,
    stringsAsFactors = FALSE
  ) -> out

  class(out) <- c("tbl_df", "tbl", "data.frame")

  out

}



