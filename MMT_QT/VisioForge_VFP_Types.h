#pragma once

struct VFS_TMP
{
    static const int size = (sizeof(int)*(4+4+4+4))+(sizeof(int)*(4+4+4));

    char* p;
	
	int* r;
	int* g;
	int* b;
	int* n;

    int* ra;
    int* ga;
    int* ba;
     
    int count;

    double dTime;
};

struct VFC_TMP
{
    int* p1;

    int* r1;
    int* g1;
    int* b1;

    int* r2;
    int* g2;
    int* b2;

    int* n;
     
    int count;

    double dTime;

    unsigned long long r_avg[5];
    unsigned long long g_avg[5];
    unsigned long long b_avg[5];

    unsigned long long r1_avg[64];
    unsigned long long g1_avg[64];
    unsigned long long b1_avg[64];

    unsigned long long r2_avg[64];
    unsigned long long g2_avg[64];
    unsigned long long b2_avg[64];

    unsigned long long x_avg[64];
    unsigned long long y_avg[64];
};
