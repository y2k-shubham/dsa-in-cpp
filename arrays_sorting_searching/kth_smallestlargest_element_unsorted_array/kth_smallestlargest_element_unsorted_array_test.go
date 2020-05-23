package kth_smallestlargest_element_unsorted_array

import (
	"github.com/stretchr/testify/assert"
	"math"
	"testing"
)

func TestSwap(t *testing.T) {
	type Input struct {
		arr []int
		i   int
		j   int
	}
	argsIn := []Input{
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, i: 0, j: 0},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, i: 0, j: 1},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, i: 0, j: 6},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, i: 1, j: 5},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, i: 1, j: 6},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, i: 3, j: 4},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, i: 6, j: 6},
		{arr: []int{8}, i: 0, j: 0},
	}
	argsOutExpected := [][]int{
		[]int{8, 1, 3, 7, 4, 2, 9},
		[]int{1, 8, 3, 7, 4, 2, 9},
		[]int{9, 1, 3, 7, 4, 2, 8},
		[]int{8, 2, 3, 7, 4, 1, 9},
		[]int{8, 9, 3, 7, 4, 2, 1},
		[]int{8, 1, 3, 4, 7, 2, 9},
		[]int{8, 1, 3, 7, 4, 2, 9},
		[]int{8},
	}
	for idx, arg := range argsIn {
		argOutExpected := argsOutExpected[idx]

		Swap(arg.arr, arg.i, arg.j)
		argOutComputed := arg.arr

		assert.Equal(t, argOutExpected, argOutComputed, "Output at idx=%d mismatches\narr=%v\ni=%d\tj=%d", idx, arg.arr, arg.i, arg.j)
	}
}

func TestPartition(t *testing.T) {
	type Input struct {
		arr []int
		lo  int
		hi  int
	}
	argsIn := []Input{
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 0, hi: 0},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 0, hi: 1},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 0, hi: 3},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 2, hi: 3},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 4, hi: 6},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 4, hi: 4},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 5, hi: 6},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, lo: 6, hi: 6},
		{arr: []int{8}, lo: 0, hi: 0},
	}
	type Output struct {
		arr      []int
		pivotInd int
	}
	argsOutExpected := []Output{
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, pivotInd: 0},
		{arr: []int{1, 8, 3, 7, 4, 2, 9}, pivotInd: 0},
		{arr: []int{1, 3, 7, 8, 4, 2, 9}, pivotInd: 2},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, pivotInd: 3},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, pivotInd: 6},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, pivotInd: 4},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, pivotInd: 6},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, pivotInd: 6},
		{arr: []int{8}, pivotInd: 0},
	}
	for idx, arg := range argsIn {
		arrOutExpected := argsOutExpected[idx].arr
		pivotIndOutExpected := argsOutExpected[idx].pivotInd

		pivotIndOutComputed := Partition(arg.arr, arg.lo, arg.hi)
		arrOutComputed := arg.arr

		assert.Equal(t, arrOutExpected, arrOutComputed, "Array at idx=%d mismatches\narr=%v\ni=%d\tj=%d", idx, arg.arr, arg.lo, arg.hi)
		assert.Equal(t, pivotIndOutExpected, pivotIndOutComputed, "Pivot at idx=%d mismatches\narr=%v\ni=%d\tj=%d", idx, arg.arr, arg.lo, arg.hi)
	}
}

func TestQuickSelect(t *testing.T) {
	type Input struct {
		arr []int
		k   int
	}
	argsIn := []Input{
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 1},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 2},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 3},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 4},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 5},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 6},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 7},
		{arr: []int{8}, k: 1},
	}
	argsOutExpected := []int{
		1,
		2,
		3,
		4,
		7,
		8,
		9,
		8,
	}
	for idx, arg := range argsIn {
		kthSmallestOutExpected := argsOutExpected[idx]
		kthSmallestOutComputed, errOutComputed := QuickSelect(arg.k, arg.arr, 0, (len(arg.arr) - 1))

		assert.Equal(t, kthSmallestOutExpected, kthSmallestOutComputed, "Outputs at idx=%d mismatch\narr=%v\tk=%d", idx, arg.arr, arg.k)
		assert.NoError(t, errOutComputed, "Error at idx=%d is not nil", idx)
	}
}

func TestQuickSelectError(t *testing.T) {
	type Input struct {
		arr []int
		k   int
	}
	argsIn := []Input{
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: -1},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 0},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 8},
		{arr: []int{8, 1, 3, 7, 4, 2, 9}, k: 9},
	}
	errMsgOutExpected := []string{
		"k-1=-2 can't be less than lo=0",
		"k-1=-1 can't be less than lo=0",
		"k-1=7 can't exceed hi=6",
		"k-1=8 can't exceed hi=6",
	}
	for idx, arg := range argsIn {
		kthSmallestOutComputed, errOutComputed := QuickSelect(arg.k, arg.arr, 0, (len(arg.arr) - 1))

		assert.Equal(t, math.MinInt32, kthSmallestOutComputed, "Outputs at idx=%d mismatch\narr=%v\tk=%d", idx, arg.arr, arg.k)
		assert.EqualError(t, errOutComputed, errMsgOutExpected[idx], "Errors at idx=%d mismatch\narr=%v\tk=%d", idx, arg.arr, arg.k)
	}
}
