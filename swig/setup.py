from distutils.core import setup, Extension

fesapi_module = Extension('_fesapi',
	sources=['swigGeneratedPythonWrapper.cpp',
	],
	include_dirs=['../src',
		'../src/epc',
		'../src/proxies',
		'../../../appli/minizip_unofficial/install/include',
	],
	library_dirs=['../../buildForFesapi/src'],
	libraries=['FesapiCpp',],
)

setup (name = 'fesapi',
	version = '0.1',
	author      = "F2I-CONSULTING",
	description = """An API for the Energistics standards""",
	ext_modules = [fesapi_module],
	py_modules = ["fesapi"],
)
