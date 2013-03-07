#!/usr/bin/env python
################################################################################
# slMake                                                                       #
# Copyright (c) 7lifes.com                                                     #
#                                                                              #
# This script is a self-contained build system.                                #
################################################################################

################################################################################
################################################################################
import os, string, hashlib, sys, shutil, plistlib, itertools, subprocess, re

from os import path
from subprocess import Popen, call, PIPE

from pprint import pprint
from time import time

from optparse import OptionParser

totalBuildTime = 0

if sys.version_info[0] >= 3:
	def slExecWithEnv(code, locals=None, globals=None):
		exec("exec(code, locals, globals)")
else:
	def slExecWithEnv(code, locals=None, globals=None):
		exec("exec code in locals, globals")

def slExecfile(filepath, locals=None, globals=None):
	return slExec(open(filepath, 'r').read(), locals, globals)

def slIsString(obj):
	if sys.version_info[0] >= 3: return isinstance(obj, str)
	return isinstance(obj, basestring)

def slMakedirs(dirPath):
	if not path.exists(dirPath): os.makedirs(dirPath)

def slIsIdentifierNative(identifier):
	return identifier.startswith('com.7lifes.')

def slDecodeCLIOutput(output):
	#TODO: Check for universal newlines supported. For now, hope that it is.
	return output

def slPlatform():
	if sys.platform == 'darwin':
		return 'macos'
	elif sys.platform == 'win32':
		return 'windows'
	return None

def itersubclasses(cls, _seen=None):
	if not isinstance(cls, type):
		raise TypeError('itersubclasses must be called with '
						'new-style classes, not %.100r' % cls)
	if _seen is None: _seen = set()
	try:
		subs = cls.__subclasses__()
	except TypeError: # fails only when cls is type
		subs = cls.__subclasses__(cls)
	for sub in subs:
		if sub not in _seen:
			_seen.add(sub)
			yield sub
			for sub in itersubclasses(sub, _seen):
				yield sub
