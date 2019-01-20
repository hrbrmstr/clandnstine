#' Create a gdns DNS over TLS context and populate it with a resolver
#' for use in resolution functions
#'
#' @param resolver character vector of valid DNS over TLS resolvers;
#'        Defaults to Quad9 (`9.9.9.9`).
#' @export
#' @examples
#' x <- gdns_resolver()
#' x <- gdns_resolver("1.1.1.1")
gdns_resolver <- function(resolvers = "9.9.9.9") {
  int_gdns_resolver(resolvers)
}

#' Arbitrary DNS queries
#'
#' Perform any valid resource record inquiry for a given name. See `Details`.
#'
#' This returns a fairly complex result object but that is the nature
#' of DNS queries. You're likely going to want what is in `$replies_tree$answer`
#' but the rest of the structure contains lovely metadata about the query and
#' remote query environment. There will eventually be "as data frame"-ish helpers
#' for this object.
#'
#' Valid values for `rr_type`:
#' - `a`
#' - `a6`
#' - `aaaa`
#' - `afsdb`
#' - `any`
#' - `apl`
#' - `atma`
#' - `avc`
#' - `axfr`
#' - `caa`
#' - `cdnskey`
#' - `cds`
#' - `cert`
#' - `cname`
#' - `csync`
#' - `dhcid`
#' - `dlv`
#' - `dname`
#' - `dnskey`
#' - `doa`
#' - `ds`
#' - `eid`
#' - `eui48`
#' - `eui64`
#' - `gid`
#' - `gpos`
#' - `hinfo`
#' - `hip`
#' - `ipseckey`
#' - `isdn`
#' - `ixfr`
#' - `key`
#' - `kx`
#' - `l32`
#' - `l64`
#' - `loc`
#' - `lp`
#' - `maila`
#' - `mailb`
#' - `mb`
#' - `md`
#' - `mf`
#' - `mg`
#' - `minfo`
#' - `mr`
#' - `mx`
#' - `naptr`
#' - `nid`
#' - `nimloc`
#' - `ninfo`
#' - `ns`
#' - `nsap`
#' - `nsap_ptr`
#' - `nsec`
#' - `nsec3`
#' - `nsec3param`
#' - `null`
#' - `nxt`
#' - `openpgpkey`
#' - `opt`
#' - `ptr`
#' - `px`
#' - `rkey`
#' - `rp`
#' - `rrsig`
#' - `rt`
#' - `sig`
#' - `sink`
#' - `smimea`
#' - `soa`
#' - `spf`
#' - `srv`
#' - `sshfp`
#' - `ta`
#' - `talink`
#' - `tkey`
#' - `tlsa`
#' - `tsig`
#' - `txt`
#' - `uid`
#' - `uinfo`
#' - `unspec`
#' - `uri`
#' - `wks`
#' - `x25`
#' - `zonemd`
#'
#' @references <https://www.iana.org/assignments/dns-parameters/dns-parameters.xhtml>
#' @export
#' @examples
#' x <- gdns_resolver()
#' gdns_query(x, "example.com")
gdns_query <- function(gcx, name, rr_type = "txt") {

  rr_type <- match.arg(trimws(tolower(rr_type[1])), names(rr_types))
  res <- int_gdns_query(gcx, name, unname(as.integer(rr_types[rr_type])))
  if (length(res)) {
    out <- jsonlite::fromJSON(res)
    out
  } else {
    NULL
  }

}