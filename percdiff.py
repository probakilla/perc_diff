#!/usr/bin/env python3

import ctypes
import ctypes.util
import getopt
import os
import pyperclip
import sys

SCRIPT_LOCATION = os.path.dirname(__file__)


def usage():
    print("Usage")
    print("\tpercdiff -d 123,456")


def parse_args():
    try:
        opts, _ = getopt.getopt(sys.argv[1:], "hd:", ["help", "direct"])
    except getopt.GetoptError as err:
        print(err)
        usage()
        sys.exit(1)
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit(0)
        elif opt in ("-d", "--direct"):
            return arg
        else:
            print("\033[31mERROR\033[0m Unhandled option")
            usage()
            sys.exit(2)
    return ""


def clib_call(arguments):
    libpath = SCRIPT_LOCATION + "/lib/percdiff.so"
    lib = ctypes.cdll.LoadLibrary(libpath)
    clib = ctypes.CDLL(ctypes.util.find_library('c'))
    lib.check_input.argtypes = (ctypes.c_char_p,)
    lib.check_input.restype = ctypes.c_char_p
    c_string = arguments.encode('utf-8')
    clib.free.argtypes = (ctypes.c_void_p,)
    result = lib.check_input(c_string)
    return result.decode("utf-8")


def main():
    args = parse_args()
    result = clib_call(args)
    pyperclip.copy(result)
    print(result)
    print("\033[33m[Result copied to clipboard]\033[0m")


if __name__ == "__main__":
    main()
