# Task 0b
from plumbum.cmd import grep, sed, awk,wc, uniq, sort

VERBOSE = 2

def get_student_names():
    return awk["-F", r"\t",  '{print $1}' , "lab10_grades.csv"]

def get_number_of_students():
    return (get_student_names() | wc["-l"])

def get_error_codes():
    chain = (awk["-F", r"\t",  '{print $2}' , "lab10_grades.csv"] |
             sed["-r", r'/^\s*$/d']  |
             sed[r's/|/\n/g'] |
             awk["-F", ":", '{print $1}'] |
             sort |
             uniq["-c"])
    return chain 

def task0b():
    print("The students names are\n {}".format(get_student_names()))
    print("The number of studet is : {}".format(get_number_of_students()))
    print("The error codes are:\n{}", get_error_codes())
