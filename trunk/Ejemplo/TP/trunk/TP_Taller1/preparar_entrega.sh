#!/bin/sh

dirEntrega=TP1_Taller
nombreEntrega=TP1_Taller

##########

mkdir -p $dirEntrega

for emt in fonts imagenes src Makefile README.TXT .project .cproject 
do
  cp -R $emt $dirEntrega
done

find $dirEntrega -name .svn -delete

zip -r $nombreEntrega.zip $dirEntrega > /dev/null
md5sum $nombreEntrega.zip > $nombreEntrega.md5

rm -rf $dirEntrega
