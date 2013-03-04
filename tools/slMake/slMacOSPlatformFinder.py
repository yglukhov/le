class CMacOSPlatfromFinder:
	def findPlatforms(self):
		self.result = {'macos' : {}, 'ios' : {}, 'iosSimulator' : {}}
		for dir in os.listdir('/'):
			if dir != 'Developer':
				developerFolder = path.join('/', dir)
				if path.exists(path.join(developerFolder, 'SDKs')) and path.exists(path.join(developerFolder, 'Platforms')):
					self.findPlatformsInDeveloper(developerFolder)

		mainDeveloperFolder = Popen("xcode-select -print-path", stdout=PIPE, shell=True).stdout.read()
		mainDeveloperFolder = mainDeveloperFolder[:-1]
		print('mainDeveloperFolder ' + mainDeveloperFolder)
		self.findPlatformsInDeveloper(mainDeveloperFolder)

		for platform, result in self.result.items():
			self.setLatestVersionInResult(result)

		return self.result

	def setLatestVersionInResult(self, result):
		latestVersion = ['0']
		latestVersionSdk = None
		for version, sdk in result.items():
			versionList = version.split('.')
			if versionList > latestVersion:
				latestVersion = versionList
				latestVersionSdk = sdk
		result['latestVersion'] = latestVersionSdk

	def findSdks(self, sdkFolder, sdkNamePrefix):
		sdkExtension = '.sdk'
		if path.exists(sdkFolder):
			for sdkName in os.listdir(sdkFolder):
				if sdkName.startswith(sdkNamePrefix) and sdkName.endswith('.sdk'):
					version = sdkName[len(sdkNamePrefix):-len(sdkExtension)]
					yield (path.join(sdkFolder, sdkName), version)

	def findSdksForPlatform(self, developerFolder, platformRoot, sdkNamePrefix):
		result = {}
		for (sdkRoot, sdkVersion) in self.findSdks(path.join(platformRoot, 'SDKs'), sdkNamePrefix):
			if sdkNamePrefix == 'MacOSX' and sdkVersion == '10.4u':
				sdkVersion = '10.4'
			result[sdkVersion] = {}
			result[sdkVersion]['sdkRoot'] = sdkRoot
			result[sdkVersion]['developerFolder'] = developerFolder
			result[sdkVersion]['platformRoot'] = platformRoot
			result[sdkVersion]['version'] = sdkVersion
		return result

	def findPlatformsInDeveloper(self, developerFolder):
		self.result['macos'].update(self.findSdksForPlatform(developerFolder, developerFolder, 'MacOSX'))
		platformRoot = path.join(developerFolder, 'Platforms', 'iPhoneOS.platform', 'Developer')
		if path.exists(platformRoot):
			self.result['ios'].update(self.findSdksForPlatform(developerFolder, platformRoot, 'iPhoneOS'))

		platformRoot = path.join(developerFolder, 'Platforms', 'iPhoneSimulator.platform', 'Developer')
		if path.exists(platformRoot):
			self.result['iosSimulator'].update(self.findSdksForPlatform(developerFolder, platformRoot, 'iPhoneSimulator'))

		platformRoot = path.join(developerFolder, 'Platforms', 'MacOSX.platform', 'Developer')
		if path.exists(platformRoot):
			self.result['macos'].update(self.findSdksForPlatform(developerFolder, platformRoot, 'MacOSX'))

