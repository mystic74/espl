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

def dict_from_error_code_freq():
    return_dict = dict()
    in_list = get_error_codes()().strip('\t').split()    
    for curr, nex in list(zip(in_list, in_list[1:]))[::2]:
        return_dict[nex] = float(curr)
    return return_dict

def parse_student_grade(index_string):
    # Parse the string to a dictionary for each error
    if (index_string.strip() is "" ):
        return None
    error_dict = dict()
    for i in index_string.split("|"):
        curr_err = i.strip().split(":")
        error_dict[curr_err[0]] = float(curr_err[1])
    return error_dict

def parse_all_stduents_grades():
    grfile = open("lab10_grades.csv")
    grade_lines = grfile.readlines()
    student_dict = dict()
    for line in grade_lines:
        curr_splited_line = line.split('\t')
        student_dict[curr_splited_line[0]] = parse_student_grade(curr_splited_line[1])
    return student_dict

def get_error_codes_dict():
    error_file = open("error_codes.txt")
    error_val_dict = dict()
    for line in error_file.readlines():
        line = line.strip().split()
        error_val_dict[line[0]] = float(line[1])
    return error_val_dict

def calc_removal(error_dict, value_dict = None):
    if value_dict is None:
        value_dict = get_error_codes_dict()
    curr_grade = 100
    if error_dict is None:
        return curr_grade
    
    for k in error_dict:
        if (VERBOSE >= 2):
            print("Removing {}:{}*{} from current grade {}".format(k, value_dict[k],error_dict[k], curr_grade))
        curr_grade = curr_grade - (error_dict[k] * value_dict[k])
    return curr_grade

def print_student_grade(value_dict = None):
    student_dict = parse_all_stduents_grades()
    student_grade = {}
    for name in student_dict:
        student_grade[name] = calc_removal(student_dict[name], value_dict)
        if (VERBOSE >= 1):
            print("Grade for {} is {}".format(name, student_grade[name]))    
    return student_grade

def plot_histogram(grades_arr):
    import numpy as np
    import matplotlib.mlab as mlab
    import matplotlib.pyplot as plt

    num_bins = 5
    n, bins, patches = plt.hist(grades_arr, num_bins, facecolor='blue', alpha=0.5)
    plt.show()

def high_grade_info():
    import operator
    value_dict = get_error_codes_dict()
    freq_dict = dict_from_error_code_freq()
    return max(freq_dict.items(), key=operator.itemgetter(1))[0]

def print_high_info():
    print(high_grade_info())

def add_factor():
    value_dict = get_error_codes_dict()
    max_error = high_grade_info()
    value_dict[max_error] = 0
    print_student_grade(value_dict)
