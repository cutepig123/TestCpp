function [Y,X]=meshgrid(ny,nx)
n = ny*nx;
P =[];
for y=1:ny
    x =1:nx;
    p = zeros(2,nx);
    p(1,:) = x;
    p(2,:) = y;
    P =[P p];
end
X=P(1,:);
Y=P(2,:);
