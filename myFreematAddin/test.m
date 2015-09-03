f1 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer498.bmp';
f2 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer504.bmp';
f3 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer510.bmp';

f1 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer00.bmp';
f2 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer06.bmp';
f3 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer12.bmp';


A1=imread(f1);
A2=imread(f2);
A3=imread(f3);
y=640/2;
rShiftPixel = 665.5*2.197 / 21.03
plot(A1(y,:),'r',A2(y,:),'g',A3(y,:),'b')
axis on
