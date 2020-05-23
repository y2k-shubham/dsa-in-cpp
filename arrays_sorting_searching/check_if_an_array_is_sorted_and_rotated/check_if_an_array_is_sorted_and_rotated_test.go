package check_if_an_array_is_sorted_and_rotated

import (
	"errors"
	"fmt"
	"math"
	"strings"
	"testing"
)

func TestFindMinEleIndex(t *testing.T) {
	argsIn := [][]int{
		// unsorted
		[]int{2, 1},
		[]int{3, 4, 5, 1, 2},
		[]int{7, 7, 8, 2, 4, 6, 6, 7},
		// sorted
		[]int{3, 4, 5},
		[]int{1, 1, 4, 5, 9},
		[]int{2, 2, 4, 5},
		// reverse-sorted
		[]int{5, 4, 3},
		[]int{9, 5, 4, 1, 1},
		[]int{5, 4, 2, 2},
		// equal
		[]int{1, 1, 1},
		[]int{2, 2},
		// single / empty
		[]int{5},
		[]int{1},
		[]int{},
	}
	minEleIndOutExpected := []int{
		// unsorted
		1,
		3,
		3,
		// sorted
		0,
		0,
		0,
		// reverse-sorted
		2,
		3,
		2,
		// equal
		0,
		0,
		// single / empty
		0,
		0,
		math.MinInt32,
	}
	allCasesPassed := true
	var stringBuilder strings.Builder
	stringBuilder.WriteString("\n")

	for idx, arg := range argsIn {
		minEleIndComputed := FindMinEleIndex(arg)
		minEleIndExpected := minEleIndOutExpected[idx]

		if minEleIndExpected != minEleIndComputed {
			allCasesPassed = false
			stringBuilder.WriteString("[failed]\t")
		} else {
			stringBuilder.WriteString("[passed]\t")
		}

		stringBuilder.WriteString(fmt.Sprintf("Idx=%d\tinput: array=%v\t", idx, arg))
		stringBuilder.WriteString(fmt.Sprintf("expected=%d\t", minEleIndExpected))
		stringBuilder.WriteString(fmt.Sprintf("computed=%d\t", minEleIndComputed))
		stringBuilder.WriteString("\n")
	}

	if allCasesPassed {
		stringBuilder.WriteString("TestFindMinEleIndex: All  cases passed\n")
	} else {
		stringBuilder.WriteString("TestFindMinEleIndex: Some cases failed\n")
	}

	t.Logf(stringBuilder.String())
	if !allCasesPassed {
		t.Fail()
	}
}

func TestCheckAscendingOrder(t *testing.T) {
	arrIn := [][]int{
		// sorted-range
		[]int{8, 1, 3, 7, 4, 2, 9},
		[]int{8, 1, 3, 7, 4, 2, 9},
		[]int{8, 1, 3, 7, 4, 2, 9},
		// unsorted-range
		[]int{8, 1, 3, 7, 4, 2, 9},
		[]int{8, 1, 3, 7, 4, 2, 9},
		[]int{8, 1, 3, 7, 4, 2, 9},
		// zero-range
		[]int{8, 1, 3, 7, 4, 2, 9},
		[]int{8, 1, 3, 7, 4, 2, 9},
		// empty-array
		[]int{},
	}
	indRangeIn := [][]int{
		// sorted range
		[]int{1, 2},
		[]int{1, 3},
		[]int{5, 6},
		// unsorted range
		[]int{0, 1},
		[]int{0, 4},
		[]int{1, 4},
		// zero-range
		[]int{1, 1},
		[]int{5, 5},
		// empty-array
		[]int{0, 0},
	}
	isAscendingOutExpected := []bool{
		//sorted range
		true,
		true,
		true,
		// unsorted range
		false,
		false,
		false,
		// zero range
		true,
		true,
		// empty-array
		true,
	}

	allCasesPassed := true
	var stringBuilder strings.Builder
	stringBuilder.WriteString("\n")

	for idx, arr := range arrIn {
		isAscendingComputed, errComputed := CheckAscendingOrder(arr, indRangeIn[idx][0], indRangeIn[idx][1], true)
		isAscendingExpected := isAscendingOutExpected[idx]

		if (isAscendingExpected != isAscendingComputed) || (nil != errComputed) {
			allCasesPassed = false
			stringBuilder.WriteString("[failed]\t")
		} else {
			stringBuilder.WriteString("[passed]\t")
		}

		stringBuilder.WriteString(fmt.Sprintf("Idx=%d\tinput: array=%v\tindRangeIn = (%d, %d)\t", idx, arr, indRangeIn[idx][0], indRangeIn[idx][1]))
		stringBuilder.WriteString("\n")

		stringBuilder.WriteString("\t\t")
		stringBuilder.WriteString(fmt.Sprintf("expected: isAscending=%t, err=nil\t", isAscendingExpected))
		stringBuilder.WriteString(fmt.Sprintf("computed: isAscending=%t, err=%s\t", isAscendingComputed, errComputed))
		stringBuilder.WriteString("\n")
	}

	if allCasesPassed {
		stringBuilder.WriteString("TestCheckAscendingOrder: All  cases passed\n")
	} else {
		stringBuilder.WriteString("TestCheckAscendingOrder: Some cases failed\n")
	}

	t.Logf(stringBuilder.String())
	if !allCasesPassed {
		t.Fail()
	}
}

func TestCheckAscendingOrderError(t *testing.T) {
	arrIn := [][]int{
		// lo > hi
		[]int{1, 2, 3},
		// hi > len(arr)
		[]int{1, 2, 3},
		[]int{},
	}
	indRangeIn := [][]int{
		// lo > hi
		[]int{2, 1},
		// hi > len(arr)
		[]int{2, 3},
		[]int{3, 4},
	}
	trueOnErrorIn := []bool{
		// lo > hi
		true,
		// hi > len(arr)
		false,
		true,
	}

	isAscendingOutExpected := []bool{
		// lo > hi
		true,
		// hi > len(arr)
		false,
		true,
	}
	errorOutExpected := []error{
		// lo > hi
		errors.New(fmt.Sprintf("Invalid range lo=2 < hi=1; lo can't be greater than hi")),
		// hi > len(arr)
		errors.New(fmt.Sprintf("Invalid range lo=2, hi=3 for arr[] of len=3")),
		nil,
	}

	allCasesPassed := true
	var stringBuilder strings.Builder
	stringBuilder.WriteString("\n")

	for idx, arr := range arrIn {
		isAscendingComputed, errComputed := CheckAscendingOrder(arr, indRangeIn[idx][0], indRangeIn[idx][1], trueOnErrorIn[idx])
		isAscendingExpected := isAscendingOutExpected[idx]
		errExpected := errorOutExpected[idx]
		testFailed := false

		if errExpected == nil && errComputed == nil {
			// no worries
		} else if errExpected != nil && errComputed != nil {
			// errors should match
			if errExpected.Error() != errComputed.Error() {
				testFailed = true
			}
		} else {
			// guaranteed failure
			testFailed = true
		}

		if isAscendingExpected != isAscendingComputed {
			// guaranteed failure
			testFailed = true
		}

		if testFailed {
			allCasesPassed = false
			stringBuilder.WriteString("[failed]\t")
		} else {
			stringBuilder.WriteString("[passed]\t")
		}

		stringBuilder.WriteString(fmt.Sprintf("Idx=%d\tinput: array=%v\tindRangeIn = (%d, %d)\t", idx, arr, indRangeIn[idx][0], indRangeIn[idx][1]))
		stringBuilder.WriteString("\n")

		stringBuilder.WriteString("\t\t")
		stringBuilder.WriteString(fmt.Sprintf("expected: isAscending=%t, err=%s\t", isAscendingExpected, errExpected))
		stringBuilder.WriteString(fmt.Sprintf("computed: isAscending=%t, err=%s\t", isAscendingComputed, errComputed))
		stringBuilder.WriteString("\n")
	}

	if allCasesPassed {
		stringBuilder.WriteString("TestCheckAscendingOrder: All  cases passed\n")
	} else {
		stringBuilder.WriteString("TestCheckAscendingOrder: Some cases failed\n")
	}

	t.Logf(stringBuilder.String())
	if !allCasesPassed {
		t.Fail()
	}
}

func TestIsSortedRotated(t *testing.T) {
	argsIn := [][]int{
		// valid
		[]int{2, 1},
		[]int{3, 4, 5, 1, 2},
		[]int{7, 7, 8, 2, 4, 6, 6, 7},
		// invalid
		[]int{1, 2, 3},
		[]int{5, 4, 3},
		[]int{1, 1, 5, 4, 9},
		[]int{2, 4, 2, 5},
	}
	isSortedRotatedOutExpected := []bool{
		// valid
		true,
		true,
		true,
		// invalid
		false,
		false,
		false,
		false,
	}
	pivotIndexOutExpected := []int{
		// valid
		1,
		3,
		3,
		// invalid
		-1,
		-1,
		-1,
		-1,
	}

	allCasesPassed := true
	var stringBuilder strings.Builder
	stringBuilder.WriteString("\n")

	for idx, arg := range argsIn {
		isSortedRotatedComputed, pivotIndexComputed := IsSortedRotated(arg)
		isSortedRotatedExpected := isSortedRotatedOutExpected[idx]
		pivotIndexExpected := pivotIndexOutExpected[idx]
		testFailed := false

		if isSortedRotatedExpected != isSortedRotatedComputed {
			testFailed = true
		} else if pivotIndexExpected != pivotIndexComputed {
			testFailed = true
		}

		if testFailed {
			allCasesPassed = false
			stringBuilder.WriteString("[failed]\t")
		} else {
			stringBuilder.WriteString("[passed]\t")
		}

		stringBuilder.WriteString(fmt.Sprintf("Idx=%d\tinput: array=%v\t", idx, arg))
		stringBuilder.WriteString("\n")

		stringBuilder.WriteString("\t\t")
		stringBuilder.WriteString(fmt.Sprintf("expected: isSortedRotated=%t, pivotyIndex=%d\t", isSortedRotatedExpected, pivotIndexExpected))
		stringBuilder.WriteString(fmt.Sprintf("computed: isSortedRotated=%t, pivotyIndex=%d\t", isSortedRotatedComputed, pivotIndexComputed))
		stringBuilder.WriteString("\n")
	}

	if allCasesPassed {
		stringBuilder.WriteString("TestCheckAscendingOrder: All  cases passed\n")
	} else {
		stringBuilder.WriteString("TestCheckAscendingOrder: Some cases failed\n")
	}

	t.Logf(stringBuilder.String())
	if !allCasesPassed {
		t.Fail()
	}
}
