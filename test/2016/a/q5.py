import sys
DEBUG = True
output = sys.argv[1]
for i in range(-1, -len(sys.argv[1]) - 1, -1):
    print output
    output = output + sys.argv[1][i]

print output
