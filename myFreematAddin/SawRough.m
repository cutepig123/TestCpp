function SawRough(path)
     [P0,s0]=loadTiff(path);
     P=Rough(P0);
     figure,plot(P)
    %Main(path)

function Main(path)
   listing= dir(sprintf('%s\\WISI*', path));
   N= length(listing);
   for i=1:N
       casepath=sprintf('%s\\%s', path, listing(i).name)
       Case(casepath)
   end
       
function Case(path)
    fp = fopen('sawrough.log','a');
    fprintf(fp,'\n');
    figure
    
    %l=cell(6);
    for i=0:2
        for j=1:2
            %l{i*sprintf('pair%d_cam%d',i,j)};
            
            tb={'top','btm'};
            fullpath=sprintf('%s\\pair%d\\%s\\SawMark\\diff_x.tif',path,i,tb{j})
            [P0,s0]=loadTiff(fullpath);
            if s0~=0
                error 'error loadTiff found'
            end
            
            P=Rough(P0)
            hold on, plot(P)
            
            fprintf(fp,'\n%s ',fullpath);
            fprintf(fp,'%f ',P);
           
        end
    end
    grid on
    legend
    title(path)
    fclose(fp);
     
function P=Rough(P0)
    sprintf('mean of P0 %f\n', mean(mean(abs(P0))))
    %P0=P0/4;
    
    % y average
    B=ones(32,1)/32;
    P1=conv2(P0,B,'valid');
    if max(sum(P0(1:32,:))/32~=P1(1,:))~=0
        error 'xxxx'
    end
    
    %plot(max(P1,[],1))
    % abs
    P2=abs(P1);
    
    % sub the mean
    mean_P2=mean(mean(P2))
    P3=P2-mean(mean(P2));
    
    P4=min(P2, P3*1.5);
    %P4(P4<0)=0;
    
    % y max, 1d
    P5=max(P4,[],1);
    
    % x average
    partsz=(5000/27);
    B2=ones(1,int32(partsz))/partsz;
    P6=conv2(P5,B2,'valid');
    
    P7=P6(1:partsz:length(P6));
    P=P7;
    