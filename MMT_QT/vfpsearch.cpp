#include "VisioForge_VFP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vfpsearch.h"

#include "VisioForge_VFP_Types.h"

#ifndef INT_MAX
    #include <limits.h>
#endif

int vfpsearch(const char* srcSig, const char* destSig, int *timeSeconds)
{
//	if(argc!=3)
//    {
//		printf("\nUsage: search SIG1 SIG2\n\n");
//		printf("Finds SIG1 in SIG2\n\n");
//		return 1;
//	}

    const char* pPath1 = srcSig; //argv[1];
    const char* pPath2 = destSig; //argv[2];

	long n1 = 0;
	long n2 = 0;
    *timeSeconds = 0;

	FILE* pFile1 = fopen(pPath1, "rb");
	if(pFile1)
	{
		fseek(pFile1, 0, SEEK_END);
		n1 = ftell(pFile1);
		fclose(pFile1);
	}
        else
        {
		printf("can't open %s\n", pPath1);
        }

	FILE* pFile2 = fopen(pPath2, "rb");
	if(pFile2)
	{
		fseek(pFile2, 0, SEEK_END);
		n2 = ftell(pFile2);
		fclose(pFile2);
	}
	else
	{
		printf("can't open %s\n", pPath2);
	}

    if(!n1) return -1;
    if(!n2) return -1;

	char* pData1 = new char[n1];
	char* pData2 = new char[n2];

	pFile1 = fopen(pPath1, "rb");
	if(pFile1)
	{
		int r=0;
		for(r=0; r<n1; r+=fread(pData1+r, 1, n1-r, pFile1)){}
		fclose(pFile1);
	}

	pFile2 = fopen(pPath2, "rb");
	if(pFile2)
	{
		int r=0;
		for(r=0; r<n2; r+=fread(pData2+r, 1, n2-r, pFile2)){}
		fclose(pFile2);
	}

    VFS_TMP* vfp = new VFS_TMP();
    VFPSearch_Init(3, vfp);
    double diff = 0.0;

    int maxDiff = 500;

    int pos = VFPSearch_Search(pData1, n1, 0, pData2, n2, 0, &diff, maxDiff, vfp);

    VFPSearch_Clear(vfp);


    if(pos == INT_MAX)
    {
        //printf("match not found\n");
        return -1;
    }
	else
	{
        //int minutes = pos/60;
        //int seconds = pos%60;
        //printf("match was found at %.2d:%.2d\n", minutes, seconds);

        *timeSeconds = pos;
	}    

	return 0;
}

