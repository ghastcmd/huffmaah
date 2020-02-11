from matplotlib import pyplot as plt
import csv

data_folder = 'data/'

without_heap = 'priority_queue_without_heap.txt'
with_heap = 'priority_queue_with_heap.txt'

with open(f'{data_folder + without_heap}', 'r') as heap_file:
    heap_data = csv.reader(heap_file)
    next(heap_data)
    number, comparison = zip(*list(heap_data))

    number = list(map(int, number))
    comparison = list(map(int, comparison))

    plt.scatter(number, comparison, label='With heap')


with open(f'{data_folder + with_heap}', 'r') as queue_file:
    queue_data = csv.reader(queue_file)
    next(queue_data)
    number, comparison = zip(*list(queue_data))

    number = list(map(int, number))
    comparison = list(map(int, comparison))

    plt.scatter(number, comparison, label='Without heap')

plt.ylabel('Number of comparisons')
plt.xlabel('Draft numbers')
plt.title('Priority queue with heap vs. without heap')
plt.show()