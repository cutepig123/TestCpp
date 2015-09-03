Ix=rand
Ixx=rand
fai=rand*pi
alpha=120/180*pi
I1=Ix+Ixx*cos(fai-alpha)
I2=Ix+Ixx*cos(fai)
I3=Ix+Ixx*cos(fai+alpha)
fai_cmp=atan(sqrt(3)*(I1-I3)/(2*I2-I1-I3))
%fai_cmp should == fai
