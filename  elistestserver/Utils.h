#ifndef UTILS_H
#define UTILS_H
#pragma once

#include <math.h>

class CUtils
{
public:
	CUtils(void) {}
	~CUtils(void) {}
/*
	static int maximum(int *arr, int len) {
		int max = arr[0];
		for(int i = 0; i < len; ++i){
			if(max < arr[i]){
				max = arr[i]; 
			}
		}
		return max;
	 }
	
	static BOOL isPrime(int x){
		if(x == 2)  return TRUE;
		if(x % 2 == 0) return FALSE;
		for(int i = 3; i <= (int)sqrt((float)x); i += 2){
			if(x % i == 0) return FALSE; 
		}
		return TRUE;
	 }

	static int lcm(int *a, int len) {
		int lcm = 1;
		int max =  maximum(a, len);
		int i, j, temp;
		for(i = 2; i <= max; ++i) {
			if(isPrime(i)) {
				temp = 1;
				for(j = 0; j < len; ++j) {
					while(a[j] % temp == 0) {
						temp *= i;
					}
				}
				temp /= i;
				lcm *= temp;
			}
		}
		return lcm;
	}
*/
	/* 数组的最小公倍数;*/  
	static int GetCommonMultiple(int *nSampleRate, int nSampleNum)   //lhx 08-1-18
	{
		int i = 0;
		int nFirst = nSampleRate[0];
		for (i = 0 ; i < nSampleNum ; i++ )
		{
			
			nFirst = CommonMultiple(nSampleRate[i],nFirst );
		}
		return nFirst; 
	}

	/* 数组的最大公约数 */
	static int GetCommonDivisor(int *nSampleRate, int nSampleNum) //lhx 08-1-18
	{
		int i = 0;
		int nFirst = nSampleRate[0];
		for ( i = 0 ; i < nSampleNum ; i++ )
		{
			
			nFirst = CommonDivisor(nSampleRate[i],nFirst );
		}
		return nFirst; 

	}

	/* 最小公倍数;*/  
	static int CommonMultiple(int m, int n) //lhx 08-1-18
	{
		int   temp=m*n/CommonDivisor(m,n);  
		return   temp;  

	}

	/* 最大公约 */
	static int CommonDivisor(int m, int n)//lhx 08-1-18
	{
		if(n==0)  
			return  m;  
		else  
			CommonDivisor(n,m%n);  

	}

};

#endif