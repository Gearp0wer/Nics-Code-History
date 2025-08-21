# This is a dummy pointer back to the needed files from libc.

LIBC_SRCS-y=

LIBC_SRCS-y+=__printf.c snprintf.c

# C files for standard string operations
LIBC_SRCS-y+=atoi.c bzero.c \
      memcmp.c memcpy.c memmove.c memset.c \
      strcat.c strchr.c strcmp.c strcpy.c strlen.c strrchr.c \
      strtok.c strtok_r.c

# Machine-dependent setjmp implementation
LIBC_SRCS-y+=$(PLATFORM)-setjmp.S

SRCS-y += $(addprefix ../../lib/libc/,$(LIBC_SRCS-y))