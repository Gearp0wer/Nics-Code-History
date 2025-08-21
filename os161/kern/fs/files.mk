SRCS-y += vfs/

# entire sfs directory is only needed when OPT_SFS is set
SRCS-$(OPT_SFS) += sfs/