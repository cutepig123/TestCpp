%clear,clc
a=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair0\Thick\profile.tif_r.dat.tif');
b=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair1\Thick\profile.tif_r.dat.tif');
c=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair2\Thick\profile.tif_r.dat.tif');

x1=mean(a(:,215+(2000:2100)),2);
x2=mean(b(:,415+(2000:2100)),2);
x3=mean(c(:,615+(2000:2100)),2);
X=[x1;x2;x3];
figure,plot(X);grid on;title('Thick')

a2=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair0\top\ProfAfShear.tif');
b2=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair1\top\ProfAfShear.tif');
c2=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair2\top\ProfAfShear.tif');

t1=mean(a2(:,215+(2000:2100)),2);
t2=mean(b2(:,415+(2000:2100)),2);
t3=mean(c2(:,615+(2000:2100)),2);
T=[t1;t2;t3];
figure,plot(T);grid on;title('top')

a3=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair0\btm\ProfAfShear.tif');
b3=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair1\btm\ProfAfShear.tif');
c3=loadTiff('\\vis_3d_stereo\c$\WinEagle\log\AutoRpt\CALINS\WISL0241\pair2\btm\ProfAfShear.tif');

b1=mean(a3(:,215+(2000:2100)),2);
b2=mean(b3(:,415+(2000:2100)),2);
b3=mean(c3(:,615+(2000:2100)),2);
B=[b1;b2;b3];
figure,plot(B);grid on;title('btm')