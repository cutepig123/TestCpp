function cs=xmlChildrenByName(p,name)
    cs={};
    k=1;
    for i=1:length(p.Children)
        if strcmp(p.Children{i}.Name,name)
            cs{k}=p.Children{i};
            k=k+1;
        end
    end
    