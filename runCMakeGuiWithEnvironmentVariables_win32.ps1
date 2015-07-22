##
#
# Example of a shell script to run cmake-gui with all the needed environement variables.
#
##

# Please modify the path to HDF5_ROOT according to your configuration
if ($Env:HDF5_ROOT)
{
	'HDF5_ROOT already set to ' + $Env:HDF5_ROOT
}
else
{
	'Need to set HDF5_ROOT'
	$Env:HDF5_ROOT = Join-Path (Get-Location) "..\dependencies\hdf5-1.8.15-patch1-win32-vs2012-shared"
}

# Please modify the path to MINIZIP_DIR according to your configuration
if ($Env:MINIZIP_DIR)
{
	'MINIZIP_DIR already set to ' + $Env:MINIZIP_DIR
}
else
{
	'Need to set MINIZIP_DIR'
	$Env:MINIZIP_DIR = Join-Path (Get-Location) "..\dependencies\minizip-win32-vs2012-static"
}

# Please modify the path to cmake-gui according to your configuration
C:\Progra~2\CMake\bin\cmake-gui .
