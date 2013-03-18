class CMacOSXToolset(CGCCToolset):
	def ratingForBuildEnvironment(self):
		if slPlatform() == 'macos':
			return 0xff
		return 0

	def currentSdk(self):
		sdkVersion = self.settings.get('sdkVersion', 'latestVersion')
		return self.availableSdks[self.builder.globalDefinitions['targetPlatform']][sdkVersion]

	def sdkRoot(self):
		return self.currentSdk()['sdkRoot']

	def platformRoot(self):
		return self.currentSdk()['platformRoot']

	def platformBinDir(self):
		result = path.join(self.platformRoot(), 'usr/bin')
		if not path.exists(result):
			result = path.join(self.currentSdk()['developerFolder'], 'usr/bin')
		return result

	def targetPlatformVersion(self):
		result = self.settings.get('targetPlatformVersion')
		if not result:
			result = self.currentSdk()['version']
		return result

	def onToolsetSelected(self):
		CGCCToolset.onToolsetSelected(self)
		if 'targetPlatform' not in self.builder.globalDefinitions:
			self.builder.globalDefinitions['targetPlatform'] = 'macos'
		self.availableSdks = CMacOSPlatfromFinder().findPlatforms()

	def defaultWrapperExtension(self):
		return {
			'application' : 'app',
			'framework' : 'framework',
			'bundle' : 'bundle',
			}.get(self.settings['targetType'])

	def defaultExecutableExtension(self):
		if self.settings['targetType'] == 'dynamicLib':
			return 'dylib'
		return CGCCToolset.defaultExecutableExtension(self)

	def executablePath(self):
		if self.settings['targetType'] == 'application':
			if self.builder.globalDefinitions['targetPlatform'] == 'macos':
				return path.join(self.wrapperFileName(), 'Contents', 'MacOS')
			else:
				return self.wrapperFileName()
		elif self.settings['targetType'] == 'framework':
			return path.join(self.wrapperFileName(), 'Versions', 'A')
		return ''

	def headersRootPath(self):
		if self.settings['targetType'] == 'framework':
			return path.join(self.wrapperFileName(), 'Versions', 'A', 'Headers')
		return CGCCToolset.headersRootPath(self)

	def resourcesRootPath(self):
		if self.settings['targetType'] == 'application':
			if self.builder.globalDefinitions['targetPlatform'] == 'macos':
				return path.join(self.wrapperFileName(), 'Contents', 'Resources')
			else:
				return self.wrapperFileName()
		elif self.settings['targetType'] == 'framework':
			return path.join(self.wrapperFileName(), 'Versions', 'A', 'Resources')
		return ''

	def appendFlagsToLinkerCommand(self, command):
		#		command.append('-F' + path.join(self.sdkRoot(), 'System', 'Library', 'Frameworks'))

		for framework in self.settings.get('frameworks', []):
			command.append('-framework')
			command.append(framework)

		for lib in self.settings.get('libraries', []):
			if '/' in lib:
				libname = path.filename(lib).split('.')[0]
				command.append('-l' + libname)
				if lib.startswith('/'):
					if path.exists(lib):
						command.append(lib)
				else:
					projectDir = self.builder.projectDir
					if path.exists(path.join(projectDir, lib)):
						command.append('-L' + path.dirname(path.join(projectDir, lib)))
			else:
				command.append('-l' + lib)

		for libPath in self.settings.get('librarySearchPaths', []):
			command.append('-L' + libPath)


	def linkerCommandLine(self, objectFiles, outputFile):
		command = []
		if self.settings['targetType'] == 'staticLib':
			command.append('libtool')
			command.append('-static')
			command.append('-arch_only')
			command.append(self.settings['architecture'])
		elif self.settings['targetType'] == 'dynamicLib':
			command.append('g++')
			command.append('-dynamiclib')
			command.append('-arch')
			command.append(self.settings['architecture'])
		elif self.settings['targetType'] == 'application':
			command.append(path.join(self.platformBinDir(), 'g++'))
			command.append('-arch')
			command.append(self.settings['architecture'])
			if self.builder.globalDefinitions['targetPlatform'] == 'iosSimulator':
				command.extend('-Xlinker -objc_abi_version -Xlinker 2'.split())
		elif self.settings['targetType'] == 'framework':
			command.append('g++')
			command.append('-dynamiclib')
			command.append('-arch')
			command.append(self.settings['architecture'])
		command.extend(objectFiles)
		command.append('-isysroot')
		command.append(self.sdkRoot())
		command.append('-o')
		command.append(outputFile)
		self.addMinTargetPlatformVersionToCommandLine(command)
		self.appendFlagsToLinkerCommand(command)
		print(command)
		return command

	def createUniversalBinary(self, binaries, output):
		command = ['lipo']
		command.extend(binaries)
		command.append('-create')
		command.append('-output')
		command.append(output)
		print(command)
		call(command)

	def addMinTargetPlatformVersionToCommandLine(self, command):
		targetPlatform = self.builder.globalDefinitions['targetPlatform'];
		if targetPlatform in ['ios']:
			command.append('-miphoneos-version-min=' + self.targetPlatformVersion())
		if targetPlatform in ['macos']:
			command.append('-mmacosx-version-min=' + self.targetPlatformVersion())
		if targetPlatform in ['iosSimulator']:
			command.append('-mmacosx-version-min=10.6')

	def compilerCommandLine(self, sourceFile, outputFile):
		result = CGCCToolset.compilerCommandLine(self, sourceFile, outputFile)
		sdk = self.sdkRoot()
		result[0] = path.join(self.platformBinDir(), 'gcc')
		result.append('-isysroot')
		result.append(sdk)
		self.addMinTargetPlatformVersionToCommandLine(result)
		targetPlatform = self.builder.globalDefinitions['targetPlatform']
		if targetPlatform == 'iosSimulator':
			result.append('-fobjc-abi-version=2')
			if sourceFile.endswith('.mm'):
				result.append('-fobjc-legacy-dispatch')
		if targetPlatform in ['iosSimulator', 'ios']:
			result.append('-D__IPHONE_OS_VERSION_MIN_REQUIRED=40200')
		return result

	def createFrmameworkSymlinks(self):
		wrapperPath = path.join(self.settings['configurationBuildDir'], self.wrapperFileName())
		link = path.join(wrapperPath, 'Versions', 'Current')
		if not path.lexists(link):
			os.symlink('A', link)

		link = path.join(wrapperPath, 'Headers')
		if not path.lexists(link):
			os.symlink('Versions/Current/Headers', link)

		link = path.join(wrapperPath, 'Resources')
		if not path.lexists(link):
			os.symlink('Versions/Current/Resources', link)

		executableName = self.executableFileName()
		link = path.join(wrapperPath, executableName)
		if not path.lexists(link):
			os.symlink(path.join('Versions/Current', executableName), link)

	def destInfoPlistPath(self):
		wrapperPath = path.join(self.settings['configurationBuildDir'], self.wrapperFileName())
		result = None
		if self.settings['targetType'] == 'framework':
			result = path.join(wrapperPath, 'Versions', 'A', 'Resources')
		elif self.builder.globalDefinitions['targetPlatform'] == 'macos':
			result = path.join(wrapperPath, 'Contents')
		else:
			result = wrapperPath
		return path.join(result, 'Info.plist')

	def importKeyFromSettingsToInfoPlist(self, infoPlist, settingsKey, infoPlistKey):
		value = self.settings.get(settingsKey)
		if value:
			infoPlist[infoPlistKey] = value

	def createInfoPlist(self):
		destInfoPlist = self.destInfoPlistPath()
		infoPlistPath = self.settings.get('infoPlistPath')
		slMakedirs(path.dirname(destInfoPlist))
		if infoPlistPath:
			shutil.copy(infoPlistPath, destInfoPlist)
			self.processInfoPlist(destInfoPlist)
		else:
			packageType = 'FMWK'
			if self.settings['targetType'] == 'application':
				packageType = 'APPL'
			infoPlist = {
				'CFBundleDevelopmentRegion' : 'English',
				'CFBundleExecutable' : self.executableFileName(),
				'CFBundleInfoDictionaryVersion' : '6.0',
				'CFBundlePackageType' : packageType,
				'CFBundleSignature' : '????',
			}
			self.importKeyFromSettingsToInfoPlist(infoPlist, 'productIdentifier', 'CFBundleIdentifier')
			self.importKeyFromSettingsToInfoPlist(infoPlist, 'productVersion', 'CFBundleVersion')

			infoPlistAdditions = self.settings.get('infoPlist')
			if infoPlistAdditions:
				infoPlist.update(infoPlistAdditions)
			plistlib.writePlist(infoPlist, destInfoPlist)

	def build(self):
		CGCCToolset.build(self)
		print(self.sdkRoot())
		if self.settings['targetType'] == 'framework':
			self.createFrmameworkSymlinks()
		if self.productNeedsWrapper():
			self.createInfoPlist()

availableToolsets.append(CMacOSXToolset)
