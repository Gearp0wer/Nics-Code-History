#!/bin/bash

ACHREAL=./compile/autoconf.h
ACH=$(mktemp)
ACC=$(mktemp)

echo '/* Automatically generated; do not edit */' > $ACH
echo '/* Automatically generated; do not edit */' > $ACC

echo '#ifndef _AUTOCONF_H_' >> $ACH
echo '#define _AUTOCONF_H_' >> $ACH

#
# first, declare struct foo_softc for all devices foo.
#

echo >> $ACH
awk < devices.attach '{ printf "struct %s_softc;\n", $2 }' >> $ACH

#
# second, declare the autoconf_foo functions for unattached devices.
#
# The autoconf_foo functions for attached devices are file-static 
# in autoconf.c.
#

echo >> $ACH
awk < devices.attach '$1=="noattach" { print $2 }' | sort -u | awk '
    {
	printf "void autoconf_%s(struct %s_softc *dev, int unit);\n", $1, $1;
    }
' >> $ACH

#
# third, declare the attach functions.
#

echo >> $ACH
awk < devices.attach '
    $1=="attach" {
	dev = $2;
	bus = $5;
	f = sprintf("struct %s_softc *attach_%s_to_%s", dev, dev, bus);
	printf "%s(int devunit, struct %s_softc *bus);\n", f, bus;
    }
    $1=="pseudo" {
	dev = $2;
	printf "struct %s_softc *pseudoattach_%s(int devunit);\n", dev, dev;
    }
' >> $ACH

#
# fourth, declare the config functions.
#

echo >> $ACH
awk < devices.attach '
    $1=="attach" {
	dev = $2;
	printf "int config_%s(struct %s_softc *dev, int unit);\n", dev, dev;
    }
' >> $ACH

#
# Declare pseudoconfig()
#
echo >> $ACH
echo 'void pseudoconfig(void);' >> $ACH
echo >> $ACH

#
# Done with the header file.
#
echo '#endif /* _AUTOCONF_H_ */' >> $ACH

#
# Avoid changing the actual autoconf.h if it's not different, so as to
# reduce unnecessary recompiles.
#

if diff $ACHREAL $ACH >/dev/null 2>&1; then
    rm -f $ACH            # unchanged
else
    mv -f $ACH $ACHREAL   # it changed
fi

#
# now, autoconf.c
#

echo '#include <types.h>' >> $ACC
echo '#include <lib.h>' >> $ACC
echo '#include "autoconf.h"' >> $ACC

#
# first, declare the static autoconf_foo functions and the nextunit_foo vars
#
echo >> $ACC
awk < devices.attach '$1=="attach" || $1=="pseudo" { print $2 }' | sort -u |\
  awk '
    { 
	printf "static void autoconf_%s(struct %s_softc *, int);\n", $1, $1;
    }
' >> $ACC
awk < devices.attach '$1=="attach" { print $2 }' | sort -u | awk '
    { 
	printf "static int nextunit_%s;\n", $1;
    }
' >> $ACC
echo >> $ACC

#
# Now generate the tryattach_ functions.
#

awk < devices.attach '
    $1=="attach" {
	dev = $2;
	bus = $5;
	printf "static\n";
	printf "int\n";
	printf "tryattach_%s_to_%s", dev, bus;
	printf "(int devunit, struct %s_softc *bus, int busunit)\n", bus;
	printf "{\n";
	printf "\tstruct %s_softc *dev;\n", dev;
	printf "\tint result;\n", dev;
	printf "\n";
	printf "\tdev = attach_%s_to_%s(devunit, bus);\n", dev, bus;
	printf "\tif (dev==NULL) {\n";
	printf "\t\treturn -1;\n";
	printf "\t}\n";
	printf "\tkprintf(\"%s%%d at %s%%d\", devunit, busunit);\n", dev, bus;
	printf "\tresult = config_%s(dev, devunit);\n", dev;
	printf "\tif (result != 0) {\n";
	printf "\t\tkprintf(\": %%s\\n\", strerror(result));\n";
		# Note: we leak the device softc instead of trying 
		# to clean it up.
	printf "\t\t/* should really clean up dev */\n";
	printf "\t\treturn result;\n";
	printf "\t}\n";
	printf "\tkprintf(\"\\n\");\n";
	printf "\tnextunit_%s = devunit+1;\n", dev;
	printf "\tautoconf_%s(dev, devunit);\n", dev;
	printf "\treturn 0;\n";
	printf "}\n";
	printf "\n";
    }
' >> $ACC
echo >> $ACC


#
# Now comes the tricky part, actually writing those autoconf
# functions.  We need one for every device. In each one, there needs
# to be a probe section for each line in $CONFTMP.attach in which that
# device appears on the *right hand* (bus) side.
#

awk < devices.attach '
    BEGIN { nlines=0; npseudo=0; }
    $1=="attach" {
	devs[nlines] = $2;
	devunits[nlines] = $3;
	buses[nlines] = $5;
	busunits[nlines] = $6;
	alldevs[$2] = 1;
	nlines++;
    }
    $1=="noattach" {
	alldevs[$2] = 0;
    }
    $1=="pseudo" {
	alldevs[$2] = 0;
	pseudodevs[npseudo] = $2;
	pseudounits[npseudo] = $3;
	npseudo++;
    }

    function genprobe(dev, devunit, bus, busunit) {

	tryfunc = sprintf("tryattach_%s_to_%s", dev, bus);
	    
	if (busunit!="*") {
	    printf "\tif (busunit==%d) {\n", busunit;
	}
	else {
	    printf "\t{\n";
	}

	if (devunit!="*") {
	    printf "\t\tif (nextunit_%s <= %d) {\n", dev, devunit;
	    printf "\t\t\t%s(%d, bus, busunit);\n", tryfunc, devunit;
	    printf "\t\t}\n";
	}
	else {
	    printf "\t\tint result, devunit=nextunit_%s;\n", dev;
	    printf "\t\tdo {\n";
	    printf "\t\t\tresult = %s(devunit, bus, busunit);\n", tryfunc;
	    printf "\t\t\tdevunit++;\n";
	    printf "\t\t} while (result==0);\n";
	}

	printf "\t}\n";
    }

    END {
	for (bus in alldevs) {
	    softc = sprintf("struct %s_softc", bus);

	    if (alldevs[bus]) printf "static\n";
	    printf "void\n";
	    printf "autoconf_%s(%s *bus, int busunit)\n", bus, softc;
	    printf "{\n";
	    printf "\t(void)bus; (void)busunit;\n";

	    for (i=0; i<nlines; i++) {
		if (buses[i]==bus) {
		    genprobe(devs[i], devunits[i], buses[i], busunits[i]);
		}
	    }

	    printf "}\n\n";
	}

	printf "void\n";
	printf "pseudoconfig(void)\n";
	printf "{\n";
	for (i=0; i<npseudo; i++) {
	    dev = pseudodevs[i];
	    unit = pseudounits[i];
	    printf "\t{\n";
	    printf "\t\tstruct %s_softc *s;\n", dev;
	    printf "\t\t\n";
	    printf "\t\ts = pseudoattach_%s(%s);\n", dev, unit;
	    printf "\t\tif (s!=NULL) {\n";
	    printf "\t\t\tkprintf(\"%s%d (virtual)\\n\");\n", dev, unit;
	    printf "\t\t\tautoconf_%s(s, %s);\n", dev, unit;
	    printf "\t\t}\n";
	    printf "\t}\n";
	}
	printf "}\n\n";
    }
' >> $ACC

if diff ./compile/autoconf.c $ACC >/dev/null 2>&1; then
    rm -f $ACC            # unchanged
else
    mv -f $ACC ./compile/autoconf.c # it changed
fi