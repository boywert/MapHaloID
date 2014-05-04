#!/bin/sh
#
#assumes that the lib.so is in the same dir as the install-bangdb.sh file
#

BANG_GROUP=bangdb
BANGDB_DATA=bangdbdata
BANG_LIB_NAME=libbangdb.so.1.4
SYS_LIB_DIR=/usr/local/lib
SRC_INCLUDE_DIR=include
DEST_INCLUDE_DIR=/usr/local/include
BANG_CONFIG=bangdb.config

read -p 'Enter the user name (user who will use the db) : ' USER_NAME
#read -p 'Enter the dir to install (pls provide full path, create if does not exist) : ' BANG_DIR
#read -p "NOTE: set SERVER_DIR = $BANG_DIR[/bangdata/] in the bangdb.config file : (enter for ok)" OK

#BANG_DATA_DIR=$BANG_DIR/$BANGDB_DATA
#if [ -d $BANG_DIR ]; then
#echo "install dir already exists"
#else
#mkdir $BANG_DIR
#fi

groupadd $BANG_GROUP
echo "group " $BANG_GROUP " created"
usermod -a -G $BANG_GROUP $USER_NAME

cp $BANG_LIB_NAME $SYS_LIB_DIR/
echo "copied the bangdb lib.so to sys local lib dir"

ln -sf $SYS_LIB_DIR/$BANG_LIB_NAME $SYS_LIB_DIR/libbangdb.so
ln -sf $SYS_LIB_DIR/libbangdb.so $SYS_LIB_DIR/libbangdb.so.0
echo "created the soft link to the lib."

ldconfig 

mkdir $DEST_INCLUDE_DIR/$BANG_GROUP
cp $SRC_INCLUDE_DIR/*.h $DEST_INCLUDE_DIR/$BANG_GROUP

echo "copied the include dir in to the sys local include dir, install completed successfully!"
