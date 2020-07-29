def fact(x):
    if x == 1:
        return 1
    else:
        return x * fact(x - 1)


print(fact(10))


def sum_arr(arr):
    if not arr:
        return 0
    return arr[0] + sum(arr[1:])


print(sum_arr([1, 2, 3, 4, 6, 7]))


def quantity(arr):
    if not arr:
        return 0
    return 1 + quantity(arr[1:])


print(quantity([1, 2, 5, 7, 8, 9]))


def max_arr(arr):
    if len(arr) == 2:
        return arr[0] if arr[0] > arr[1] else arr[1]
    sub_max = max(arr[1:])
    return arr[0] if arr[0] > sub_max else sub_max


print(max_arr([2, 7, 4, 9, 10]))


def quick_sort(array):
    if len(array) < 2:
        return array
    else:
        pivot = array[0]
        less = [i for i in array[1:] if i <= pivot]
        greater = [i for i in array[1:] if i > pivot]
        return quick_sort(less) + [pivot] + quick_sort(greater)


print(quick_sort([10, 5, 2, 3]))
