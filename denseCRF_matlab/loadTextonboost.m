function [unary, L] = loadTextonboost(filename, numLabels)

% load binary textonboost unary
% 	Input
%	    numLabels: number of labels
%	    filename: filename of the textonboost unary
%	Output
%	    unary: textonboost unary (dim: length * numLabels)
%	    L: label map from the max likelihood in matrix format (for debug) 
%(c)2015 Jun Xie


fileID = fopen(filename,'rb'); 
if (fileID > 0)
    [dim, len] = fread(fileID, 3, '*int');
    [unary, l] = fread(fileID, '*single');
    fclose(fileID);
else 
    error('No textonboost file %s \n.', filename);
end

assert(numLabels == dim(3));

% manipulate matrix
unary = reshape(unary, dim(3), []);
unary = unary';
unary = reshape(unary, dim(1), dim(2), []);
unary = permute(unary, [2 1 3]);

[~, L] = max(unary, [], 3);

% transform to matlab index
unary = reshape(unary, [], dim(3));

