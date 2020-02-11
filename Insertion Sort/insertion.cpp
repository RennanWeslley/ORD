#include <iostream>
#include <sstream>

void printArr(int *, int);
void insertion_sort(int *, int);

int main(int argc, char *argv[]) {
	    /* CHAR TO INT */
	int size = argc - 1;
	int arr[size];
	
	std::stringstream *d;	

	for(int i = 1; i < argc; i++) {
		d = new std::stringstream(argv[i]);
		*d >> arr[i-1];
	}
	/* END OF CHAR TO INT */
	
	printArr(arr, size);

	std::cout << "\nApplying Insertion Sort...\n" << std::endl;

	insertion_sort(arr, size);

	std::cout << "Done" << std::endl;

	printArr(arr, size);	

	return 0;
}

void printArr(int *arr, int size) {
    std::cout << "\nArray: {";

    for(int i = 0 ; i < size; i++)
        if((i+1) != size)
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i] << "}" << std::endl;
}

void insertion_sort(int *arr, int size) {
	for(int i = 1; i < size; i++) {
		for(int j = i; ;) {
			if(arr[j] < arr[j-1])
				std::swap(arr[j], arr[j-1]);

			j--;

			if(!j || arr[j] > arr[j-1])
				break;
		}
	}
}

