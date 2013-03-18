#!/usr/bin/env python
################################################################################
# slMake                                                                       #
# Copyright (c) 7lifes.com                                                     #
#                                                                              #
# This script is a self-contained build system.                                #
################################################################################

################################################################################
################################################################################
_slMakeInlineSections = """
### SLMAKE INLINE SECTIONS BEGIN
### SLMAKE INLINE SECTION testSection
### Hello World!
### This is a section
### SLMAKE INLINE SECTION AnotherSection
### Hello World! This is another! #
### SLMAKE INLINE SECTIONS END
"""

import os, string, hashlib, sys, shutil, plistlib, itertools, subprocess, re, codecs

from os import path
from subprocess import Popen, call, PIPE

from pprint import pprint
from time import time

from optparse import OptionParser

try:
	from io import StringIO
except:
	from StringIO import StringIO

totalBuildTime = 0

if sys.version_info[0] >= 3:
	def slExecWithEnv(code, locals=None, globals=None): exec("exec(code, locals, globals)")
	def slIsString(obj): return isinstance(obj, str)
else:
	def slExecWithEnv(code, locals=None, globals=None): exec("exec code in locals, globals")
	def slIsString(obj): return isinstance(obj, basestring)

def slExecfile(filepath, locals=None, globals=None):
	return slExec(open(filepath, 'r').read(), locals, globals)

def slMakedirs(dirPath):
	if not path.exists(dirPath): os.makedirs(dirPath)

def slIsIdentifierNative(identifier):
	return identifier.startswith('com.7lifes.')

def slDecodeCLIOutput(output):
	#TODO: Check for universal newlines supported. For now, hope that it is.
	return output

def slEscapeString(str):
	return str

def slUnescapeString(str):
	return str

def slPlatform():
	if sys.platform == 'darwin':
		return 'macos'
	elif sys.platform == 'win32':
		return 'windows'
	return None

def slInlineSections():
	file = open(__file__, 'r').read()
	result = {}
	inSections = False
	curSection = ""
	curSectionName = None
	sectionPrefix = '### SLMAKE INLINE SECTION '
	for line in file.splitlines():
		if inSections:
			nextSection = line.startswith(sectionPrefix)
			if line == '### SLMAKE INLINE SECTIONS END' or nextSection:
				if curSectionName: result[curSectionName] = slUnescapeString(curSection)
				if nextSection:
					curSectionName = line[len(sectionPrefix):]
					curSection = ""
				else:
					break
			else:
				curSection += line[4:] + '\n'
		elif line == '### SLMAKE INLINE SECTIONS BEGIN':
			inSections = True
	return result

def slSetInlineSections(sections):
	file = open(__file__, 'r').read()
	inSections = False
	for line in file.splitlines():
		if inSections:
			if line == '### SLMAKE INLINE SECTIONS END':
				for key, value in sections:
					print('### SLMAKE INLINE SECTION ' + key)
					for sectionLine in value.splitlines():
						print('### ' + sectionLine)
				print(line)
				inSections = False
		else:
			print(line)
			if line == '### SLMAKE INLINE SECTIONS BEGIN':
				inSections = True

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
