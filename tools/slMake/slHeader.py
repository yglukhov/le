#!/usr/bin/env python
################################################################################
# slMake                                                                       #
# Copyright (c) 7lifes.com                                                     #
#                                                                              #
# This script is a self-contained build system.                                #
################################################################################

################################################################################
__inlineProjects = """
# Inline Projects Start

# Inline Projects End
"""
################################################################################
import os, string, md5, sys, shutil, plistlib

from os import path
from subprocess import Popen, call, PIPE

from pprint import pprint
from time import time

from optparse import OptionParser

totalBuildTime = 0


def slMakedirs(dirPath):
	if not path.exists(dirPath): os.makedirs(dirPath)

def slIsIdentifierNative(identifier):
	return identifier.startswith('com.7lifes.')

def slPlatform():
	if sys.platform == 'darwin':
		return 'macos'
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
