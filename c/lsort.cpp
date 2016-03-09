#include <cstdio>
#include <cstdlib>
#include <ctime>
int a[100], t[100];

void init() {
	srand(time(NULL));
	printf("Before sort:\n");
	for (int i = 0; i < 100; i++) {
		a[i] = rand();
		if (a[i] > 1000) a[i] %= 1000;
		printf("%d ", a[i]);
	}
	printf("\n");
}

void quicksort(int* arr, int left, int right) { // quick sort
	if (left < right) {
		int i = left, j = right, x = arr[i];
		while (i < j) {
			while (i < j && arr[j] >= x) j--;
			if (i < j) arr[i++] = arr[j];
			while (i < j && arr[i] < x) i++;
			if (i < j) arr[j--] = arr[i];
		}
		arr[i] = x;
		quicksort(arr, left, i-1);
		quicksort(arr, i+1, right);
	}
}

void mergesort(int* arr, int x, int y, int* T) { // merge sort
	if (y-x > 1) {
		int m = x + (y-x)/2;
		int p = x, q = m, i = x;
		mergesort(a, x, m, T);
		mergesort(a, m, y, T);
		while(p < m || q < y) {
			if (q >= y || (p < m && arr[p] <= arr[q]))
				T[i++] = arr[p++];
			else
				T[i++] = arr[q++];
		}
		for (i = x; i < y; i++) arr[i] = T[i];
	}
}

void pr() {
	printf("After sort:\n");
	for (int i = 0; i < 100; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main() {
	init();
	// quicksort(a, 0, 99);
	mergesort(a, 0, 100, t);
	pr();
	return 0;
}
