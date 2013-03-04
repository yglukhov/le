
class CGCCToolset(CToolset):
	def ratingForBuildEnvironment(self):
		return 1

	def objectNameForSourceName(self, sourceFile):
		return sourceFile + '.o'

	def defaultExecutableExtension(self):
		return {
			'staticLib' : 'a',
			'dynamicLib' : 'so'
			}.get(self.settings['targetType'])

	def compilerCommandLine(self, sourceFile, outputFile):
		command = ['gcc', '-c', sourceFile, '-o', outputFile]
		for searchPath in self.settings['headerSearchPaths']:
			command.append('-I')
			command.append(searchPath)

		command.append('-arch')
		command.append(self.settings['architecture'])
		return command

	def compileSource(self, sourceFile, objectFile):
		slMakedirs(path.dirname(objectFile))
		command = self.compilerCommandLine(sourceFile, objectFile)
		theTime = time()
		p = Popen(command, stdout = PIPE, stderr = PIPE)
		out, err = p.communicate()
		global totalBuildTime
		totalBuildTime += time() - theTime
		if len(out):
			print(out)
		if len(err):
			print(err)

	def linkerCommandLine(self, objectFiles, outputFile):
		result = ['ld']
		result.extend(objectFiles)
		result.append('-o')
		result.append(outputFile)

	def linkObjects(self, objects, executable):
		command = self.linkerCommandLine(objects, executable)
		theTime = time()
		call(command)
		global totalBuildTime
		totalBuildTime += time() - theTime

	def actualDependenciesForSourceFile(self, source):
		command = self.compilerCommandLine(source, '-')
		command.append('-MM')
		p = Popen(command, stdout = PIPE, stderr = PIPE)
		out, err = p.communicate()
		result = []
		for line in out.split('\n')[2:]:
			if line.endswith(' \\'):
				line = line[:-2]
			line = line.strip()

			if len(line):
				for dep in line.split():
					result.append(dep)
		return result

availableToolsets.append(CGCCToolset)
