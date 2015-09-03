#include <file.h>
#include "inc.h"
#include <boost/regex.hpp>
#include <boost/unordered_map.hpp> 

#define		LINE_MAX_LENGTH				(256)

IMG_WORD	FILE_RmComment(FILE_CFG_FORMAT	const	*pstCfgFormat,
						   IMG_UBYTE				*pubLine)
{
	IMG_UBYTE	*pubCharPtr;

	/* Search for the comment marker */
	pubCharPtr = (IMG_UBYTE *)strchr((char*)pubLine, (char)pstCfgFormat->ubCommentSym);
	if (pubCharPtr != NULL) *pubCharPtr = '\0';

	return OK;
}

IMG_WORD	FILE_RmSpace(IMG_UBYTE	*pubLine)
{
	IMG_ULWORD	L;

	L = (IMG_ULWORD)strlen((char*)pubLine);

	if (L > 0)
	{
		IMG_UBYTE	*pubStartPtr, *pubEndPtr;

		pubStartPtr = pubLine;
		pubEndPtr = pubLine + L;

		/* Remove leading white space */
		while (isspace(*pubStartPtr))
			++pubStartPtr;

		/* Remove trailing white space */
		while ((pubEndPtr>pubStartPtr) && isspace(*(--pubEndPtr)))
			*pubEndPtr = '\0';

		/* Return the results */
		memmove((char*)pubLine,(char*)pubStartPtr,strlen((char*)pubStartPtr)+1);
	}

	return OK;
}


IMG_WORD	FILE_GetSectionName(FILE_CFG_FORMAT	const	*pstCfgFormat,
								IMG_UBYTE		const	*pubLine,
								IMG_UBYTE				*pubSectionName)
{
	IMG_UBYTE	aubTmpBuf[LINE_MAX_LENGTH];
	IMG_WORD	wLineLen;

	if (pstCfgFormat->wHaveSectionHdr == IMG_FALSE)
		return FILE_MAC_INVALID_SYNTAX;

	/* Check for left and right delimiters */
	if ((pstCfgFormat->ubSectionLSym != '\0') &&
		(*pubLine != pstCfgFormat->ubSectionLSym))
		return FILE_MAC_INVALID_SYNTAX;

	wLineLen = (IMG_WORD)strlen((char*)pubLine);
	if ((pstCfgFormat->ubSectionRSym != '\0') &&
		(*(pubLine+wLineLen-1) != pstCfgFormat->ubSectionRSym))
		return FILE_MAC_INVALID_SYNTAX;

	/* Work in a temp buffer */
	strcpy((char*)aubTmpBuf, (char*)pubLine);

	/* Remove the delimiters */
	if (pstCfgFormat->ubSectionLSym != '\0')
		aubTmpBuf[0] = ' ';
	if (pstCfgFormat->ubSectionRSym != '\0')
		aubTmpBuf[wLineLen-1] = ' ';

	/* Remove the white space */
	FILE_RmSpace(aubTmpBuf);

	/* If blank */
	if (aubTmpBuf[0] == '\0')
		return FILE_MAC_MISSING_FIELD;

	/* Return the results */
	strcpy((char*)pubSectionName, (char*)aubTmpBuf);

	return OK;
}


/*
 *	Set the comment marker of the cfg format
 */
IMG_WORD	FILE_SetCfgCommentSym(IMG_UBYTE			const	ubSymbol,
								  FILE_CFG_FORMAT			*pstCfgFormat)
{
	pstCfgFormat->ubCommentSym = ubSymbol;

	return OK;
}

/*
 *	Set the assignment operator of the cfg format
 */
IMG_WORD	FILE_SetCfgAssignOp(IMG_UBYTE		const	ubSymbol,
								FILE_CFG_FORMAT			*pstCfgFormat)
{
	pstCfgFormat->ubAssignOp = ubSymbol;

	return OK;
}

/*
 *	Set the separator of the cfg format
 */
IMG_WORD	FILE_SetCfgSeparator(	IMG_UBYTE		const	ubSymbol,
									FILE_CFG_FORMAT			*pstCfgFormat)
{
	pstCfgFormat->ubSeparator = ubSymbol;

	return OK;
}

/*
 *	Set the presence of section header of the cfg format
 */
IMG_WORD	FILE_SetCfgHaveSectionHdr(	IMG_WORD		const	wFlag,
										FILE_CFG_FORMAT			*pstCfgFormat)
{
	pstCfgFormat->wHaveSectionHdr = wFlag;

	return OK;
}

/*
 *	Set the section header delimiters of the cfg format
 */
IMG_WORD	FILE_SetCfgSectionHdr(IMG_UBYTE			const	ubLDelimiter,
								  IMG_UBYTE			const	ubRDelimiter,
								  FILE_CFG_FORMAT			*pstCfgFormat)
{
	FILE_SetCfgHaveSectionHdr(IMG_TRUE, pstCfgFormat);

	pstCfgFormat->ubSectionLSym = ubLDelimiter;
	pstCfgFormat->ubSectionRSym = ubRDelimiter;

	return OK;
}

IMG_WORD	FILE_InitCfgFormat(FILE_CFG_FORMAT	*pstCfgFormat)
{
	FILE_SetCfgCommentSym('#', pstCfgFormat);
	FILE_SetCfgAssignOp('=', pstCfgFormat);
	FILE_SetCfgSeparator(',', pstCfgFormat);

	FILE_SetCfgSectionHdr('[', ']', pstCfgFormat);

	return OK;
}

IMG_WORD	FILE_IsMatchSectionHdr(FILE_CFG_FORMAT	const	*pstCfgFormat,
								   IMG_UBYTE		const	*pubLine,
								   IMG_UBYTE		const	*pubSectionName)
{
	IMG_UBYTE	aubWorkLine[LINE_MAX_LENGTH];
	IMG_UBYTE	aubTestName[LINE_MAX_LENGTH];

	/* Remove comment, trailing and leading white space */
	strcpy((char*)aubWorkLine, (char*)pubLine);
	FILE_RmComment(pstCfgFormat, aubWorkLine);
	FILE_RmSpace(aubWorkLine);

	/* Checking */
	// Check if blank line
	if (aubWorkLine[0] == '\0')
		return IMG_FALSE;

	// Check if valid section header
	if (FILE_GetSectionName(pstCfgFormat, aubWorkLine, aubTestName) != OK)
		return IMG_FALSE;

	// Check if the desired section
	if (stricmp((char*)aubTestName, (char*)pubSectionName) == 0)
	{
		return IMG_TRUE;
	}
	else
	{
		return IMG_FALSE;
	}
}

#define	N 1000000
#define	pubSectionName	"SectionName"

char acline[100][100];
int nLine=0;
int aexpectResult[100];

void init()
{
	sprintf(acline[0], "  [ %s ]  ", pubSectionName);
	sprintf(acline[1], "  [ %s ]  ", "WrongSection");
	nLine =2;
	aexpectResult[0]=1;
	aexpectResult[1]=0;
}

void	test_boost()
{
	char str[100];
	sprintf(str, " *\\[ *%s *\\] *", pubSectionName);
	boost::regex	e(str, boost::regex::icase);

	MyTimeMeasure tm("test_boost");

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<nLine; j++)
		{
			bool ret =regex_match((char*)acline[j], e);
			int nRet= ret?1:0;
			assert(nRet==aexpectResult[j]);
		}
	}
}

void test_CFG()
{
	FILE_CFG_FORMAT	stCfgFormat;
	FILE_InitCfgFormat(&stCfgFormat);

	MyTimeMeasure tm("test_CFG");

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<nLine; j++)
		{
			bool ret =FILE_IsMatchSectionHdr( &stCfgFormat, (IMG_UBYTE*)acline[j], (IMG_UBYTE*)pubSectionName);
			int nRet= ret?1:0;
			assert(nRet==aexpectResult[j]);
		}
	}
	
}

void test_cfg_main()
{
	init();
	test_boost();
	test_CFG();
}


IMG_WORD	FILE_SrchFieldname(IMG_UBYTE			const	*pubFieldname,
							   FILE_CFG_DATA_LIST	const	*pstCfgDataList,
							   FILE_CFG_DATA				**ppstData)
{
	FILE_CFG_DATA	*pstSrchData;
	IMG_WORD		i;
	IMG_WORD		wStatus;


	//	Initialization
	*ppstData	= NULL;

	pstSrchData	= (FILE_CFG_DATA*)pstCfgDataList->ptr;
	wStatus		= FILE_MAC_FIELD_NOT_FOUND;

	for (i = 0; i < pstCfgDataList->wNumOfElements; i++)
	{
		if (stricmp((char*)pubFieldname, (char*)pstSrchData->aubFieldName) == 0)
		{
			/* The variable is found */
			*ppstData = pstSrchData;
			wStatus = OK;
			break;
		}
		pstSrchData++;
	}

	return wStatus;
}

IMG_WORD	FILE_InitCfgDataList(FILE_CFG_DATA*	const	ptr,
								 IMG_UWORD		const	uwMaxNumOfElements,
								 FILE_CFG_DATA_LIST		*pstDataList)
{
	pstDataList->ptr = ptr;

	pstDataList->wMaxNumOfElements	= uwMaxNumOfElements;
	pstDataList->wNumOfElements		= 0;

	return OK;
}


#define	NUM_FIELD	6000
#define	NUM_LOOP	6000
char			g_acFields[NUM_FIELD][100];

void init_2()
{
	
}

void test_CFG_SrchField()
{
	MyTimeMeasure tm(__FUNCTION__);
	
	std::vector<FILE_CFG_DATA>       _file_cfgf_sect_mac_astData(NUM_FIELD);	
	FILE_CFG_DATA_LIST	g_file_cfgf_sect_mac_stCfgDataList;

	FILE_InitCfgDataList((&_file_cfgf_sect_mac_astData[0]),	
		NUM_FIELD, &g_file_cfgf_sect_mac_stCfgDataList);
		
	for(int i=0; i<NUM_FIELD;i++)
	{
		sprintf(g_acFields[i], "Object %d", i);
		strcpy((char*)_file_cfgf_sect_mac_astData[i].aubFieldName, g_acFields[i]);
		
	}
	g_file_cfgf_sect_mac_stCfgDataList.wNumOfElements =NUM_FIELD;

	for(int i=0; i<NUM_FIELD; i++)
	{
		FILE_CFG_DATA				*pstData=0;
		IMG_WORD wRet =FILE_SrchFieldname( (IMG_UBYTE*)g_acFields[i], &g_file_cfgf_sect_mac_stCfgDataList,&pstData);
		assert(wRet==OK);
		assert(pstData ==_file_cfgf_sect_mac_astData +i);
	}
}


void test_stdmap_SrchField()
{
	MyTimeMeasure tm(__FUNCTION__);
	
	std::map<std::string, int> g_map;

	for(int i=0; i<NUM_FIELD;i++)
	{
		sprintf(g_acFields[i], "Object %d", i);
		g_map[g_acFields[i] ]=i;
	}
	
	for(int i=0; i<NUM_FIELD; i++)
	{
		auto it =g_map.find(g_acFields[i]);
		assert(it!=g_map.end());
		assert(it->second ==i);
	}
}

void test_boostunordered_map_SrchField()
{
	MyTimeMeasure tm(__FUNCTION__);
	
	boost::unordered_map<std::string, int> g_map;
	
	for(int i=0; i<NUM_FIELD;i++)
	{
		sprintf(g_acFields[i], "Object %d", i);
		g_map[g_acFields[i] ]=i;
	}
	
	for(int i=0; i<NUM_FIELD; i++)
	{
		auto it =g_map.find(g_acFields[i]);
		assert(it!=g_map.end());
		assert(it->second ==i);
	}
}

void test_cfg_main2()
{
	init_2();
	test_stdmap_SrchField();
	test_boostunordered_map_SrchField();
	test_CFG_SrchField();
}
