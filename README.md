
[![Travis-CI Build
Status](https://travis-ci.org/hrbrmstr/clandnstine.svg?branch=master)](https://travis-ci.org/hrbrmstr/clandnstine)
[![Coverage
Status](https://codecov.io/gh/hrbrmstr/clandnstine/branch/master/graph/badge.svg)](https://codecov.io/gh/hrbrmstr/clandnstine)
[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/clandnstine)](https://cran.r-project.org/package=clandnstine)

# clandnstine

Perform ‘DNS’ over ‘TLS’ Queries

## Description

Something something ‘DNS. Something something ’TLS’. Something something
‘getdns API/library’.

## NOTE

Requires [`getdns`](https://getdnsapi.net/) to be installed and
available for compilation (no guard rails setup yet):

  - Use `brew install getdns` on macOS
  - Install `libgetdns-dev` on debian/ubuntu
  - (Nothing to see here Windows folks stuck in a backwards ecosysem)

You’re going to need version 1.5.1 of `getdns` for this package to
install.

I’ve gotten this running on macOS and Ubuntu 16.04. For the latter I had
to ensure `libidn2-dev` and `libunbound-dev` were installed then had to
grab the 1.5.1 tarball (e.g. `aria2c
https://getdnsapi.net/releases/getdns-1-5-1/getdns-1.5.1.tar.gz`),
extract it and `config`/`make`/`make install` (plus `ldconfig` after).

## TODO/WAT

I finally grok the getdns api so the package api is going to change
wildly and fast. It’s only going to support DNS over TLS but will
support all types of DNS queries.

## Why?

Well, for starters, to help research DNS over TLS servers. Plus, for
fun\!

If you’re asking “Why DNS over TLS at all?” then “faux” privacy. Why
“faux”? Well, *something* is handing your query and that something
knows your IP address and what you looked for. So, you’re relying on the
good faith, honest nature and technical capability of the destination
server to not mess with you. I don’t trust Cloudflare or Google and am
witholding judgement on Quad9 either way (they’ve been doing good things
and are less “look at how cool we are” than CF is).

Also “faux” in that you’re going to be using a standard port (853) and a
TLS session for the queries so your internet provider will know you’re
doing *something* and the current, sorry state of SSL certificates,
certificate authorities, and authoritarian companies and regimes
combined means confidentiality and integrity are always kinda in
question unless done super-well.

## What’s Different About This vs Regular DNS?

Well, if we lookup the addresses for `yahoo.com` the old-fashioned way
it’s cleartext UDP on the
    wire:

    1   0.000000   10.1.10.57 → 10.1.10.200  DNS 80 Standard query 0x8af8 A yahoo.com OPT
    2   0.003297  10.1.10.200 → 10.1.10.57   DNS 176 Standard query response 0x8af8 A yahoo.com A 72.30.35.10 A 98.138.219.231 A 72.30.35.9 A 98.137.246.7 A 98.138.219.232 A 98.137.246.8 OPT

I watched for port 53 UDP traffic with `tshark` as `yahoo.com` was being
looked up. Notice the fast and diminuitive — and plaintext — response.
(I’m fibbing a bit since I pre-loaded the local home DNS server with
this query since I tested it alot before knitting this readme. My home
server forwards all queries to a custom DNS over TLS server since I
really don’t trust any of the providers when it comes down to it. So, in
reality for me, it’s even slower than the below — at least initially).

This is the same query via DNS over
TLS

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

  - `gdns_get_address`: Resolve a host to an addrss
  - `gdns_lib_version`: Return gdns library version
  - `gdns_query`: Arbitrary DNS queries
  - `gdns_resolver`: Create a gdns DNS over TLS context and populate it
    with a resolver for use in resolution functions

## Installation

``` r
devtools::install_git("https://gitlab.com/hrbrmstr/clandnstine.git")
# or
devtools::install_github("hrbrmstr/clandnstine")
```

## Usage

``` r
library(clandnstine)

# current version
packageVersion("clandnstine")
## [1] '0.1.0'
```

### Get an address(es) from a name:

``` r
gdns_lib_version()
## [1] "1.5.1"

(x <- gdns_resolver())
## <gdns v1.5.1 resolver context; resolvers: [9.9.9.9]>

(x <- gdns_resolver("1.1.1.1"))
## <gdns v1.5.1 resolver context; resolvers: [1.1.1.1]>

(x <- gdns_resolver(c("8.8.8.8", "1.1.1.1", "9.9.9.9")))
## <gdns v1.5.1 resolver context; resolvers: [8.8.8.8, 1.1.1.1, 9.9.9.9]>

(gdns_get_address(x, "rud.is"))
## [1] "2604:a880:800:10::6bc:2001" "104.236.112.222"

(gdns_get_address(x, "yahoo.com"))
##  [1] "2001:4998:58:1836::10" "2001:4998:c:1023::5"   "2001:4998:44:41d::4"   "2001:4998:c:1023::4"  
##  [5] "2001:4998:44:41d::3"   "2001:4998:58:1836::11" "98.137.246.8"          "98.137.246.7"         
##  [9] "98.138.219.232"        "98.138.219.231"        "72.30.35.9"            "72.30.35.10"

(gdns_get_address(x, "yahoo.commmm"))
## character(0)
```

### Any record type query:

``` r
str(leno <- gdns_query(x, "lenovo.com", "txt"), 1)
## List of 5
##  $ answer_type   : int 800
##  $ canonical_name: chr "lenovo.com."
##  $ replies_full  : int [1, 1:600] 14 77 129 128 0 1 0 8 0 0 ...
##  $ replies_tree  :'data.frame':  1 obs. of  7 variables:
##  $ status        : int 900

sort(unlist(leno$replies_tree$answer[[1]]$rdata$txt_strings))
## [1] "a82c74b37aa84e7c8580f0e32f4d795d"                                                        
## [2] "ece42d7743c84d6889abda7011fe6f53"                                                        
## [3] "facebook-domain-verification=1r2am7c2bhzrxpqyt0mda0djoquqsi"                             
## [4] "google-site-verification=VxW_e6r_Ka7A518qfX2MmIMHGnkpGbnACsjSxKFCBw0"                    
## [5] "iHzQJvsKnyGP2Nm2qBgL3fyBJ0CC9z4GkY/flfk4EzLP8lPxWHDDPKqZWm1TkeF5kEIL+NotYOF1wo7JtUDXXw=="
## [6] "qh7hdmqm4lzs85p704d6wsybgrpsly0j"                                                        
## [7] "v=spf1 include:spf.messagelabs.com include:_netblocks.eloqua.com ~all"                   
## [8] "Visit www.lenovo.com/think for information about Lenovo products and services"
```

Yep. Advertising even in DNS `TXT` records (see item number
8).

## clandnstine Metrics

| Lang | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :--- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| C++  |        3 | 0.25 | 240 | 0.59 |          66 | 0.49 |       61 | 0.19 |
| R    |        8 | 0.67 | 154 | 0.38 |          20 | 0.15 |      171 | 0.54 |
| Rmd  |        1 | 0.08 |  16 | 0.04 |          48 | 0.36 |       84 | 0.27 |

## Code of Conduct

Please note that this project is released with a [Contributor Code of
Conduct](CONDUCT.md). By participating in this project you agree to
abide by its terms.
