%p = xmlread('\\vis_mc_solar\c\wineagle\log\AutoRpt\WISI0392_nonshiny\result.xml');

function tXml(x, level)
    if ~isfield(x,'Children') | level>3
        return
    end
    
    sprintf('Name %s Children %d level %d', x.Name, length(x.Children), level)
    x
    
    for i=1:length(x.Children)
        tXml(x.Children{i},level+1);
    end
    
    if isfield(x,'Attributes')
         for i=1:length(x.Attributes)
             tXml(x.Attributes{i},level+1);
         end
    end