class CBuilder:
	def __init__(self, projectDir):
		self.scripts = dict()
		self.defaultTarget = None
		self.defaultConfiguration = None
		self.projectDir = projectDir
		self.targets = []
		self.configurations = []
		self.globalDefinitions = {
								'projectDir' : self.projectDir,
								'platform' : slPlatform(),
								'path' : path
								}
		self.addGlobalIdentifiers('ppc i386 x86_64 ppc64 armv6 armv7') # architectures
		self.addGlobalIdentifiers('executable staticLib dynamicLib application framework bundle') # target types
		self.addGlobalIdentifiers('macos ios iosSimulator windows windowsPhone') # platforms
		self.settings = []
		self.dependencies = CDependencyGraph()

	def addGlobalIdentifiers(self, identifiers):
		for identifier in identifiers.split():
			self.globalDefinitions[identifier] = identifier

	def addTarget(self, targetName):
		if targetName in self.targets:
			log.logError('Target "' + targetName + '" already defined')
			return
		self.targets.append(targetName)
		self.addGlobalIdentifiers(targetName)

	def addConfiguration(self, configurationName):
		if configurationName in self.configurations:
			log.logError('Configuration "' + configurationName + '" already defined')
			return
		self.configurations.append(configurationName)
		self.addGlobalIdentifiers(configurationName)

	def addSettings(self, settings):
		self.settings.append(settings)

	def populateSettings(self, settings):
		for settingsData in self.settings:
			predicateMatched = False
			try:
				predicateMatched = eval(settingsData['predicate'], self.globalDefinitions, settings)
			except SyntaxError, error:
				error.filename = settingsData['file']
				error.lineno = settingsData['line']
				raise

			if predicateMatched:
				try:
					slExecWithEnv(settingsData['block'], self.globalDefinitions, settings)
				except SyntaxError, error:
					error.filename = settingsData['file']
					error.lineno += settingsData['line']
					raise
		expandedSettings = CSettingsExpander(settings, self.globalDefinitions).destSettings
		settings.update(expandedSettings)

	def createSettings(self, target, configuration):
		result = {
			'target' : target,
			'configuration' : configuration,
			'projectDir' : self.globalDefinitions['projectDir'],
			'sourcesRoots' : [],
			'treeHeadersRoots' : [],
			'plainHeadersRoots' : [],
			'treeResourcesRoots' : [],
			'plainResourcesRoots' : [],
			'buildDir' : path.join('$(projectDir)', 'build'),
			'intermediateDir' : path.join('$(buildDir)', 'intermediate'),
			'configurationBuildDir' : path.join('$(buildDir)', '$(configuration)'),
			'configurationIntermediateDir' : path.join('$(intermediateDir)', '$(target)', '$(configuration)'),
			'objectsRootDir' : path.join('$(configurationIntermediateDir)', 'objects', '$(targetPlatform)', '$(architecture)'),
			'dependenciesRootDir' : path.join('$(configurationIntermediateDir)', 'dependencies', '$(targetPlatform)', '$(architecture)'),
			'intermediateProductsDir' : path.join('$(configurationIntermediateDir)', 'products', '$(targetPlatform)', '$(architecture)'),
			'productName' : '$(target)',
			'executableName' : '$(productName)',
			'executableExtension' : '',
			'headerSearchPaths' : [],
			'wrapperExtension' : '',
			'libraries' : []
			}
		return result

	def createToolset(self, target, configuration):
		bestToolset = None
		bestToolsetRating = 0
		for i in availableToolsets:
			toolset = i(self, target, configuration)
			rating = toolset.ratingForBuildEnvironment()
			if rating > bestToolsetRating:
				bestToolsetRating = rating
				bestToolset = toolset
		bestToolset.onToolsetSelected()
		return bestToolset

	def performBuild(self):
		if self.defaultTarget == None:
			self.defaultTarget = self.targets[0]

		if self.defaultConfiguration == None:
			self.defaultConfiguration = self.configurations[0]

		for target in self.dependencies.unwrappedForObject(self.defaultTarget):
			log.logStartBuildTarget(target, self.defaultConfiguration)
			toolSet = self.createToolset(target, self.defaultConfiguration)
			toolSet.build()

	def performScript(self, scriptName):
		exec(self.scripts[scriptName])
