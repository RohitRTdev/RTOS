#! /bin/bash

GREEN=
BOLD=
END=

if [ ! -z $1 ] ; then
  if [ $1 == ENABLE ] ; then
    GREEN=\\e[32m
    BOLD=\\e[1m
    END=\\e[0m
  fi
fi

echo -e "${GREEN}${BOLD}Fetching files from https://github.com/RohitRTdev/RT-mod-creator/archive/refs/tags/v1.0.tar.gz"
mkdir -p tools tools/rtmodx64
cd tools/rtmodx64 && wget https://github.com/RohitRTdev/RT-mod-creator/archive/refs/tags/v1.0.tar.gz
echo -e "Extracting files from archive"
tar -xvf v1.0.tar.gz
echo -e "Building rtmodx64"
cd RT-mod-creator-1.0 && make -s && cd ..
echo -e "Removing intermediate files${END}"
cp -r RT-mod-creator-1.0/resources . && cp RT-mod-creator-1.0/rtmodx64 .
rm -rf RT-mod-creator-1.0 v1.0.tar.gz