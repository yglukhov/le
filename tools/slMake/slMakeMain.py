
import py_compile

def findProjectConfiguration():
	selfPath = path.abspath(sys.argv[0])
	inlineSections = slInlineSections()
	if 'config' in inlineSections:
		return { 'configFile' : selfPath, 'config' : inlineSections['config'] }
	else:
		for dir in [
			os.getcwd(),
			path.dirname(selfPath)
			]:
			configFile = path.join(dir, 'config')
			if path.isfile(configFile):
				return { 'configFile' : configFile, 'config' : codecs.open(configFile, 'rU', 'utf').read() }
				break
	return None

def main():
	#print("Sections:")
	#pprint(slInlineSections())
	#print("platform: " + slPlatform())
	#	selfDirPath = os.path.dirname(path.abspath(argv[0]))
	projectConfiguration = findProjectConfiguration()
	if projectConfiguration:
		projectDir = path.dirname(projectConfiguration['configFile'])
		fileInput = StringIO(projectConfiguration['config'])
		#fileInput.name = 'config'
		builder = CBuilder(projectDir)
		parser = OptionParser()
		(options, args) = parser.parse_args()
		builder.globalDefinitions['targetPlatform'] = slPlatform();
		parser = CParser()
		parser.inputName = 'config'
		parser.parseFileInputToBuilder(fileInput, builder)
		builder.performBuild()
	else:
		print("Project directory not found")

if __name__ == "__main__":
	totalTime = time()
	main()
	totalTime = time() - totalTime
	print ("total time: " + str(totalTime))
	print ("build time: " + str(totalBuildTime))
	print ("usefull time ratio: " + str(totalBuildTime / totalTime))
