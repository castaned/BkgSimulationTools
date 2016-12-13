#!/usr/bin/python26
# -*- coding: utf-8 -*-
"""
FOCUS - FLUKA for CMS Users | PH-CMX-DS | BRIL Radiation Simulation
European Organization for Nuclear Research (CERN)

tested with: Python 2.6 (available in CERN AFS: /usr/bin/python26)

enforced coding style:
    http://google-styleguide.googlecode.com/svn/trunk/pyguide.html
pydoc command:
    /usr/bin/pydoc26 -w ./

Script common.py
================
file: common.py

description: Contains common code used by other FOCUS's scripts. 

HOW TO
======
Please see README.txt.

contact:
http://hypernews.cern.ch/HyperNews/CMS/get/bril-radiation-simulation.html

"""
#------------------------------------------------------------------------------

from os import environ
import version

__author__ = version.AUTHOR_
__version__ = version.VERSION_
__date__ = version.DATE_

LOG_FILE_ = 'log_common.txt'

#------------------------------------------------------------------------------

def os_error(command):
    """Prints information abut OS error. Kills FOCUS process!
    
       Returns:
           Kills FOCUS process and returns to the system exit status 1.
    """
    print_delimiter()
    print 'ERROR: no such file or directory:'
    print '\t%s' % ' '.join(command)
    print 'please check if environment variable $FLUPRO is set properly'
    print 'process is closed'
    print_delimiter()
    exit(1)

def Popen_error(error_msg):
    """Prints information abut Popen() call error. Kills FOCUS process!
    
       Returns:
           Kills FOCUS process and returns to the system exit status 1.
    """
    print_delimiter()
    print 'ERROR: %s' % error_msg
    print 'FOCUS execution terminated'
    print_delimiter()
    exit(1)

#------------------------------------------------------------------------------

def print_header():
    """Prints scripts header."""
    print_delimiter(limiter='/')
    print '//'
    print '//    FOCUS version %s | %s' % (__version__, __date__)
    print '//    FLUKA for CMS Users'
    print '//    BRIL Radiation Simulation'
    print '//'
    print_delimiter(limiter='/')

def path_error_():
    """Prints help in case when environment variable $FLUPRO is not set up.
    
       Returns:
           Kills FOCUS process and returns to the system exit status 1.
    """
    print 'ERROR: $FLUPRO environment variable has to be set up.'
    print 'for bash-like shell:'
    print '\texport FLUPRO=$HOME/FLUKA'
    print 'for tcsh-like shell:'
    print '\tsetenv FLUPRO $HOME/FLUKA'
    print 'where $HOME/FLUKA is a path to FLUKA installation folder.'
    print 'process execution stopped'
    exit(1)

def get_FLUKA_path():
    """Extract from environment variable $FLUPRO path to FLUKA installation
    directory."""
    try:
        path = environ['FLUPRO']
    except KeyError:
        path_error_()
    return path

def print_delimiter(limiter='*'):
    """Prints single line containing 79 copies of chosen character.
    
       Args:
           limiter: Character that will be used to build a line.    
    """
    LINE_LENGTH = 80 - 1
    line = [None] * LINE_LENGTH
    for i in range(LINE_LENGTH):
        line[i] = limiter
    print ''.join(line)

def save_delimiter(file_handle, limiter='*'):
    """Saves to file single line containing 79 copies of chosen character.
    
       Args:
           file_handle: A handle to a file to whom the line will be written.
           limiter: Character that will be used to build a line.
    """
    LINE_LENGTH = 80 - 1
    line = [None] * LINE_LENGTH
    for i in range(LINE_LENGTH):
        line[i] = limiter
    file_handle.write((''.join(line) + '\n'))


#------------------------------------------------------------------------------ 

def main():
    print 'library: common.py'

if __name__ == '__main__':
    main()
