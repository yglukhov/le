class CToolset:
	def __init__(self, builder, target, configuration):
		self.builder = builder
		self.target = target
		self.configuration = configuration

	def onToolsetSelected(self):
		self.filesCollector = CFilesCollector()
		pass

	def defaultWrapperExtension(self):
		return ''

	def wrapperExtension(self):
		result = self.settings.get('wrapperExtension')
		if not result:
			result = self.defaultWrapperExtension()
		return result

	def defaultExecutableExtension(self):
		return ''

	def executableExtension(self):
		result = self.settings.get('executableExtension')
		if not result:
			result = self.defaultExecutableExtension()
		return result

	def wrapperFileName(self):
		wrapperExtension = self.wrapperExtension()
		if wrapperExtension:
			return self.settings['productName'] + '.' + wrapperExtension
		return self.settings['productName']

	def productNeedsWrapper(self):
		return self.settings['targetType'] in ['application', 'framework', 'bundle']

	def createSettings(self, architecture):
		settings = self.builder.createSettings(self.target, self.configuration)
		settings['architecture'] = architecture
		self.builder.populateSettings(settings)
		return settings

	def actualDependenciesForSourceFile(self, source):
		return None

	def createDependencies(self, sourceFile, dependenciesFile):
		result = self.actualDependenciesForSourceFile(sourceFile)
		if result != None:
			slMakedirs(path.dirname(dependenciesFile))
			file = open(dependenciesFile, 'w')
			file.writelines([line + '\n' for line in result])
			file.close()
		return result

	def loadDependencies(self, dependenciesFile):
		file = open(dependenciesFile, 'r')
		result = [line.strip() for line in file]
		file.close()
		return result

	def areDependenciesValid(self, dependencies, objMTime, sourceFile, dependenciesFile, depsMTime):
		for dep in dependencies:
			depMTime = float('inf')
			if path.exists(dep):
				depMTime = path.getmtime(dep)
			if depMTime > depsMTime:
				dependencies = self.createDependencies(sourceFile, dependenciesFile)
				if dependencies != None:
					return self.areDependenciesValid(dependencies, objMTime, sourceFile, dependenciesFile, float('inf'))
				return True
			if depMTime > objMTime:
				return True
		return False

	def areDependenciesOutOfDate(self, sourceFile, objectFile, dependenciesFile):
		if not path.exists(objectFile):
			return True
		objMTime = path.getmtime(objectFile)
		if path.getmtime(sourceFile) > objMTime:
			return True

		depsMTime = 0
		dependencies = None

		if path.exists(dependenciesFile):
			depsMTime = path.getmtime(dependenciesFile)
			dependencies = self.loadDependencies(dependenciesFile)
		else:
			dependencies = self.createDependencies(sourceFile, dependenciesFile)
			depsMTime = float('inf')

		if not dependencies: return True
		return self.areDependenciesValid(dependencies, objMTime, sourceFile, dependenciesFile, depsMTime)

	def executablePath(self):
		return ''

	def executableFileName(self):
		extension = self.executableExtension()
		if extension:
			return self.settings['executableName'] + '.' + extension
		return self.settings['executableName']

	def dependenciesNameForSourceName(self, sourceFile):
		return sourceFile + '.dep'

	def iterateFileRoots(self, roots):
		rootCounter = 0
		for root in roots:
			rootCounter += 1
			rootPath = ''
			files = None
			if len(root) == 2:
				rootPath = root[0]
				files = root[1]
			else:
				files = [root]
			yield [rootCounter, rootPath, files]

	def buildExecutable(self):
		self.settings = self.createSettings('')
		#print(self.settings)
		architectures = self.settings.get('architectures', ['i386'])

		linkedProducts = []
		objects = set()
		needsRebuildUniversalBinary = False
		needsRelink = False
		executablePath = path.join(self.settings['configurationBuildDir'], self.executablePath(), self.executableFileName())

		for arch in architectures:
			self.settings = self.createSettings(arch)
			targetName = self.settings['target']
			objects.clear()

			needsRelink = False
			fileRoots = self.filesCollector.collectSources(self.settings.get('sourcesRoots', []))
			for srcRootCounter, srcRootPath, sources in self.iterateFileRoots(fileRoots):
				for source in sources:
					sourceFileName = path.basename(source)
					object = path.join(self.settings['objectsRootDir'], str(srcRootCounter), path.dirname(source), self.objectNameForSourceName(sourceFileName))
					dependencies = path.join(self.settings['dependenciesRootDir'], str(srcRootCounter), path.dirname(source), self.dependenciesNameForSourceName(sourceFileName))
					source = path.join(srcRootPath, source)
					if object in objects:
						log.logError('Object file: ' + object + '(' + source + ') was already processed!')
					else:
						objects.add(object)

					if self.areDependenciesOutOfDate(source, object, dependencies):
						log.logInfo('Compiling ' + sourceFileName)
						self.compileSource(source, object)
						needsRelink = True
					else:
						#log.logInfo('Skipping  ' + sourceFileName)
						pass

			if len(architectures) > 1 and len(objects):
				productDir = self.settings['intermediateProductsDir']
				intermediateExecutable = path.join(productDir, self.executableFileName())
				print("will link: " + intermediateExecutable)
				if not path.exists(intermediateExecutable):
					print("needs relink")
					needsRelink = True
				if needsRelink:
					log.logInfo('Linking ' + targetName)
					slMakedirs(productDir)
					self.linkObjects(objects, intermediateExecutable)
					linkedProducts.append(intermediateExecutable)
					needsRebuildUniversalBinary = True

		if len(architectures) == 1:
			if needsRelink or not path.exists(executablePath):
				log.logInfo('Linking ' + targetName)
				slMakedirs(path.dirname(executablePath))
				self.linkObjects(objects, executablePath)
		elif needsRebuildUniversalBinary or not path.exists(executablePath):
			log.logInfo('Creating universal binary for ' + targetName)
			slMakedirs(path.dirname(executablePath))
			self.createUniversalBinary(linkedProducts, executablePath)

	def headersRootPath(self):
		return 'Headers'

	def resourcesRootPath(self):
		return 'Resources'

	def copyFile(self, header, destination):
		if not path.exists(destination) or path.getmtime(destination) < path.getmtime(header):
			print('copying ' + header)
			shutil.copy(header, destination)

	def copyHeaders(self):
		headerDestinationRoot = path.join(self.settings['configurationBuildDir'], self.headersRootPath())
		if 'plainHeadersRoots' in self.settings:
			slMakedirs(headerDestinationRoot)
			plainHeadersRoots = self.filesCollector.collectHeaders(self.settings['plainHeadersRoots'])
			for headerRootCounter, headerRootPath, headers in self.iterateFileRoots(plainHeadersRoots):
				for header in headers:
					self.copyFile(path.join(headerRootPath, header), path.join(headerDestinationRoot, path.basename(header)))

		treeHeadersRoots = self.filesCollector.collectHeaders(self.settings.get('treeHeadersRoots', []))
		for headerRootCounter, headerRootPath, headers in self.iterateFileRoots(treeHeadersRoots):
			for header in headers:
				headerDestination = path.join(headerDestinationRoot, header)
				slMakedirs(path.dirname(headerDestination))
				self.copyFile(path.join(headerRootPath, header), headerDestination)

	def copyResources(self):
		resourceDestinationRoot = path.join(self.settings['configurationBuildDir'], self.resourcesRootPath())
		if 'plainResourcesRoots' in self.settings:
			slMakedirs(resourceDestinationRoot)
			plainResourcesRoots = self.filesCollector.collectAllFiles(self.settings['plainResourcesRoots'])
			for headerRootCounter, headerRootPath, headers in self.iterateFileRoots(plainResourcesRoots):
				for header in headers:
					self.copyFile(path.join(headerRootPath, header), path.join(resourceDestinationRoot, path.basename(header)))

		treeResourcesRoots = self.filesCollector.collectAllFiles(self.settings.get('treeResourcesRoots', []))
		for headerRootCounter, headerRootPath, headers in self.iterateFileRoots(treeResourcesRoots):
			for header in headers:
				headerDestination = path.join(resourceDestinationRoot, header)
				slMakedirs(path.dirname(headerDestination))
				self.copyFile(path.join(headerRootPath, header), headerDestination)


	def build(self):
		self.buildExecutable()
		if self.settings['targetType'] == 'framework':
			self.copyHeaders()
		if self.productNeedsWrapper():
			self.copyResources()

availableToolsets = []
