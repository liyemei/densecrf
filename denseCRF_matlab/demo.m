clc; clear; close all;

addpath('src/');

% parameter setting
fullcrfPara.uw = 1; 
fullcrfPara.sw = 8; 
fullcrfPara.bw = 9;
fullcrfPara.s = 5;  
fullcrfPara.bl = 31; 
fullcrfPara.bc = 15;

numlabels = 14;

% Load unary (textonboost)
[textonboost, L_t] = loadTextonboost('test.unary', numlabels);
  
% Load colorimg
img = imread('test.png');

% convert matlab index to c++ index
u = -1*textonboost;
u = reshape(u, size(img, 1), size(img, 2), numlabels);
u = permute(u, [2 1 3]);
u = reshape(u, size(img, 1)*size(img, 2), numlabels);
u = u'*fullcrfPara.uw;

tmpImg = reshape(img, [], 3);
tmpImg = tmpImg';
tmpImg = reshape(tmpImg, 3, size(img, 1), size(img, 2));
tmpImg = permute(tmpImg, [1 3 2]);

% Do the hard work
tic;

%note: the weight of the unary should be set outside the function
%{
@params
  	unary (num_labels*num_pixels) 
  	img (channel  * width * height) 
    ...
@output:
	map (0 - num_label-1)
	probability
%}

[L, prob] = fullCRFinfer(single(u), uint8(tmpImg), fullcrfPara.s, fullcrfPara.s, ...  
    fullcrfPara.sw, fullcrfPara.bl, fullcrfPara.bl, fullcrfPara.bc, fullcrfPara.bc, ... 
    fullcrfPara.bc, fullcrfPara.bw, size(img, 2), size(img, 1));
toc;

map = (reshape(L, size(img, 2), size(img, 1)))';
p = reshape(prob, numlabels, size(img, 2), size(img, 1));
p = permute(p, [3 2 1]);

figure; imagesc(map);truesize;colormap jet;
figure; imshow(img);
