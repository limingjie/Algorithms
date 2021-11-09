package main

// Multiply large positive integers a and b
func Multiply(a, b string) string {
	// Calculate length and prepare slices
	lenA := len(a)
	lenB := len(b)
	lenP := lenA + lenB
	arrA := make([]int64, lenA)
	arrB := make([]int64, lenB)
	prod := make([]int64, lenA+lenB)

	// Split x into int array
	for i, c := range a {
		arrA[lenA-i-1] = int64(c - '0')
	}

	// Split y into int array
	for i, c := range b {
		arrB[lenB-i-1] = int64(c - '0')
	}

	// Multiply without processing carry
	for i, a := range arrA {
		for j, b := range arrB {
			prod[i+j] += a * b
		}
	}

	// Process carry
	for i, p := range prod {
		if p > 9 {
			prod[i+1] += p / 10
			prod[i] = p % 10
		}
	}

	// Remove leading zeros
	for i := lenP - 1; i >= 1; i-- {
		if prod[i] != 0 {
			break
		}
		lenP--
	}

	buf := make([]byte, lenP)
	for i := lenP - 1; i >= 0; i-- {
		buf[lenP-1-i] = byte(prod[i]) + '0'
	}

	return string(buf[:])
}
