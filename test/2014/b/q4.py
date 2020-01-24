#!/usr/bin/python3

DEBUG = True

def foo(arg):
    if DEBUG:
        print("For {} (with arg[::-1] {}) its {}".format(arg,arg[::-1], arg==arg[::-1]))
    return arg==arg[::-1]

print(foo(['A', 'V', 'I', 'V', 'A']) or foo(['A','B', 'C','D']) and foo([1,2,3,1]))
