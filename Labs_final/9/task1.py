from task0b import *

VERBOSE = 0

def dict_from_error_code_freq():
    return_dict = dict()
    in_list = get_error_codes()().strip('\t').split()    
    for curr, nex in list(zip(in_list, in_list[1:]))[::2]:
        return_dict[nex] = float(curr)
    return return_dict


def task1a():
	error_freq_dict = dict_from_error_code_freq()
	f = open('errorcodes.stats' , 'w')
	for key in error_freq_dict:
		f.write("{}|{}\n".format(key, error_freq_dict[key]))


def parse_student_grade(index_string):
    # Parse the string to a dictionary for each error
    if (index_string.strip() is "" ):
        return None
    error_dict = dict()
    for i in index_string.split("|"):
        curr_err = i.strip().split(":")
        error_dict[curr_err[0]] = float(curr_err[1])
    return error_dict

"""
Go through all students in csv,
for each one, parse the comments made for each grade,
return the dictionary of student:errors_array
"""
def parse_all_stduents_grades():
    grfile = open("lab10_grades.csv")
    grade_lines = grfile.readlines()
    student_dict = dict()
    for line in grade_lines:
        curr_splited_line = line.split('\t')
        student_dict[curr_splited_line[0]] = parse_student_grade(curr_splited_line[1])
    return student_dict

"""
Codex of the errors, and each value we want to remove for them.
"""
def get_error_codes_dict():
    error_file = open("error_codes.txt")
    error_val_dict = dict()
    for line in error_file.readlines():
        line = line.strip().split()
        error_val_dict[line[0]] = float(line[1])
    return error_val_dict

"""
Actually calculate the removal for a single student.
getting the error dictionary for this student (calculated in parse_student_grade())
the value_dict is for the option to add the "Factor" later on easliy.
"""
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

"""
Gets a dict of students:grade
"""
def get_student_grade(value_dict = None):
    student_dict = parse_all_stduents_grades()
    student_grade = {}
    for name in student_dict:
        student_grade[name] = calc_removal(student_dict[name], value_dict)
        if (VERBOSE >= 1):
            print("Grade for {} is {}".format(name, student_grade[name]))    
    return student_grade


def task1b():
	student_grade_dict = get_student_grade()
	f = open('final_grades', 'w')
	for st in student_grade_dict:
		f.write("{}|{}\n".format(st, student_grade_dict[st]))

	if VERBOSE >=1:
		print("Done printing grades to file 'final_grades' ")

def plot_histogram(grades_arr):
    import numpy as np
    import matplotlib.mlab as mlab
    import matplotlib.pyplot as plt

    num_bins = 5
    n, bins, patches = plt.hist(grades_arr, num_bins, facecolor='blue', alpha=0.5)
    plt.show()

def task1c():
	student_grade_dict = get_student_grade()
	plot_histogram(list(student_grade_dict.values()))

def get_most_freq_grade():
    import operator
    freq_dict = dict_from_error_code_freq()
    return max(freq_dict.items(), key=operator.itemgetter(1))[0]

def task1d():
	value_dict = get_error_codes_dict()
	most_freq = get_most_freq_grade()
	freq_dict = dict_from_error_code_freq()
	if VERBOSE >= 2:
		print(freq_dict)
	print("The most frequent error code is {}:{} with {} time shown".format(most_freq, value_dict[most_freq],freq_dict[most_freq]))

def task1():
	task1a()
	task1b()
	task1c()
	task1d()

if __name__ == "__main__":
    # execute only if run as a script
    task1d()
