% solve Ax+By+C=0

%generate X Y
N=20;
Y=rand(N,1);
%generate a,b,c
a=rand;
b=rand;
c=rand;
ABC=[a,b,c]/norm([a,b])
X=-(b*Y+c)/a;

%solve
[U,S,V]=svd([X-mean(X), Y-mean(Y)]);
AB = V(:,2)
C = -(AB(1)*mean(X)+AB(2)*mean(Y))
