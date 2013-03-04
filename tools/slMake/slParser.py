class CParser:
	def parseFileInputToBuilder(self, fileInput, builder, parentParser = None):
		self.parentParser = parentParser;
		self.fileInput = fileInput
		self.builder = builder
		self.line = 0
		return self.parse()

	def parse(self):
		while True:
			line = self._readLine()
			if len(line) == 0: break
			words = line.split()
			if len(words) == 0: continue
			if words[0][0] == '#': continue
			if words[0].startswith('//'): continue
			if words[0] == 'target':
				self._processTarget(words)
			elif words[0] == 'configuration':
				self._processConfig(words)
			elif words[0] == 'default':
				self._processDefault(words)
			elif words[0] == 'depend':
				self._processDependency(words)
			elif words[0] == 'script':
				self._processScript(words)
			elif words[0] == 'extension':
				self._processExtension(words)
			elif words[0] == 'include':
				self._processInclude(words)
			elif words[0] == 'settings' or (words[0] == 'optional' and words[1] == 'settings'):
				self._processSettings(words)
			elif words[0] == 'targets':
				self._processTargets(words)
			elif words[0] == 'configurations':
				self._processConfigurations(words)
			else:
				self._pushError('Unknown keyword "' + words[0] + '"')

	def _pushError(self, text):
		log.logError(text, self.fileInput.name, self.line)

	def _processTarget(self, words):
		self._processSettingsWithPredicate("target==" + words[1], True)

	def _processConfig(self, words):
		self._processSettingsWithPredicate("configuration==" + words[1], True)

	def _processExtension(self, words):
		exec(self._readBlock())

	def _processScript(self, words):
		self.builder.scripts[words[1]] = self._readBlock()

	def _processInclude(self, words):
		childParser = CParser()
		fileInput = open(words[1])
		childParser.parseFileInputToBuilder(fileInput, self.builder, self)

	def _processSettingsWithPredicate(self, predicate, optional):
		line = self.line + 1
		block = self._readBlock()
		self.builder.addSettings({'predicate' : predicate, 'block' : block, 'line' : line, 'file' : self.fileInput.name })

	def _processSettings(self, words):
		optional = False
		settingsPredicate = "True"
		if len(words) > 1:
			optional = words[0] == 'optional'
			if optional:
				settingsPredicate = words[2:]
			else:
				settingsPredicate = words[1:]
			settingsPredicate = ' '.join(settingsPredicate)

		self._processSettingsWithPredicate(settingsPredicate, optional)

	def _processTargets(self, words):
		for word in words[1:]:
			self.builder.addTarget(word)

	def _processConfigurations(self, words):
		for word in words[1:]:
			self.builder.addConfiguration(word)

	def _processDefault(self, words):
		if len(words) == 3:
			if words[1] == 'target':
				self.builder.defaultTarget = words[2]
			elif words[1] == 'configuration':
				self.builder.defaultConfiguration = words[2]
			else:
				self._pushError('Unknown keyword "' + words[1] + '". Expected "target" or "configuration."')
		else:
			self._pushError('Invalid statement')

	def _processDependency(self, words):
		if len(words) < 4:
			log.logError("Invalid statement")
		self.builder.dependencies.addDependenciesForObject(words[3:], words[1])

	def _readLine(self):
		self.line += 1
		return self.fileInput.readline()

	def _readBlock(self):
		lines = []
		self._readLine()
		while True:
			line = self._readLine()
			if line[0] == '}': break
			if line[0] == '\t':
				line = line[1:]
			lines.append(line)
		return ''.join(lines)
