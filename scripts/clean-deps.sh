#! /bin/bash

FILES=$(ls)
DIRFILES=

for file in $FILES ; do if [ -d $file ] ; then DIRFILES+=$file' ' ; fi ; done

for dir in $DIRFILES ; do for file in $(find $dir -name "Makefile") ; do make -f $file clean-dep ; done ; done 





 