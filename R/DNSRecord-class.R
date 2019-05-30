R6Class(

  classname = "DNSRecord",

  public = list(

    header = NULL,
    questions = list(),
    rr = list(),
    auth = list(),
    ar = list(),

    initialize = function(header = NULL, questions = NULL,
                          rr = NULL, q = NULL, a = NULL,
                          auth = NULL, ar = NULL) {

      self$header <- header %||% DNSHeader$new()
      self$questions <- questions %||% list()
      self$rr <- rr %||% list()
      self$auth <- auth %||% list()
      self$ar <- ar %||% list()

      if (length(q)) self$questions <- append(self$questions, q)
      if (length(a)) self$rr <- append(self$rr, a)

      self$set_header_qa()

    },

    question = function(qname, qtype = "A", qclass = "IN") {
      DNSRecord$new(
        q = DNSQuestion$new(
          qname = qname,
          qtype = .qtype[toupper(qtype)],
          qclass = .class[toupper(qclass)]
        )
      )
    },

    parse = function(buf, buf_pos = 1L) {

      #self$header <- NULL
      self$questions <- list()
      self$rr <- list()
      self$auth <- list()
      self$ar <- list()

      buf_pos <- 1L

      ret <- DNSHeader$new()$parse(buf)

      self$header <- ret

      buf_pos <- attr(ret, "buflen") + 1L

      message(buf_pos)

      self$questions <- lapply(1:self$header$q, function(.idx) {

        ret <- DNSQuestion$new()$parse(buf, buf_pos)
        buf_pos <<- buf_pos + attr(ret, "buflen")
        ret

      })

      self

    },

    # Reset header q/a/auth/ar counts to match numver of records (normally done transparently)

    set_header_qa = function() {
      self$header$q <- length(self$questions)
      self$header$a <- length(self$rr)
      self$header$auth <- length(self$auth)
      self$header$ar <- length(self$ar)
    },

    pack = function() {
      out <- self$header$pack()
      for (q in self$questions) out <- c(out, q$pack())
      out
    }

  ),

  private = list(
  )

) -> DNSRecord
