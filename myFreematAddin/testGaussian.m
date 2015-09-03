%Gaussian filters are designed to give no overshoot to a step function input while minimizing the rise and fall time

delta=3;
x=-15:15;
k=exp(-x.*x/2/delta/delta)/sqrt(2*pi)/delta;
sum(k) %==1!


y_in=zeros(500,0);
y_in(250:500)=1;

y_resp=conv2(y_in,k,'valid');
plot(y_resp);
