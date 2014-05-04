#!/bin/sh
#
#

BANG_GROUP=bangdb
SYS_LIB_DIR=/usr/local/lib
DEST_INCLUDE_DIR=/usr/local/include

read -p 'Do you want to uninstall bangdb(y/n)? : ' YN
if [ "$YN" == 'n' ]; then
echo "exiting..."
exit
fi

groupdel $BANG_GROUP
echo "group " $BANG_GROUP " deleted"

rm -rf $DEST_INCLUDE_DIR/$BANG_GROUP

echo "headers deleted from the sys local include dir"

rm $SYS_LIB_DIR/libbangdb.so*

echo "removed the soft link to the lib.so"

echo "uninstall completed successfully!, you may manually delete the data dir when needed"






