// https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/
// Method 4 (QuickSelect)

package kth_smallestlargest_element_unsorted_array

import (
	"errors"
	"fmt"
	"math"
)

func Swap(arr []int, i int, j int) {
	tmp := arr[i]
	arr[i] = arr[j]
	arr[j] = tmp
}

func Partition(arr []int, lo int, hi int) int {
	pivotInd := hi
	pivot := arr[hi]

	j := lo - 1
	for i := lo; i < pivotInd; i++ {
		if arr[i] <= pivot {
			j++
			Swap(arr, j, i)
		}
	}

	j++
	Swap(arr, j, pivotInd)

	return j
}

func QuickSelect(k int, arr []int, lo int, hi int) (int, error) {
	if lo > hi {
		return math.MinInt32, errors.New(fmt.Sprintf("lo=%d can't exceed hi=%d", lo, hi))
	} else if k-1 < lo {
		return math.MinInt32, errors.New(fmt.Sprintf("k-1=%d can't be less than lo=%d", k-1, lo))
	} else if k-1 > hi {
		return math.MinInt32, errors.New(fmt.Sprintf("k-1=%d can't exceed hi=%d", k-1, hi))
	} else {
		pivotInd := Partition(arr, lo, hi)
		if k < pivotInd+1 {
			return QuickSelect(k, arr, lo, pivotInd-1)
		} else if pivotInd+1 == k {
			return arr[pivotInd], nil
		} else {
			return QuickSelect(k, arr, pivotInd+1, hi)
		}
	}
}
