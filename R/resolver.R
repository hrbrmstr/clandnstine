#' Create a gdns DNS over TLS context and populate it with a resolver
#' for use in resolution functions
#'
#' @note [DNS Privacy](https://dnsprivacy.org/wiki/display/DP/DNS+Privacy+Test+Servers#DNSPrivacyTestServers-DoTservers)
#'       maintains a list of DNS over TLS servers.
#' @param resolvers character vector of valid DNS over TLS resolvers;
#'        Defaults to Quad9 (`9.9.9.9`).
#' @export
#' @family query functions
#' @examples
#' x <- gdns_context()
#' x <- gdns_context("1.1.1.1")
gdns_context <- function(resolvers = "9.9.9.9") {
  int_gdns_context(resolvers)
}

#' Changes the list of resolvers in an already created context for use in resolution functions
#'
#' @note [DNS Privacy](https://dnsprivacy.org/wiki/display/DP/DNS+Privacy+Test+Servers#DNSPrivacyTestServers-DoTservers)
#'       maintains a list of DNS over TLS servers.
#' @param gctx gdns resolver context created with [gdns_resolver()]
#' @param resolvers character vector of valid DNS over TLS resolvers
#' @family context functions
#' @export
#' @examples
#' x <- gdns_context()
#' x <- gdns_update_resolvers(x, "1.1.1.1")
gdns_update_resolvers<- function(gctx, resolvers) {
  int_gdns_update_resolvers(gctx, resolvers)
}

#' Initialized the context's local names namespace with values from the given hosts file.
#'
#' @param gctx gdns resolver context created with [gdns_resolver()]
#' @param hosts_file path to a valid `hosts` file (e.g. "`/etc/hosts`). This value
#'        will be [path.expand()]ed.
#' @export
#' @family context functions
#' @examples
#' x <- gdns_context()
#' gdns_set_hosts(x, "/etc/hosts")
gdns_set_hosts<- function(gctx, hosts_file) {
  hosts_file <- path.expand(hosts_file[1])
  stopifnot(file.exists(hosts_file))
  int_gdns_set_hosts(gctx, hosts_file)
}

#' Retrieve the list of addresses in use for looking up top-level domains in use by the context.
#'
#' @param gctx gdns resolver context created with [gdns_resolver()]
#' @export
#' @family context functions
# x <- gdns_context()
# gdns_get_root_servers(x)
gdns_get_root_servers <- function(gctx) {
  x <- int_gdns_get_root_servers(gctx);
  if (length(x)) jsonlite::fromJSON(x) else NULL
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
#' @note Local hosts files are ignored when using this `getdns` API endpoint
#' @param gctx gdns resolver context created with [gdns_resolver()]. If `NULL` a
#'        temporary context will be created but is not ideal since there is overhead
#'        associated with context creation and garbage collection.
#' @param name an entity to query for
#' @param rr_type what resource record type do you want to queyr for? See `Details`.
#' @param include_reporting if `TRUE` include debugging information for queries
#'        such as the length of time it takes for each query. Default: `FALSE`
#' @references <https://www.iana.org/assignments/dns-parameters/dns-parameters.xhtml>
#' @family query functions
#' @export
#' @examples
#' x <- gdns_resolver()
#' gdns_query(x, "example.com")
gdns_query <- function(gctx = NULL, name, rr_type = "txt", rr_class = 1L,
                       include_reporting = FALSE) {

  if (is.null(gctx)) gctx <- gdns_context()

  stopifnot(is_gctx(gctx))

  rr_class <- rr_class[1]
  if (!rr_class %in% c(1, 3, 4, 254, 255)) rr_class <- 1

  rr_type <- match.arg(trimws(tolower(rr_type[1])), names(rr_types))
  res <- int_gdns_query(gctx, name, unname(as.integer(rr_types[rr_type])),
                        as.logical(include_reporting))
  if (length(res)) {
    out <- jsonlite::fromJSON(res)
    class(out) <- c("gdns_response", "list")
    out
  } else {
    NULL
  }

}

#' Printer for gdns_response objects
#'
#' @param x a `gdns_response` object
#' @param ... ignored
#' @keywords internal
#' @export
print.gdns_response <- function(x, ...) {

  cat(
    "Query: ",
    x$replies_tree$question$qname[1], " ",
    toupper(rr_types_rev[x$replies_tree$question$qtype[1]]),
    "\n", sep=""
  )

  qtype <- as.character(x$replies_tree$question$qtype[[1]])
  ans <- x$replies_tree$answer[[1]]
  ans$rdata$rdata_raw <- NULL

  switch(
    qtype,
    "1" = {
      cat(
        "Answer: ",
        paste0(unlist(x$just_address_answers$address_data), collapse="\n"),
        "\n", sep=""
      )
    },
    "2" ={
      cat(
        "Answer: ",
        paste0(ans$rdata$nsdname, collapse=", "),
        "\n", sep=""
      )
    },
    "15" = {
      cat(
        "Answer: \n",
        paste0(glue::glue_data(ans$rdata, "{preference} {exchange}"), collapse="\n"),
        "\n", sep=""
      )
    },
    "16" = {
      rd <- ans$rdata
      typs <- ans$type
      typs <- which(typs == 16)
      if (length(typs)) {
        cat(
          "Answer: ",
          paste0(unlist(rd$txt_strings[typs]), collapse="\n"),
          "\n", sep=""
        )
      }
    },
    "28" = {
      cat(
        "Answer: ",
        paste0(unlist(x$just_address_answers$address_data), collapse="\n"),
        "\n", sep=""
      )
    },
    "257" = {
      cat(
        "Answer: \n",
        paste0(glue::glue_data(ans$rdata, "{flags} {tag} {value}"), collapse="\n"),
        "\n", sep=""
      )
    },
    {
      print(str(ans$rdata, give.attr = FALSE))
    }
  )

}





