SRCS-y += array.c bitmap.c kgets.c kheap.c kprintf.c misc.c ntoh.c queue.c

# Note: We don't include copyinout.c here, as it has some machine dependent
# assumptions. Instead, it is include under arch/mips/mips.