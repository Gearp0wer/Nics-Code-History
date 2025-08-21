ifeq ($(MAKEFILE_COLORS),y)
echo-color=echo -e "$$(tput setaf $(1))$(2)$$(tput sgr0)$(3)"
else
echo-color=echo -e "$(2)$(3)"
endif

# Arguments: do-link <target> <sources> <ldflags>
do-link=@$(call echo-color,5,LINK    ,$(1)); $(LD) $(2) $(3) -o $(1) 

# Arguments: do-ar <target> <.os>
do-ar=@$(call echo-color,1,AR      ,$(1)); sh $(OSTREE)/mk/ar-indirect.sh $(AR) $(1) $(2)

# Arguments: do-cc <.o> <.c> <cflags>
do-cc=@$(call echo-color,2,CC      ,$(2)); $(CC) -MD $(2) -c -o $(1) $(3)

# Arguments: do-symlink <to> <from>
do-symlink=@$(call echo-color,6,LN      ,$(1)); rm -f $(1); ln -s $(2) $(1)

# Arguments: do-install <from> <to>
do-install=@$(call echo-color,4,INSTALL ,$(2)); cp -f $(1) $(2)

# Arguments: do-show-gen <filename>
do-show-gen=@$(call echo-color,6,GEN     ,$(1))

# Arguments: do-show-rebuild <filename>
# Note: Implemented manually by depend.mk as well
do-show-rebuild=@$(call echo-color,3,REBUILD ,$(1))

# Arguments: do-show-clean <what is being cleaned>
do-show-clean=@$(call echo-color,3,CLEAN   ,$(1))

# Arguments: do-clean <target file>
do-clean=@if [ -f $(1) ]; then \
	$(call echo-color,3,CLEAN   ,$(1)); \
	rm -f $(1); \
fi

do-clean-symlink=@if [ -h $(1) ]; then \
	$(call echo-color,3,CLEAN   ,$(1)); \
	rm -f $(1); \
fi

do-clean-dir=@if [ -d $(1) ]; then \
	$(call echo-color,3,CLEAN   ,$(1)); \
	rm -rf $(1); \
fi