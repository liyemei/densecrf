# DenseCRF

This is a (Cython-based) Python wrapper for Philipp Krähenbühl's Fully-Connected CRFs (version 2).

If you use this code for your reasearch, please cite:


```
Efficient Inference in Fully Connected CRFs with Gaussian Edge Potentials
Philipp Krähenbühl and Vladlen Koltun
NIPS 2011
```
# Interface
-  Win64  python2.7 <pydensecrf-py27>
-  Win64  python3.5 <pydensecrf-py35>
-  Win64  MATLAB2016 <denseCRF_matlab>
# Installation
- Download code 

```
git clone https://github.com/liyemei/densecrf
```
-  Renameing
```
Renameing the file  "pydensecrf-py27" or 
"pydensecrf-py35" to the new name  "pydensecrf"
```
- Installing package

```
Puting this file "pydensecrf" in this directory "C:\Program Files\Anaconda3\Lib\site-packages"
```
- denseCRF_matlab  can  be run directly 
# Example
- Python 
> Run on the command line

```
cd examples/
python inference.py  im1.png anno1.png out.png
```
![image](https://github.com/liyemei/densecrf/blob/master/examples/out1.png?raw=true)

- Matlab 


---
 run the demo.m
# Thanks for above code
>
```
https://github.com/ClaireXie/denseCRF_matlab
```

```
https://github.com/lucasb-eyer/pydensecrf
```
