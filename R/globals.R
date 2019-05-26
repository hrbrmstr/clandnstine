c(
  'A' = 1L, 'NS' = 2L, 'CNAME' = 5L, 'SOA' = 6L, 'PTR' = 12L, 'HINFO' = 13L,
  'MX' = 15L, 'TXT' = 16L, 'RP' = 17L, 'AFSDB' = 18L, 'SIG' = 24L,
  'KEY' = 25L, 'AAAA' = 28L, 'LOC' = 29, 'SRV' = 33L, 'NAPTR' = 35L,
  'KX' = 36L, 'CERT' = 37L, 'A6' = 38L, 'DNAME' = 39L, 'OPT' = 41,
  'APL' = 42L, 'DS' = 43L, 'SSHFP' = 44L, 'IPSECKEY' = 45L, 'RRSIG' = 46L,
  'NSEC' = 47L, 'DNSKEY' = 48L, 'DHCID' = 49L, 'NSEC3' = 50L,
  'NSEC3PARAM' = 51L, 'TLSA' = 52L, 'HIP' = 55L, 'CDS' = 59L,
  'CDNSKEY' = 60L, 'OPENPGPKEY' = 61L, 'SPF' = 99L, 'TKEY' = 249L,
  'TSIG' = 250L, 'IXFR' = 251L, 'AXFR' = 252L, 'ANY' = 255L,
  'URI' = 256L, 'CAA' = 257L, 'TA' = 32768L, 'DLV' = 32769L
) -> .qtype

c(
  'IN' = 1L,
  'CS' = 2L,
  'CH' = 3L,
  'Hesiod' = 4L,
  'None' = 254L,
  '*' = 255L
) -> .class

.qr <- c('QUERY' = 0, 'RESPONSE' = 1)

c(
  'NOERROR' = 0L,
  'FORMERR' = 1L,
  'SERVFAIL' = 2L,
  'NXDOMAIN' = 3L,
  'NOTIMP' = 4L,
  'REFUSED' = 5L,
  'YXDOMAIN' = 6L,
  'YXRRSET' = 7L,
  'NXRRSET' = 8L,
  'NOTAUTH' = 9L,
  'NOTZONE' = 10L
) -> .rcode

c(
  'QUERY' = 0L,
  'IQUERY' = 1L,
  'STATUS' = 2L,
  'UPDATE' = 5L
) -> .opcode

#' Built-in list of DoH Servers
#'
#' The `url` element has the URL for `GET`/`POST` requests and
#' the `extra_params` element has any needed query parameters
#' for `GET` requests.
#'
#' The list so far.
#' - `google`: <https://dns.google.com/experimental>
#' - `cloudflare`: <https://cloudflare-dns.com/dns-query>
#' - `quad9`: <https://dns.quad9.net/dns-query>
#' - `securedns_eu`: <https://doh.securedns.eu/dns-query>
#' - `dnswarden_adblock`: <https://doh.dnswarden.com/adblock>
#' - `dnswarden_uncensored`: <https://doh.dnswarden.com/uncensored>
#' - `cleanbrowsing_security`: <https://doh.cleanbrowsing.org/doh/security-filter/>
#' - `cleanbrowsing_family`: <https://doh.cleanbrowsing.org/doh/family-filter/>
#' - `cleanbrowsing_adult`: <https://doh.cleanbrowsing.org/doh/adult-filter/>
#' - `power_dns`: <https://doh.powerdns.org>
#' - `appliedprivacy`: <https://doh.appliedprivacy.net/query>
#'
#' @docType data
#' @export
list(
  google = list(
    url = "https://dns.google.com/experimental",
    extra_params = list()
  ),
  cloudflare = list(
    url = "https://cloudflare-dns.com/dns-query",
    extra_params = list(
      cd = "false",
      do = "true",
      ct = "application/dns-json"
    )
  ),
  quad9 = list(
    url = "https://dns.quad9.net/dns-query",
    extra_params = list()
  ),
  securedns_eu = list(
    url = "https://doh.securedns.eu/dns-query",
    extra_params = list(
      edns_client_subnet = NULL
    )
  ),
  dnswarden_adblock = list(
    url = "https://doh.dnswarden.com/adblock",
    extra_params = list()
  ),
  dnswarden_uncensored = list(
    url = "https://doh.dnswarden.com/uncensored",
    extra_params = list()
  ),
  cleanbrowsing_security = list(
    url = "https://doh.cleanbrowsing.org/doh/security-filter/",
    extra_params = list(cd = "false")
  ),
  cleanbrowsing_family = list(
    url = "https://doh.cleanbrowsing.org/doh/family-filter/",
    extra_params = list()
  ),
  cleanbrowsing_adult = list(
    url = "https://doh.cleanbrowsing.org/doh/adult-filter/",
    extra_params = list()
  ),
  power_dns = list(
    url = "https://doh.powerdns.org",
    extra_params = list()
  ),
  appliedprivacy = list(
    url = "https://doh.appliedprivacy.net/query",
    extra_params = list()
  )
) -> doh_servers