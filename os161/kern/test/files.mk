SRCS-y += arraytest.c bitmaptest.c fstest.c malloctest.c queuetest.c \
	synchtest.c threadtest.c tt3.c

# Only include nettest.c when OPT_NET is set
SRCS-$(OPT_NET) += nettest.c