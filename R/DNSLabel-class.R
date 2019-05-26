R6Class(

  classname = "DNSLabel",

  public = list(

    label = NULL,

    initialize = function(label) {

      if (inherits(label, "DNSLabel")) {

        self$label <- label$label

      } else if (length(label) > 1) {

        self$label <- as.character(label)

      } else if (is.character(label)) {
        label <- sub("\\.$", "", label)
        self$label <- unlist(strsplit(label, "\\."), use.names = FALSE)
      }

    },

    encode = function() {

      sz <- nchar(self$label)
      out <- raw()
      for (i in seq_along(self$label)) {
        out <- c(out, as.raw(sz[[i]]), charToRaw(self$label[[i]]))
      }
      c(out, as.raw(0x00))

    },

    parse = function(buf, buf_pos) {

    }

  )

) -> DNSLabel
