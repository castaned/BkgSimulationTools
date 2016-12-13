#!/usr/bin/python26   
# -*- coding: utf-8 -*-

from string import Template                                                         
from contextlib import nested 
from shutil import copyfile                                                                                  
from random import randint                                                                                   
from os import getcwd   


import subprocess
import os
import fileinput
import sys

FILE_TEMPLATE_ = 'CMSpp_template.inp'

def get_random_num_():

#    sim_params = {}

    random_seed = randint(1,9999999)

    file_in_path = FILE_TEMPLATE_

    file_out_path = 'CMSpp_'
    file_out_path += str(random_seed).strip() + '.inp'
    print file_in_path
    print file_out_path

    try:
        copyfile(file_in_path, file_out_path)
    except IOError:
        print 'ERROR: I/O error and will be closed'
        exit(1)

#    sim_params['random_seed'] = int(random_seed)*1.0        

    my_random = int(random_seed)*1.0

    with open(file_out_path, "a") as myfile:
        myfile.write("RANDOMIZ         1.0 %d.\n" %my_random)
        myfile.write("START            1.0 99999999.                          0.0\n")
        myfile.write("*\n")
        myfile.write("STOP\n")


#        for line in fileinput.input([filename], inplace=True):
#    if line.strip().startswith('initial_mass = '):
#        line = 'initial_mass = 123\n'
#    sys.stdout.write(line)


#    with open(file_in_path,"w") as file_in:
#        for line in fileinput.input(file_in_path, inplace=True):
#            if line.strip().startswith('RANDOMIZE'):
#                line = 'RANDOMIZE        1.0  9999\n'
#                sys.stdout.write(line)
#    data = f.read()
#    do something with data


#    with nested(open(file_in_path, 'r'), open(file_out_path, 'w')) as (file_in, file_out):
#        template = Template(file_in.read())
#        text_out = template.substitute(sim_params)
#        file_out.write(text_out)
        
    
    bashCommand = "$FLUPRO/flutil/rfluka -e runFLUKA  "+file_out_path
    print bashCommand

    os.system(bashCommand)
#    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
#    output = process.communicate()[0]

    return random_seed



def main():

    random_seed_val = get_random_num_()
    print 'random number:  ' 
    print random_seed_val*1.0

    

main()


