f1 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer498.bmp';

f2 = '\\vis_3d_solar\c$\WinEagle\20101117cal&insp\WISI0051\buffer00.bmp';


A1=imread(f1);
A2=imread(f2);

y=640/2;
rShiftPixel = 665.5*2.197 / 21.03

y1=mean(A1((y-5):(y+5),:),1);
y2=mean(A2((y-5):(y+5),:),1);
plot(y1,'r',y2,'g')
axis on
