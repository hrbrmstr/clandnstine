context("basic wrapper works")
test_that("basic wrapper works", {

  expect_is(gdns_lib_version(), "character")

  r <- gdns_context()
  expect_is(r, "gctx")

  expect_is(gdns_lib_version(), "character")

  expect_equal(gdns_get_resolution_type(r), "stub")

  x <- gdns_get_address(r, "example.com")
  expect_true(all(c("2606:2800:220:1:248:1893:25c8:1946", "93.184.216.34") %in% x))

  expect_error(gdns_set_timeout(x, 3000))

  expect_is(gdns_update_resolvers(r, c("8.8.8.8", "1.1.1.1", "9.9.9.9")), "gctx")
  expect_is(gdns_set_round_robin_upstreams(r, TRUE), "gctx")
  expect_is(gdns_set_hosts(r, "/etc/hosts"), "gctx")
  expect_is(gdns_set_timeout(r, 2000), "gctx")

  expect_error(gdns_set_hosts(r, "/etc/hostssss"))

  x <- gdns_get_address(r, "example.com")
  expect_true(all(c("2606:2800:220:1:248:1893:25c8:1946", "93.184.216.34") %in% x))

  x <- gdns_get_address(r, "example.commm")
  expect_length(x, 0)

  x <- gdns_query(r, "example.com", "txt")

  expect_equal(x$answer_type, 800)
  expect_equal(x$canonical_name, "example.com.")
  expect_true(grepl("spf", unlist(x$replies_tree$answer[[1]]$rdata$txt_strings)))

  expect_equal(gdns_get_transports(r), "tls")
  expect_is(gdns_set_transports(r, c("udp", "tls")), "gctx")
  expect_equal(gdns_get_transports(r), c("udp", "tls"))

  expect_true(
    all(c("2606:2800:220:1:248:1893:25c8:1946", "93.184.216.34") %in%
          gdns_get_address(r, "example.com"))
  )

})
