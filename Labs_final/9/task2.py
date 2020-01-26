from task1 import *

def add_factor():
	""" Insted of getting the new dict, duplicating it,
		and setting the highest removal as zero.
		Now we have both!
	"""
	value_dict = get_error_codes_dict()
	most_freq_err = get_most_freq_grade()

	# the zerod out value for highest freq
	value_dict[most_freq_err] = 0

	default_grades_dict = get_student_grade()
	new_grades_dict = get_student_grade(value_dict)

	return new_grades_dict, default_grades_dict

def task2a():
	import statistics
	import numpy as np
	new_dict, old_dict = add_factor()

	for key in old_dict:
		print("{} : {} => {}".format(key, old_dict[key], new_dict[key]))

	print("Old mean : {}\n New mean : {}".format(statistics.mean(old_dict.values()), statistics.mean(new_dict.values())))
	
def task2b():
	new_dict, old_dict = add_factor()

	for key in old_dict:
		if (old_dict[key] < 56):
			print("{} : {} => {}".format(key, old_dict[key], new_dict[key]))


if __name__ == "__main__":
    # execute only if run as a script
    task2b()
