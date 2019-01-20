context("basic wrapper works")
test_that("we can do something", {

  x <- get_address("example.com")
  expect_true(all(c("2606:2800:220:1:248:1893:25c8:1946", "93.184.216.34") %in% x))

})
