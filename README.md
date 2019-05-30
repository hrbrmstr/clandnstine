
[![Travis-CI Build
Status](https://travis-ci.org/hrbrmstr/clandnstine.svg?branch=master)](https://travis-ci.org/hrbrmstr/clandnstine)
[![Coverage
Status](https://codecov.io/gh/hrbrmstr/clandnstine/branch/master/graph/badge.svg)](https://codecov.io/gh/hrbrmstr/clandnstine)
[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/clandnstine)](https://cran.r-project.org/package=clandnstine)

# clandnstine

Perform Secure-by-default ‘DNS’ Queries

## Description

Perform and process ‘DNS over TLS’ and ‘DNS over HTTPS’ queries.

## NOTE

Requires [`getdns`](https://getdnsapi.net/) to be installed and
available for compilation (no guard rails setup yet):

  - Use `brew install getdns` on macOS
  - Install `libgetdns-dev` or `libgetdns-devel` on debian/ubuntu
    (version 1.5.1 or higher)
  - (Nothing to see here Windows folks stuck in a backwards ecosysem)

You’re going to need version 1.5.1 of `getdns` for this package to
install.

I’ve gotten this running on macOS and Ubuntu 16.04. For the latter I had
to ensure `libidn2-0-dev` and `libunbound-dev` were installed then had
to grab the 1.5.1 tarball (e.g. `aria2c
https://getdnsapi.net/releases/getdns-1-5-1/getdns-1.5.1.tar.gz`),
extract it and `config`/`make`/`make install` (plus `ldconfig` after).

## TODO/WAT

I finally grok the getdns api so the package api is going to change
wildly and fast. The default mode will be to perform queries using DNS
over TLS but also supports UDP and TCP transports along with support for
DNS over HTTPS.

## Why?

Well, for starters, to help research DNS over TLS/DNS over HTTPS
servers. Plus, for fun\!

If you’re asking “Why DNS over TLS/HTTPS at all?” then “faux” privacy.
Why “faux”? Well, *something* is handing your query and that something
knows your IP address and what you looked for. So, you’re relying on the
good faith, honest nature and technical capability of the destination
server to not mess with you. I don’t trust Cloudflare or Google and am
witholding judgement on Quad9 either way (they’ve been doing good things
and are less “look at how cool we are” than CF is).

Also “faux” in that you’re going to be using (for DoT) a standard port
(853) and a TLS session for the queries so your internet provider will
know you’re doing *something* and the current, sorry state of SSL
certificates, certificate authorities, and authoritarian companies and
regimes combined means confidentiality and integrity are always kinda in
question unless done super-well.

## What’s Different About This vs Regular DNS?

Well, if we lookup the addresses for `yahoo.com` the old-fashioned way
it’s cleartext UDP on the wire:

    1   0.000000   10.1.10.57 → 10.1.10.200  DNS 80 Standard query 0x8af8 A yahoo.com OPT
    2   0.003297  10.1.10.200 → 10.1.10.57   DNS 176 Standard query response 0x8af8 A yahoo.com A 72.30.35.10 A 98.138.219.231 A 72.30.35.9 A 98.137.246.7 A 98.138.219.232 A 98.137.246.8 OPT

I watched for port 53 UDP traffic with `tshark` as `yahoo.com` was being
looked up. Notice the fast and diminuitive — and plaintext — response.
(I’m fibbing a bit since I pre-loaded the local home DNS server with
this query since I tested it alot before knitting this readme. My home
server forwards all queries to a custom DNS over TLS server since I
really don’t trust any of the providers when it comes down to it. So, in
reality for me, it’s even slower than the below — at least initially).

This is the same query via DNS over TLS

``` 
 1   0.000000   10.1.10.57 → 9.9.9.9      TCP 78 52128 → 853 [SYN] Seq=0 Win=65535 Len=0 MSS=1460 WS=64 TSval=602885491 TSecr=0 SACK_PERM=1 TFO=R
 2   0.021188      9.9.9.9 → 10.1.10.57   TCP 74 853 → 52128 [SYN, ACK] Seq=0 Ack=1 Win=28960 Len=0 MSS=1460 SACK_PERM=1 TSval=3426782438 TSecr=602885491 WS=256
 3   0.021308   10.1.10.57 → 9.9.9.9      TLSv1 373 Client Hello
 4   0.045324      9.9.9.9 → 10.1.10.57   TLSv1.2 1514 Server Hello
 5   0.045333      9.9.9.9 → 10.1.10.57   TLSv1.2 73 [TCP Previous segment not captured] , Ignored Unknown Record
 6   0.045334      9.9.9.9 → 10.1.10.57   TCP 1514 [TCP Out-Of-Order] 853 → 52128 [ACK] Seq=1449 Ack=308 Win=30208 Len=1448 TSval=3426782459 TSecr=602885512
 7   0.045491   10.1.10.57 → 9.9.9.9      TCP 78 52128 → 853 [ACK] Seq=308 Ack=1449 Win=130304 Len=0 TSval=602885536 TSecr=3426782459 SLE=2897 SRE=2904
 8   0.045492   10.1.10.57 → 9.9.9.9      TCP 66 52128 → 853 [ACK] Seq=308 Ack=2904 Win=128832 Len=0 TSval=602885536 TSecr=3426782459
 9   0.050527   10.1.10.57 → 9.9.9.9      TLSv1.2 192 Client Key Exchange, Change Cipher Spec, Encrypted Handshake Message
10   0.069107      9.9.9.9 → 10.1.10.57   TLSv1.2 117 Change Cipher Spec, Encrypted Handshake Message
11   0.069255   10.1.10.57 → 9.9.9.9      TCP 66 52128 → 853 [ACK] Seq=434 Ack=2955 Win=131008 Len=0 TSval=602885559 TSecr=3426782487
12   0.069516   10.1.10.57 → 9.9.9.9      TLSv1.2 225 Application Data
13   0.091087      9.9.9.9 → 10.1.10.57   TLSv1.2 303 Application Data
14   0.091207   10.1.10.57 → 9.9.9.9      TLSv1.2 225 Application Data
15   0.106738      9.9.9.9 → 10.1.10.57   TLSv1.2 231 Application Data
16   0.106836   10.1.10.57 → 9.9.9.9      TCP 66 52128 → 853 [ACK] Seq=752 Ack=3357 Win=130880 Len=0 TSval=602885595 TSecr=3426782525
17   0.107200   10.1.10.57 → 9.9.9.9      TLSv1.2 97 Encrypted Alert
18   0.107411   10.1.10.57 → 9.9.9.9      TCP 66 52128 → 853 [FIN, ACK] Seq=783 Ack=3357 Win=131072 Len=0 TSval=602885595 TSecr=3426782525
19   0.126603      9.9.9.9 → 10.1.10.57   TLSv1.2 97 Encrypted Alert
20   0.126608      9.9.9.9 → 10.1.10.57   TCP 66 853 → 52128 [FIN, ACK] Seq=3388 Ack=784 Win=32256 Len=0 TSval=3426782545 TSecr=602885595
21   0.126717   10.1.10.57 → 9.9.9.9      TCP 54 52128 → 853 [RST] Seq=784 Win=0 Len=0
22   0.126718   10.1.10.57 → 9.9.9.9      TCP 54 52128 → 853 [RST] Seq=784 Win=0 Len=0
```

It’s stupid slow, consumes more CPU and bandwidth but forces adversaries
to work pretty hard to try to figure out what you’re looking for.

## What’s Inside The Tin

The following functions are implemented:

### Utility

  - `to_inaddr_arpa`: Convert a vector of IPv4 addresses to in-addr.arpa
    format

### DNS over HTTPS

  - `doh_post`: Make a DoH Request (POST/wireformat)
  - `doh_servers`: Built-in list of DoH servers.
  - `tidy.gdns_doh_response`: Tidy a DoH POST response

### DNS over TLS

  - `gdns_query`: Arbitrary DNS queries
  - `gdns_context`: Create a gdns DNS over TLS context and populate it
    with a resolver for use in resolution functions
  - `gdns_get_address`: Resolve a host to an addrss
  - `gdns_get_resolution_type`: Get the current resolution type setting
  - `gdns_get_timeout`: Retreive the number of milliseconds to wait for
    request to return
  - `gdns_get_tls_ca_file`: Retreive the file location with CA
    certificates for verification purposes
  - `gdns_get_tls_ca_path`: Retreive the value with which the context’s
    upstream recursive servers and suffixes were initialized
  - `gdns_get_transports`: Retreive what transports are used for DNS
    lookups.
  - `gdns_lib_version`: Return gdns library version
  - `gdns_set_hosts`: Initialized the context’s local names namespace
    with values from the given hosts file.
  - `gdns_set_resolution_type`: Specify whether DNS queries are
    performed with recursive lookups or as a stub resolver
  - `gdns_set_round_robin_upstreams`: Set/unset context to round robin
    queries over the available upstreams when resolving with the stub
    resolution type.
  - `gdns_set_timeout`: Specify the number of milliseconds to wait for
    request to return
  - `gdns_set_tls_ca_file`: Specify the file with CA certificates for
    verification purposes
  - `gdns_set_tls_ca_path`: Specify where the location for CA
    certificates for verification purposes are located
  - `gdns_set_transports`: Specifies what transport(s) is/ar used for
    DNS lookups
  - `gdns_update_resolvers`: Changes the list of resolvers in an already
    created context for use in resolution functions

## Installation

``` r
devtools::install_git("https://git.sr.ht/~hrbrmstr/clandnstine")
# or 
devtools::install_gitlab("hrbrmstr/clandnstine.git")
# or
devtools::install_github("hrbrmstr/clandnstine")
```

## Usage

``` r
library(clandnstine)

# current version
packageVersion("clandnstine")
## [1] '0.2.0'
```

### Get an address(es) from a name:

``` r
gdns_lib_version()
## [1] "1.5.1"

(x <- gdns_context())
## <gdns v1.5.1 resolver context; resolvers: [9.9.9.9]; timeout: 5,000 ms; lookup transport(s): [tls]; resolution type: stub>

(x <- gdns_context("1.1.1.1"))
## <gdns v1.5.1 resolver context; resolvers: [1.1.1.1]; timeout: 5,000 ms; lookup transport(s): [tls]; resolution type: stub>

(x <- gdns_context(c("8.8.8.8", "1.1.1.1", "9.9.9.9")))
## <gdns v1.5.1 resolver context; resolvers: [8.8.8.8, 1.1.1.1, 9.9.9.9]; timeout: 5,000 ms; lookup transport(s): [tls]; resolution type: stub>

(gdns_set_timeout(x, 2000))
## <gdns v1.5.1 resolver context; resolvers: [8.8.8.8, 1.1.1.1, 9.9.9.9]; timeout: 2,000 ms; lookup transport(s): [tls]; resolution type: stub>

(gdns_update_resolvers(x, "1.1.1.1"))
## <gdns v1.5.1 resolver context; resolvers: [1.1.1.1]; timeout: 2,000 ms; lookup transport(s): [tls]; resolution type: stub>

(gdns_set_transports(x, c("udp", "tls", "tcp")))
## <gdns v1.5.1 resolver context; resolvers: [1.1.1.1]; timeout: 2,000 ms; lookup transport(s): [udp, tls, tcp]; resolution type: stub>

(gdns_get_address(x, "rud.is"))
## [1] "2602:ff16:3::4dfb:9ac5" "172.93.49.183"

(gdns_get_address(x, "yahoo.com"))
##  [1] "2001:4998:44:41d::4"   "2001:4998:58:1836::10" "2001:4998:58:1836::11" "2001:4998:c:1023::4"  
##  [5] "2001:4998:c:1023::5"   "2001:4998:44:41d::3"   "98.138.219.231"        "98.138.219.232"       
##  [9] "72.30.35.9"            "72.30.35.10"           "98.137.246.7"          "98.137.246.8"

(gdns_get_address(x, "yahoo.commmm"))
## character(0)
```

### Any record type query:

``` r
str(leno <- gdns_query(x, "lenovo.com", "txt"), 1)
## List of 5
##  $ answer_type   : int 800
##  $ canonical_name: chr "lenovo.com."
##  $ replies_full  : int [1, 1:762] 81 128 129 128 0 1 0 10 0 0 ...
##  $ replies_tree  :'data.frame':  1 obs. of  7 variables:
##  $ status        : int 900
##  - attr(*, "class")= chr [1:2] "gdns_response" "list"

sort(unlist(leno$replies_tree$answer[[1]]$rdata$txt_strings))
##  [1] "a82c74b37aa84e7c8580f0e32f4d795d"                                                        
##  [2] "ece42d7743c84d6889abda7011fe6f53"                                                        
##  [3] "facebook-domain-verification=1r2am7c2bhzrxpqyt0mda0djoquqsi"                             
##  [4] "google-site-verification=nGgukcp60rC-gFxMOJw1NHH0B4VnSchRrlfWV-He_tE"                    
##  [5] "google-site-verification=sHIlSlj0U6UnCDkfHp1AolWgVEvDjWvc0TR4KaysD2c"                    
##  [6] "google-site-verification=VxW_e6r_Ka7A518qfX2MmIMHGnkpGbnACsjSxKFCBw0"                    
##  [7] "iHzQJvsKnyGP2Nm2qBgL3fyBJ0CC9z4GkY/flfk4EzLP8lPxWHDDPKqZWm1TkeF5kEIL+NotYOF1wo7JtUDXXw=="
##  [8] "qh7hdmqm4lzs85p704d6wsybgrpsly0j"                                                        
##  [9] "v=spf1 include:spf.messagelabs.com include:_netblocks.eloqua.com ~all"                   
## [10] "Visit www.lenovo.com/think for information about Lenovo products and services"
```

Yep. Advertising even in DNS `TXT` records (see item number 8).

### DOH

``` r
str(doh_post("rud.is")$answer)
## 'data.frame':    1 obs. of  5 variables:
##  $ class: int 1
##  $ name : chr "rud.is."
##  $ rdata:'data.frame':   1 obs. of  2 variables:
##   ..$ ipv4_address: chr "172.93.49.183"
##   ..$ rdata_raw   :List of 1
##   .. ..$ : int  172 93 49 183
##  $ ttl  : int 685
##  $ type : int 1
```

``` r
a <- doh_post("apple.com", "A")
tidy(a)
##         name class type ttl  ipv4_address      rdata_raw
## 1 apple.com.     1    1 738 17.142.160.59 11, 8e, a0, 3b
## 2 apple.com.     1    1 738  17.178.96.59 11, b2, 60, 3b
## 3 apple.com.     1    1 738 17.172.224.47 11, ac, e0, 2f

aaaa <- doh_post("rud.is", "AAAA")
tidy(aaaa)
##      name class type   ttl           ipv6_address                                                      rdata_raw
## 1 rud.is.     1   28 43200 2602:ff16:3::4dfb:9ac5 26, 02, ff, 16, 00, 03, 00, 00, 00, 00, 00, 00, 4d, fb, 9a, c5

mx <- doh_post("rud.is", "MX")
tidy(mx)
##      name class type   ttl                 exchange preference
## 1 rud.is.     1   15 43200 alt2.aspmx.l.google.com.         30
## 2 rud.is.     1   15 43200      aspmx.l.google.com.         10
## 3 rud.is.     1   15 43200   aspmx2.googlemail.com.         40
## 4 rud.is.     1   15 43200 alt1.aspmx.l.google.com.         20
##                                                                                                    rdata_raw
## 1 00, 1e, 04, 61, 6c, 74, 32, 05, 61, 73, 70, 6d, 78, 01, 6c, 06, 67, 6f, 6f, 67, 6c, 65, 03, 63, 6f, 6d, 00
## 2                     00, 0a, 05, 61, 73, 70, 6d, 78, 01, 6c, 06, 67, 6f, 6f, 67, 6c, 65, 03, 63, 6f, 6d, 00
## 3         00, 28, 06, 61, 73, 70, 6d, 78, 32, 0a, 67, 6f, 6f, 67, 6c, 65, 6d, 61, 69, 6c, 03, 63, 6f, 6d, 00
## 4 00, 14, 04, 61, 6c, 74, 31, 05, 61, 73, 70, 6d, 78, 01, 6c, 06, 67, 6f, 6f, 67, 6c, 65, 03, 63, 6f, 6d, 00

txt <- doh_post("lenovo.com", "TXT")
tidy(txt)
##           name class type  ttl
## 1  lenovo.com.     1   16 4990
## 2  lenovo.com.     1   16 4990
## 3  lenovo.com.     1   16 4990
## 4  lenovo.com.     1   16 4990
## 5  lenovo.com.     1   16 4990
## 6  lenovo.com.     1   16 4990
## 7  lenovo.com.     1   16 4990
## 8  lenovo.com.     1   16 4990
## 9  lenovo.com.     1   16 4990
## 10 lenovo.com.     1   16 4990
##                                                                                                                                                                                                                                                                                                                                                             rdata_raw
## 1                                                                                  44, 67, 6f, 6f, 67, 6c, 65, 2d, 73, 69, 74, 65, 2d, 76, 65, 72, 69, 66, 69, 63, 61, 74, 69, 6f, 6e, 3d, 73, 48, 49, 6c, 53, 6c, 6a, 30, 55, 36, 55, 6e, 43, 44, 6b, 66, 48, 70, 31, 41, 6f, 6c, 57, 67, 56, 45, 76, 44, 6a, 57, 76, 63, 30, 54, 52, 34, 4b, 61, 79, 73, 44, 32, 63
## 2                                                                                  44, 67, 6f, 6f, 67, 6c, 65, 2d, 73, 69, 74, 65, 2d, 76, 65, 72, 69, 66, 69, 63, 61, 74, 69, 6f, 6e, 3d, 56, 78, 57, 5f, 65, 36, 72, 5f, 4b, 61, 37, 41, 35, 31, 38, 71, 66, 58, 32, 4d, 6d, 49, 4d, 48, 47, 6e, 6b, 70, 47, 62, 6e, 41, 43, 73, 6a, 53, 78, 4b, 46, 43, 42, 77, 30
## 3                                                                              45, 76, 3d, 73, 70, 66, 31, 20, 69, 6e, 63, 6c, 75, 64, 65, 3a, 73, 70, 66, 2e, 6d, 65, 73, 73, 61, 67, 65, 6c, 61, 62, 73, 2e, 63, 6f, 6d, 20, 69, 6e, 63, 6c, 75, 64, 65, 3a, 5f, 6e, 65, 74, 62, 6c, 6f, 63, 6b, 73, 2e, 65, 6c, 6f, 71, 75, 61, 2e, 63, 6f, 6d, 20, 7e, 61, 6c, 6c
## 4  58, 69, 48, 7a, 51, 4a, 76, 73, 4b, 6e, 79, 47, 50, 32, 4e, 6d, 32, 71, 42, 67, 4c, 33, 66, 79, 42, 4a, 30, 43, 43, 39, 7a, 34, 47, 6b, 59, 2f, 66, 6c, 66, 6b, 34, 45, 7a, 4c, 50, 38, 6c, 50, 78, 57, 48, 44, 44, 50, 4b, 71, 5a, 57, 6d, 31, 54, 6b, 65, 46, 35, 6b, 45, 49, 4c, 2b, 4e, 6f, 74, 59, 4f, 46, 31, 77, 6f, 37, 4a, 74, 55, 44, 58, 58, 77, 3d, 3d
## 5                                                                                                                                                                                                                                  20, 71, 68, 37, 68, 64, 6d, 71, 6d, 34, 6c, 7a, 73, 38, 35, 70, 37, 30, 34, 64, 36, 77, 73, 79, 62, 67, 72, 70, 73, 6c, 79, 30, 6a
## 6                                                                                                                                                                                                                                  20, 65, 63, 65, 34, 32, 64, 37, 37, 34, 33, 63, 38, 34, 64, 36, 38, 38, 39, 61, 62, 64, 61, 37, 30, 31, 31, 66, 65, 36, 66, 35, 33
## 7                                              4d, 56, 69, 73, 69, 74, 20, 77, 77, 77, 2e, 6c, 65, 6e, 6f, 76, 6f, 2e, 63, 6f, 6d, 2f, 74, 68, 69, 6e, 6b, 20, 66, 6f, 72, 20, 69, 6e, 66, 6f, 72, 6d, 61, 74, 69, 6f, 6e, 20, 61, 62, 6f, 75, 74, 20, 4c, 65, 6e, 6f, 76, 6f, 20, 70, 72, 6f, 64, 75, 63, 74, 73, 20, 61, 6e, 64, 20, 73, 65, 72, 76, 69, 63, 65, 73
## 8                                                                                  44, 67, 6f, 6f, 67, 6c, 65, 2d, 73, 69, 74, 65, 2d, 76, 65, 72, 69, 66, 69, 63, 61, 74, 69, 6f, 6e, 3d, 6e, 47, 67, 75, 6b, 63, 70, 36, 30, 72, 43, 2d, 67, 46, 78, 4d, 4f, 4a, 77, 31, 4e, 48, 48, 30, 42, 34, 56, 6e, 53, 63, 68, 52, 72, 6c, 66, 57, 56, 2d, 48, 65, 5f, 74, 45
## 9                                                                                                                      3b, 66, 61, 63, 65, 62, 6f, 6f, 6b, 2d, 64, 6f, 6d, 61, 69, 6e, 2d, 76, 65, 72, 69, 66, 69, 63, 61, 74, 69, 6f, 6e, 3d, 31, 72, 32, 61, 6d, 37, 63, 32, 62, 68, 7a, 72, 78, 70, 71, 79, 74, 30, 6d, 64, 61, 30, 64, 6a, 6f, 71, 75, 71, 73, 69
## 10                                                                                                                                                                                                                                 20, 61, 38, 32, 63, 37, 34, 62, 33, 37, 61, 61, 38, 34, 65, 37, 63, 38, 35, 38, 30, 66, 30, 65, 33, 32, 66, 34, 64, 37, 39, 35, 64
##                                                                                 txt_strings
## 1                      google-site-verification=sHIlSlj0U6UnCDkfHp1AolWgVEvDjWvc0TR4KaysD2c
## 2                      google-site-verification=VxW_e6r_Ka7A518qfX2MmIMHGnkpGbnACsjSxKFCBw0
## 3                     v=spf1 include:spf.messagelabs.com include:_netblocks.eloqua.com ~all
## 4  iHzQJvsKnyGP2Nm2qBgL3fyBJ0CC9z4GkY/flfk4EzLP8lPxWHDDPKqZWm1TkeF5kEIL+NotYOF1wo7JtUDXXw==
## 5                                                          qh7hdmqm4lzs85p704d6wsybgrpsly0j
## 6                                                          ece42d7743c84d6889abda7011fe6f53
## 7             Visit www.lenovo.com/think for information about Lenovo products and services
## 8                      google-site-verification=nGgukcp60rC-gFxMOJw1NHH0B4VnSchRrlfWV-He_tE
## 9                               facebook-domain-verification=1r2am7c2bhzrxpqyt0mda0djoquqsi
## 10                                                         a82c74b37aa84e7c8580f0e32f4d795d

cname <- doh_post("dataassurance.pwc.com", "CNAME")
tidy(cname)
##                     name class type  ttl                   cname
## 1 dataassurance.pwc.com.     1    5 1346 f6759d2.x.incapdns.net.
##                                                                                    rdata_raw
## 1 66, 36, 37, 35, 39, 64, 32, 2e, 78, 2e, 69, 6e, 63, 61, 70, 64, 6e, 73, 2e, 6e, 65, 74, 2e

ns <- doh_post("rud.is", "NS")
tidy(ns)
##      name class type   ttl          nsdname                                                      rdata_raw
## 1 rud.is.     1    2 43200  dns.mwebdns.eu.     64, 6e, 73, 2e, 6d, 77, 65, 62, 64, 6e, 73, 2e, 65, 75, 2e
## 2 rud.is.     1    2 43200  dns.mwebdns.de.     64, 6e, 73, 2e, 6d, 77, 65, 62, 64, 6e, 73, 2e, 64, 65, 2e
## 3 rud.is.     1    2 43200 dns.mwebdns.net. 64, 6e, 73, 2e, 6d, 77, 65, 62, 64, 6e, 73, 2e, 6e, 65, 74, 2e

soa <- doh_post("rud.is", "SOA")
tidy(soa)
##      name class type   ttl expire minimum           mname
## 1 rud.is.     1    6 43200 604800   86400 dns.mwebdns.de.
##                                                                                                                                                                                                                                                rdata_raw
## 1 03, 64, 6e, 73, 07, 6d, 77, 65, 62, 64, 6e, 73, 02, 64, 65, 00, 0a, 68, 6f, 73, 74, 6d, 61, 73, 74, 65, 72, 0a, 6d, 61, 6e, 64, 6f, 72, 61, 77, 65, 62, 02, 64, 65, 00, 77, ce, 5b, f3, 00, 00, 2a, 30, 00, 00, 0e, 10, 00, 09, 3a, 80, 00, 01, 51, 80
##   refresh retry                     rname     serial
## 1   10800  3600 hostmaster.mandoraweb.de. 2010012659

ptr <- doh_post(to_inaddr_arpa("104.244.13.104"), "PTR")
tidy(ptr)
##                           name class type   ttl                      ptrdname
## 1 104.13.244.104.in-addr.arpa.     1   12 43200 archive.farsightsecurity.com.
##                                                                                                            rdata_raw
## 1 61, 72, 63, 68, 69, 76, 65, 2e, 66, 61, 72, 73, 69, 67, 68, 74, 73, 65, 63, 75, 72, 69, 74, 79, 2e, 63, 6f, 6d, 2e
```

## clandnstine Metrics

| Lang | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :--- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| R    |       20 | 0.80 | 686 | 0.49 |         188 | 0.40 |      370 | 0.58 |
| C++  |        4 | 0.16 | 681 | 0.49 |         220 | 0.46 |      163 | 0.25 |
| Rmd  |        1 | 0.04 |  37 | 0.03 |          66 | 0.14 |      110 | 0.17 |

## Code of Conduct

Please note that this project is released with a [Contributor Code of
Conduct](CONDUCT.md). By participating in this project you agree to
abide by its terms.