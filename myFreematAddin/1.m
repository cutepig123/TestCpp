clear,clc
P0=loadTiff2('\\aeecsyip\WinEagle\log\Autorpt\WISI1031\pair2\Thick\profile.tif_r.dat.tif');
M0=imread('\\aeecsyip\WinEagle\log\Autorpt\WISI1031\pair2\Thick\profile.tif_ub.bmp');

off=[2146 142]
sz=[183 17]
LR=off+sz-1

P0ROI=P0( 1+(off(2):LR(2)), 1+(off(1):LR(1)) );
M0ROI=M0( 1+(off(2):LR(2)), 1+(off(1):LR(1)) );

P=P0ROI(M0ROI~=0);
mean(P)
