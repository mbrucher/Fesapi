rm ../cs/src/*.cs
rm ../cs/src/resqml2_0/*.cs
rm ../cs/src/witsml1_4_1_1/*.cs
C:\Users\Philippe\appli\swigwin-3.0.5\swig -c++ -csharp -dllimport F2iEnergisticsStandardsCppApi.dll -namespace f2i.energisticsStandardsApi -o swigGeneratedCsWrapper.cpp -outdir ../cs/src swigModule.i
