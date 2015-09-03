d=zeros(2,27);
for y = 1:2
    for x = 1:27
        x1=x*5-4;
        x2=x*5;
        y1=y*5-4;
        y2=y*5;
        d(y,x) = mean(mean( a(y1:y2,x1:x2) ));
    end
end