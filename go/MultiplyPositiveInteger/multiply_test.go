package main

import (
	"testing"
)

// TestMultiply - Unit Test
func TestMultiply(t *testing.T) {
	cases := []struct {
		a       string
		b       string
		product string
	}{
		{"999", "999", "998001"},
		{"123456789", "987654321", "121932631112635269"},
		{"999999999", "0", "0"},
		{"10000", "10000", "100000000"},
	}

	for _, c := range cases {
		product := multiply.Multiply(c.a, c.b)
		if product != c.product {
			t.Errorf("Failed! Calculate %s x %s = %s => Failed, expecting %s.\n", c.a, c.b, product, c.product)
		} else {
			t.Logf("Calculate %s x %s = %s => Passed!\n", c.a, c.b, product)
		}
	}
}

func BenchmarkMultiply(b *testing.B) {
	for i := 0; i < b.N; i++ {
		multiply.Multiply(
			"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
			"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
		)
	}
}
