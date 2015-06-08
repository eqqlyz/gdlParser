#!/bin/sh

for file in `ls *.gdl`
do
  echo $file
  ./gdl2cfg $file  > "output/zzz_"$file
done

  
