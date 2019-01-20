context("basic wrapper works")
test_that("basic wrapper works", {

  expect_is(gdns_lib_version(), "character")

  r <- gdns_resolver()

  x <- gdns_get_address(r, "example.com")
  expect_true(all(c("2606:2800:220:1:248:1893:25c8:1946", "93.184.216.34") %in% x))

  r <- gdns_resolver(c("8.8.8.8", "1.1.1.1", "9.9.9.9"))

  x <- gdns_get_address(r, "example.com")
  expect_true(all(c("2606:2800:220:1:248:1893:25c8:1946", "93.184.216.34") %in% x))

  x <- gdns_get_address(r, "example.commm")
  expect_length(x, 0)

  x <- gdns_query(r, "example.com", "txt")

  expect_equal(x$answer_type, 800)
  expect_equal(x$canonical_name, "example.com.")
  expect_true(grepl("spf", unlist(x$replies_tree$answer[[1]]$rdata$txt_strings)))

})
