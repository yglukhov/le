
def validate_pair(ob):
	try:
		if not (len(ob) == 2):
			#print("Unexpected result:", ob, file=sys.stderr)
			raise ValueError
	except:
		return False
	return True

def consume(iter):
	try:
		while True: next(iter)
	except StopIteration:
		pass

def get_environment_from_batch_command(env_cmd, initial=None):
	"""
	Take a command (either a single command or list of arguments)
	and return the environment created after running that command.
	Note that if the command must be a batch file or .cmd file, or the
	changes to the environment will not be captured.

	If initial is supplied, it is used as the initial environment passed
	to the child process.
	"""
	if not isinstance(env_cmd, (list, tuple)):
		env_cmd = [env_cmd]
	# construct the command that will alter the environment
	env_cmd = subprocess.list2cmdline(env_cmd)
	# create a tag so we can tell in the output when the proc is done
	tag = 'Done running command'
	# construct a cmd.exe command to do accomplish this
	cmd = 'cmd.exe /s /c "{env_cmd} && echo "{tag}" && set"'.format(**vars())
	# launch the process
	proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, env=initial)
	out, err = proc.communicate()
	# parse the output sent to stdout
	lines = str(out).split("\\r\\n")
	# consume whatever output occurs until the tag is reached
	lines = itertools.dropwhile(lambda l: tag not in l, lines)
	# define a way to handle each KEY=VALUE line
	handle_line = lambda l: l.rstrip().split('=',1)
	# parse key/values into pairs
	pairs = map(handle_line, lines)
	# make sure the pairs are valid
	valid_pairs = filter(validate_pair, pairs)
	# construct a dictionary of the pairs
	result = dict(valid_pairs)
	return result

class CWindowsToolset(CToolset):
	def ratingForBuildEnvironment(self):
		if slPlatform() == 'windows': return 0xff
		return 0

	def openRegistryKey(self, rootKey, path):
		import winreg
		result = None
		try:
			result = winreg.OpenKey(rootKey, path)
		except WindowsError:
			pass
		return result

	def setupVisualStudioInfo(self):
		import winreg
		keyVal = 'SOFTWARE\Wow6432Node\Microsoft\VisualStudio'
		key = self.openRegistryKey(winreg.HKEY_LOCAL_MACHINE, keyVal)
		if not key:
			keyVal = 'SOFTWARE\Microsoft\VisualStudio'
			key = self.openRegistryKey(winreg.HKEY_LOCAL_MACHINE, keyVal)

		if key:
			vsInfo = {}
			subkeysCount = winreg.QueryInfoKey(key)[0]
			for i in range(subkeysCount):
				vsVersion = winreg.EnumKey(key, i)
				versionKey = self.openRegistryKey(key, vsVersion)
				if versionKey:
					installDirValue = None
					try:
						installDirValue = winreg.QueryValueEx(versionKey, 'InstallDir')
						info = {}
						info['ideDir'] = installDirValue[0]
						info['vcDir'] = installDirValue[0] + '\\..\\..\\VC'
						vsInfo[vsVersion] = info
						vsInfo['default'] = info
					except WindowsError:
						pass
			self.visualStudioInfo = vsInfo
		else:
			raise Exception()
		self._visualCppEnvironment = None

	def vcppEnvironment(self):
		if not self._visualCppEnvironment:
			command = self.visualStudioInfo['default']['vcDir'] + '\\bin\\vcvars32.bat'
			self._visualCppEnvironment = get_environment_from_batch_command(command)
		return self._visualCppEnvironment

	def visualCPPCompilerPath(self):
		return self.visualStudioInfo['default']['vcDir'] + '\\bin\\cl.exe'

	def onToolsetSelected(self):
		super(CWindowsToolset, self).onToolsetSelected()
		self.setupVisualStudioInfo()

	def objectNameForSourceName(self, sourceFile):
		return sourceFile + '.obj'

		
	def compilerCommandLine(self, sourceFile, objectFile):
		command = [self.visualCPPCompilerPath(), '/nologo', '/EHsc', '/c']
		for searchPath in self.settings['headerSearchPaths']:
			command.append('/I' + searchPath)
		command.append('/Fo' + objectFile)
		command.append(sourceFile)
		command.append('/Zi')
		command.extend(['/GS', '/RTC1', '/DEBUG'])
		return command

	def compileSource(self, sourceFile, objectFile):
		slMakedirs(path.dirname(objectFile))
		command = self.compilerCommandLine(sourceFile, objectFile)
		theTime = time()
		p = Popen(command, stdout = PIPE, stderr = PIPE, env = self.vcppEnvironment(), universal_newlines = True)
		out, err = p.communicate()
		global totalBuildTime
		totalBuildTime += time() - theTime
		if p.returncode:
			print(command)
			print(slDecodeCLIOutput(out))
		if len(err):
			print(err)

	def defaultExecutableExtension(self):
		return 'exe'

	def linkObjects(self, objects, executable):
		command = [self.visualCPPCompilerPath(), '/nologo', '/EHsc', '/MT']
		command.append('/Fe' + executable)
		for lib in self.settings['libraries']:
			command.append(lib + '.lib')
		command.extend(objects)
		command.extend(['/link', '/LTCG'])
		command.append('/DEBUG')
		for libPath in self.settings['librarySearchPaths']:
			command.append('/LIBPATH:' + libPath)
		#print(command)
		p = Popen(command, stdout = PIPE, stderr = PIPE, env = self.vcppEnvironment(), universal_newlines = True)
		out, err = p.communicate()
		print(slDecodeCLIOutput(out))

	def actualDependenciesForSourceFile(self, source):
		log.logInfo('Analyzing dependencies of ' + path.basename(source))
		command = [self.visualCPPCompilerPath(), '/nologo', '/EHsc', '/E']
		for searchPath in self.settings['headerSearchPaths']:
			command.append('/I' + searchPath)
		command.append(source)
		p = Popen(command, stdout = PIPE, stderr = PIPE, env = self.vcppEnvironment(), universal_newlines = True)
		out, err = p.communicate()
		result = set()
		for line in slDecodeCLIOutput(out).splitlines():
			if line.startswith('#line '):
				result.add(re.search('#line [^ ]+ "(.*)"', line).group(1))
		return list(result)


availableToolsets.append(CWindowsToolset)
