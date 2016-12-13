#!/usr/bin/python26
#==============================

import os

from os import environ
from subprocess import Popen
from subprocess import PIPE
from os import listdir
from os import getcwd
from os import remove

import common
import version

LOG_FILE_ = "log_compile.txt"

EXEC_FILE_ = 'runFLUKA'

RELATIVE_PATH_FFF_ = '/flutil/fff'
RELATIVE_PATH_LINK_ = '/flutil/ldpm3qmd'

OPT_FFF = ['-b', '-N']

FORTRAN_ROUTINES_ = [
    '/routines/fieldi.f',
    '/routines/lbqfin.f',
    '/routines/lbqfld.f',
    '/routines/litwod.f',
    '/routines/magfld.f',
    '/routines/mhcos.f',
    '/routines/usrglo.f',
    '/routines/mgdraw.f',
    ]

path_to_FLUKA = environ['FLUPRO']
print 'path to FLUKA '+path_to_FLUKA

path_compilation = path_to_FLUKA + RELATIVE_PATH_FFF_
print 'compilation path  '+path_compilation

path_link = path_to_FLUKA + RELATIVE_PATH_LINK_

print 'link path   '+path_link

#path_prefix = "/panfs/vol/a/alherna39/testfluka_laptop/run_fluka"
path_prefix = os.getcwd()

print 'prefix path  '+path_prefix

def compile_(file_log):
  
    cmpilation_cmd = [path_compilation]
    cmpilation_cmd.extend(OPT_FFF)

    for routine in FORTRAN_ROUTINES_:
        cmpilation_cmd.append(path_prefix + routine)
        try:

            file_log.write('\tcompiling: %s' % ' '.join(cmpilation_cmd) + '\n')
            output, error = Popen(args=cmpilation_cmd, stdout=PIPE,
                                  stderr=PIPE).communicate()
        except OSError:
            common.os_error(cmpilation_cmd)
        except ValueError:
            common.Popen_error('compilation process, invalid arguments')
        else:
            # Remove from compilation command last argument - user routines,
            # compiled with current loop step.
            del cmpilation_cmd[-1]


def link_(file_log):

    link_cmd = [path_link]
    
    exec_file = path_prefix +'/'+ EXEC_FILE_

    _OPT_LDPM3QMD = ['-o', exec_file, '-m', 'fluka']
    link_cmd.extend(_OPT_LDPM3QMD)

    for routine in FORTRAN_ROUTINES_:
        routine = routine.split('.')
        routine = path_prefix + routine[0]+'.o'
        link_cmd.append(routine)
        file_log.write('\tlinking file: %s' % routine + '\n')
        try:
            output, error = Popen(args=link_cmd, stdout=PIPE,
                              stderr=PIPE).communicate()
            file_log.write(output + '\n')
            file_log.write(error + '\n')
        except OSError:
            common.os_error(link_cmd)
        except ValueError:
            common.Popen_error('linking process, invalid arguments')


def remove_(file_log):

    print ' removing object files'

    current_path = path_prefix + '/routines/'
    file_list = listdir(current_path)

    for file_current in file_list:
        file_current = current_path + file_current
        if file_current.endswith('.o'):
            file_log.write('\tremoving file: %s' % file_current + '\n')
            remove(file_current) 
            


def main():

    with open(LOG_FILE_,"w") as file_log:
        compile_(file_log)
        link_(file_log)
        remove_(file_log)
 
if __name__=='__main__':
    main()
