package algorithms

import "sort"

// ArraySummaryThreshold - Find the threshold for array A
func ArraySummaryThreshold(A []int, T int) (t int) {
	// If the array is empty, return 0.
	length := len(A)
	if length == 0 {
		return 0
	}

	sum := 0
	for _, a := range A {
		sum += a
	}

	// If the summary <= T, return the max element of A.
	if sum <= T {
		t = 0
		for _, a := range A {
			if a > t {
				t = a
			}
		}
		return t
	}

	// Sort the array
	sort.Ints(A)

	sum = 0
	for i, a := range A {
		// Assume t = a and check summary
		if sum+a*(length-i) > T {
			// Calculate t
			t = (T - sum) / (length - i)
			break
		}

		sum += a
	}

	return t
}
