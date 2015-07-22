#! /bin/csh -f
#
# Example of a shell script to run cmake-gui with all the needed environement variables.
# Mainly used when you did not install fesapi dependencies by means of apt-get but by means of source code.
#
##

# Please modify the path to HDF5_ROOT according to your configuration
if ! $?HDF5_ROOT then
	echo "Need to set HDF5_ROOT"
	setenv HDF5_ROOT /data_local/philippeVerney/appli/hdf5-1.8.14-linux-centos6-x86_64-gcc447-shared
else
	echo "HDF5_ROOT already set."
endif

# Please modify the path to UUID_DIR according to your configuration
if ! $?UUID_DIR then
	echo "Need to set UUID_DIR"
	setenv UUID_DIR /data_local/philippeVerney/appli/libuuid
else
	echo "UUID_DIR already set."
endif

# Please modify the path to MINIZIP_DIR according to your configuration
if ! $?MINIZIP_DIR then
	echo "Need to set MINIZIP_DIR"
	setenv MINIZIP_DIR /data_local/philippeVerney/appli/minizip_unofficial
else
	echo "MINIZIP_DIR already set."
endif

# Please modify the path to cmake-gui according to your configuration
/data_local/philippeVerney/appli/cmake-3.1.3-Linux-x86_64/bin/cmake-gui .
