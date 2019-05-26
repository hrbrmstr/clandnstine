R6Class(

  classname = "DNSHeader",

  public = list(

    q = NULL,
    a = NULL,
    id = NULL,
    auth = NULL,
    bitmap = 0L,
    qr = NULL,
    opcode = NULL,
    aa = NULL,
    tc = NULL,
    rd = NULL,
    ra = NULL,
    z = NULL,
    ad = NULL,
    ar = NULL,
    cd = NULL,
    rcode = NULL,

    set_rd = function(val) {

      bits(self$bitmap, 8) <- as.integer(val)

    },

    initialize = function(id = NULL, bitmap = NULL, q = 0L,
                          a = 0L, auth = 0L, ar = 0L, ...) {

      self$id <- id %||% sample(0:65535, 1)

      self$bitmap <- bitmap %||% 0L
      if (is.null(bitmap)) self$set_rd(1L)

      self$q <- q
      self$a <- a
      self$auth <- auth
      self$ar <- ar

      valid <- c("qr", "opcode", "aa", "tc", "rd", "ra", "z", "ad", "cd", "rcode")

      args <- list(...)
      args <- setNames(args, tolower(colnames(args)))
      args <- Filter(Negate(is.null), args[valid])

      for (n in names(args)) self[[n]] <- args[[n]]

    },

    parse = function(buf, buf_pos = 1L) {

      self$id <- readBin(buf[buf_pos:(buf_pos+1)], "int", size = 2, endian = "big")
      self$bitmap <- readBin(buf[(buf_pos+2):(buf_pos+3)], "int", size = 2, endian = "big")
      self$q <- readBin(buf[(buf_pos+4):(buf_pos+5)], "int", size = 2, endian = "big")
      self$a <- readBin(buf[(buf_pos+6):(buf_pos+7)], "int", size = 2, endian = "big")
      self$auth <- readBin(buf[(buf_pos+8):(buf_pos+9)], "int", size = 2, endian = "big")
      self$ar <- readBin(buf[(buf_pos+10):(buf_pos+11)], "int", size = 2, endian = "big")

      attr(self, "buflen") <- 12L

      self

    },

    pack = function() {

      c(
        writeBin(as.integer(self$id), raw(), size = 2, endian = "big"),
        writeBin(as.integer(self$bitmap), raw(), size = 2, endian = "big"),
        writeBin(as.integer(self$q), raw(), size = 2, endian = "big"),
        writeBin(as.integer(self$a), raw(), size = 2, endian = "big"),
        writeBin(as.integer(self$auth), raw(), size = 2, endian = "big"),
        writeBin(as.integer(self$ar), raw(), size = 2, endian = "big")
      )

    }

  )

) -> DNSHeader
