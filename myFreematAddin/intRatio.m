 w=0.1;
 x=1:100;
 y=sin(w*x);
 ymin=sin(w*x-2*pi/3);
 ymax=sin(w*x+2*pi/3);
 r=zeros(100,1);
 
 for i=1:100
     t=[y(i),ymin(i),ymax(i)];
     
     t=sort(t);
     r(i)=(t(2)-t(1))/(t(3)-t(1));
 end
 r
 plot(r)
