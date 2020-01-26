# Task 0b
from plumbum.cmd import grep, sed, awk,wc, uniq, sort

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

def get_number_of_error_codes():
    return (get_error_codes() | wc["-l"])

def task0b():
    print("The students names are\n {}".format(get_student_names()()))
    print("The number of students is : {}".format(get_number_of_students()()))
    print("The error codes are:\n{}".format(get_error_codes()()))
    print("The number of error codes is : {}".format(get_number_of_error_codes()()))

if __name__ == "__main__":
    # execute only if run as a script
    task0b()