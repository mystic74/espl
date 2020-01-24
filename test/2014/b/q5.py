#!/usr/bin/python3

DEBUG = True

my_list = []
data = ['B', 'A','N', 'A', 'N', 'A']

[my_list.append(pair) for pair in enumerate(data) if data[-1 * (pair[0] + 1)] == 'A']
for my_tuple in my_list:
    data[my_tuple[0]] = '*'

print("".join(data))