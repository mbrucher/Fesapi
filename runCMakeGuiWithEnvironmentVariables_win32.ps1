##
#
# Example of a shell script to run cmake-gui with all the needed environement variables.
#
##

# Please modify the path to HDF5_DIR according to your configuration
if ($Env:HDF5_DIR)
{
	'HDF5_DIR already set to ' + $Env:HDF5_DIR
}
else
{
	'Need to set HDF5_DIR'
	$Env:HDF5_DIR = Join-Path (Get-Location) "../dependencies/hdf5-1.8.16-win32-vs2013/cmake"
}

# Please modify the path to MINIZIP_DIR according to your configuration
if ($Env:MINIZIP_DIR)
{
	'MINIZIP_DIR already set to ' + $Env:MINIZIP_DIR
}
else
{
	'Need to set MINIZIP_DIR'
	$Env:MINIZIP_DIR = Join-Path (Get-Location) "../dependencies/minizip-win32-vs2013-static"
}

# Please modify the path to cmake-gui according to your configuration
C:\Progra~2\CMake\bin\cmake-gui .
