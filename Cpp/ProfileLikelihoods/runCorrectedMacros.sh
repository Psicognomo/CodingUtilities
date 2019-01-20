g++ singleFunctionFit.cxx -o singleFunctionFit `root-config --glibs --cflags` -lRooFit -lRooFitCore
g++ drawNll.cxx -o drawNll `root-config --glibs --cflags`

./singleFunctionFit -i 10 -p -c -s
./singleFunctionFit -i 10 -l -c -s 
./singleFunctionFit -i 10 -c -s
./drawNll

