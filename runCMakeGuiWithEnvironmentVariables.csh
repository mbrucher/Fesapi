#! /bin/csh -f
#
# Example of a shell script to run cmake-gui with all the needed environement variables.
# Mainly used when you did not install fesapi dependencies by means of apt-get but by means of source code.
#
##

# Please modify the path to JAVA_HOME according to your configuration
if ! $?JAVA_HOME then
	echo "Need to set JAVA_HOME"
	setenv JAVA_HOME pathToJava
else
	echo "JAVA_HOME already set."
endif

# Please modify the path to HDF5_ROOT according to your configuration
if ! $?HDF5_ROOT then
	echo "Need to set HDF5_ROOT"
	setenv HDF5_ROOT ../dependencies/hdf5-1.8.10-linux-x86_64-shared
else
	echo "HDF5_ROOT already set."
endif

# Please modify the path to SZIP_INSTALL according to your configuration
if ! $?SZIP_INSTALL then
	echo "Need to set SZIP_INSTALL"
	setenv SZIP_INSTALL $HDF5_ROOT
else
	echo "SZIP_INSTALL already set."
endif

# Please modify the path to UUID_DIR according to your configuration
if ! $?UUID_DIR then
	echo "Need to set UUID_DIR"
	setenv UUID_DIR ../dependencies/libuuid
else
	echo "UUID_DIR already set."
endif

# Please modify the path to MINIZIP_DIR according to your configuration
if ! $?MINIZIP_DIR then
	echo "Need to set MINIZIP_DIR"
	setenv MINIZIP_DIR ../dependencies/minizip_unofficial
else
	echo "MINIZIP_DIR already set."
endif

# Please modify the path to cmake-gui according to your configuration
/data_local/philippeVerney/appli/cmake-3.3.0/bin/cmake-gui ./fesapi
