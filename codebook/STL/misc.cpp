// return iterator, find first >= val
lower_bound(vector.begin(), vector.end(), val)

// return iterator, find find > val
upper_bound(vector.begin(), vector.end(), val)

// array
min_element(arr, arr + n); // 0-based
// vector, return iterator
min_element(vector.begin(), vector.end())

// array
max_element(arr, arr + n); // 0-based
// vector, return iterator
max_element(vector.begin(), vector.end())

// fix nth element at nth index
nth_element(vector.begin(), vector.begin() + 4, vector.end()) // fix 5th element at vector[4]

// array, 0-based
do {

} while(next_permutation(arr, arr + n));
// vector
do {

} while(next_permutation(vector.begin(), vector.end()))
