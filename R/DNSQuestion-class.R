R6Class(

  classname = "DNSQuestion",

  public = list(

    qname = NULL,
    qtype = NULL,
    qclass = NULL,

    initialize = function(qname = NULL, qtype = 1L, qclass = 1L) {

      if (inherits(qname, "DNSLabel")) {
        self$qname <- qname
      } else {
        if (length(qname)) self$qname <- DNSLabel$new(qname)
      }

      self$qtype <- qtype
      self$qclass <- qclass

    },

    pack = function() {
      c(
        self$qname$encode(),
        writeBin(as.integer(self$qtype), raw(), size = 2, endian = "big"),
        writeBin(as.integer(self$qclass), raw(), size = 2, endian = "big")
      )
    },

    parse = function(buf, buf_pos = 1L) {

      ret <- DNSLabel$new()$parse(buf, buf_pos)

      self$qname <- ret

      buf_pos <- buf_pos + attr(ret, "buflen")

      self$qtype <- readBin(buf[buf_pos:(buf_pos+1)], "int", size = 2, endian = "big")
      self$qclass <- readBin(buf[(buf_pos+2):(buf_pos+3)], "int", size = 2, endian = "big")

      attr(self, "buflen") <- attr(ret, "buflen") + 4L

      self

    }

  )

) -> DNSQuestion
