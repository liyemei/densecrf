#include <math.h> /* Needed for the ceil() prototype */
#include "mex.h"
#include <iostream>

#include "densecrf.h"
#include <cstdio>
#include <cmath>

// note: the weight of the unary should be set outside the function
/*@params
  	unary (num_labels*num_pixels) 
  	img (channel  * width * height) 
  	x_std, y_std, w_smooth, 
  	x_std_bilateral, y_std_bilateral, r_std, g_std, b_std, w_bilateral, 
  	width, height
*/
/* @output:
	map (0 - num_label-1)
	probability
*/

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	double x_std, y_std, w_smooth;
	double x_std_b, y_std_b, r_std, g_std, b_std, w_bilateral;
	int width, height, labels;

	// check input and output parameters

	if (nrhs < 12 ) {
		mexErrMsgTxt("12 inputs required (unary, color_image, x_std, y_std, w_smooth, x_std_bilateral, y_std_bilateral, r_std, g_std, b_std, w_bilateral, img_width, img_height)");
	}

	// unary (be careful about c++ index and matlab index)
	if(!mxIsSingle(prhs[0])) {
		mexErrMsgTxt("Input matrix 1 must be float.");
	}
	float *unary = (float *) mxGetData(prhs[0]);
	labels = mxGetM(prhs[0]);
	
	if (!mxIsUint8(prhs[1])) {
		mexErrMsgTxt("Input matrix 2 must be uint8.");	
	}
	if (mxGetM(prhs[1]) != 3) {
		mexErrMsgTxt("Input matrix 2 must have 3 channels (channel  * width * height).");	
	}
	unsigned char * img = (unsigned char *) mxGetPr(prhs[1]);

	x_std = mxGetScalar(prhs[2]); 
	y_std = mxGetScalar(prhs[3]); 
	w_smooth = mxGetScalar(prhs[4]);

	x_std_b = mxGetScalar(prhs[5]); 
	y_std_b = mxGetScalar(prhs[6]); 
	r_std = mxGetScalar(prhs[7]);
	g_std = mxGetScalar(prhs[8]);
	b_std = mxGetScalar(prhs[9]);
	w_bilateral = mxGetScalar(prhs[10]);

	width = mxGetScalar(prhs[11]);
	height = mxGetScalar(prhs[12]);

	plhs[0] = mxCreateNumericMatrix(height, width, mxINT32_CLASS, mxREAL);
	plhs[1] = mxCreateNumericMatrix(height*width*labels, 1, mxSINGLE_CLASS, mxREAL);

	int *map = (int *)mxGetData(plhs[0]);
	float *prob = (float *)mxGetData(plhs[1]);

	int iter = 10;

	DenseCRF2D crf(width, height, labels);

	crf.setUnaryEnergy( unary);

	crf.addPairwiseGaussian( x_std, y_std, w_smooth);
	
	crf.addPairwiseBilateral( x_std_b, y_std_b, r_std, g_std, b_std, img, w_bilateral);

	crf.map(iter, map, prob);
}