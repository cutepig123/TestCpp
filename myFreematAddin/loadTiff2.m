function [buf2,sts]=loadTiff2(f)
	[buf2,sts]=loadTiff(f);
    if sts~=0
        error sprintf('Error, invalid tiff file %s',f);
    end
    