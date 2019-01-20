g++ singleFunctionFit.cxx -o singleFunctionFit `root-config --glibs --cflags` -lRooFit -lRooFitCore
g++ drawNll.cxx -o drawNll `root-config --glibs --cflags`

./singleFunctionFit -i 10 -p -s
./singleFunctionFit -i 10 -l -s
./singleFunctionFit -i 10 -s
./drawNll

