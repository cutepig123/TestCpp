a=imread('\\vis_3d_stereo2\c\WinEagle\log\AutoRpt\WISL0042\cam5\trig31\buffer0_AfWarp.bmp');
b=imread('\\vis_3d_stereo2\c\WinEagle\log\AutoRpt\WISL0042\cam5\trig31\buffer1_AfWarp.bmp');
c=imread('\\vis_3d_stereo2\c\WinEagle\log\AutoRpt\WISL0042\cam5\trig31\buffer2_AfWarp.bmp');
plot(a(120,:))
hold on 
plot(b(120,:))
hold on 
plot(c(120,:))