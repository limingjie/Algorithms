package algorithms

import "testing"

var tests = []struct {
	A []int
	T int
	t int
}{
	{[]int{}, 200, 0},                    // Empty array
	{[]int{10, 20, 30, 40, 50}, 200, 50}, // Summary < T, ordered
	{[]int{30, 20, 10, 50, 40}, 200, 50}, // Summary < T, unordered
	{[]int{10, 20, 30, 40, 50}, 150, 50}, // Summary = T, ordered
	{[]int{30, 20, 10, 50, 40}, 150, 50}, // Summary = T, unordered
	{[]int{10, 20, 30, 40, 50}, 0, 0},    // T = 0
	{[]int{10, 20, 30, 40, 50}, 128, 34}, // Summary > T, found max t which make summary = T
	{[]int{10, 20, 30, 40, 50}, 127, 33}, // Summary > T, found max t which make summary < T
	{[]int{10, 20, 30, 40, 50}, 4, 0},    // Summary > T, t = 0
	{[]int{30, 20, 10, 50, 40}, 127, 33}, // Unordered
}

func TestArraySummaryThreshold(t *testing.T) {
	for _, test := range tests {
		out := ArraySummaryThreshold(test.A, test.T)
		if out != test.t {
			t.Errorf("Test: %v\nUnexpected result: %d", test, out)
		}
	}
}
