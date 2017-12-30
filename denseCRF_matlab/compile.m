clear; clc;

cd src
mex -largeArrayDims fullCRFinfer.cpp util.cpp bipartitedensecrf.cpp permutohedral.cpp densecrf.cpp filter.cpp 

cd ..

disp('Done!');