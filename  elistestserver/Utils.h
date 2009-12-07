#ifndef UTILS_H
#define UTILS_H
#pragma once

#include <math.h>

class CUtils
{
public:
	CUtils(void) {}
	~CUtils(void) {}

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
};

#endif