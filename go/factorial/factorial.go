package main

import (
	"fmt"
	"math/big"
	"os"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Usage:\n\tfactorial number")
		return
	}

	var f = new(big.Int)
	if _, ok := f.SetString(os.Args[1], 10); !ok {
		fmt.Printf("Warning: \"%s\" is not a number.\n", os.Args[1])
		return
	}

	if !f.IsInt64() {
		fmt.Printf("Warning: \"%s\" exceeds the 64-bit integer limit.\n", os.Args[1])
		return
	}

	if f.Int64() >= 1 {
		fmt.Println(f.MulRange(1, f.Int64()))
	} else {
		fmt.Println("0")
	}
}
