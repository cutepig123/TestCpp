if ~exist('fdr') || ~exist('dest')
    'fdr or dest not defined, using default!'
    fdr='\\aaaex\AAAPROJ\Vision\app\User\aeecsyip\MyDoc\Project\SEAS\A08_Data\F30_STJ_1stBatch_20120514\40ea';
    dest='1.txt';
end

files=dir(sprintf('%s\\*.xml',fdr));
fp=fopen(dest,'w');
TITLES={};
for i=1:length(files)
    if files(i).isdir
        continue
    end
    
    cufile=files(i).name;
    fprintf(fp,'\nFile\t%s\n',files(i).name);
    file=sprintf('%s\\%s',fdr,files(i).name);
    
    p=xmlread(file);
    psubsetinfo=xmlChildrenByName(p,'SUBTESTINFO');
    for l=1:length(psubsetinfo)
        SUBTEST=xmlChildrenByName(psubsetinfo{l},'SUBTEST');
        for m=1:length(SUBTEST)
            DESCRIPTION=xmlChildrenByName(SUBTEST{m},'DESCRIPTION');
            FINDING=xmlChildrenByName(SUBTEST{m},'FINDING');
            if length(DESCRIPTION)~=1
                error 'Invalid data!'
            end
            
            V='';
            if length(FINDING)==1
                V=FINDING{1}.Children{1}.Value;
            end
            
            T=DESCRIPTION{1}.Children{1}.Value;
            fprintf(fp,'%s\t%s\n',T,V);
                   
        end
    end
    
end

fclose(fp);