
import py_compile

def configDir():
	for dir in [
				os.getcwd(),
				path.dirname(path.abspath(sys.argv[0]))
				]:
		if path.isfile(path.join(dir, 'config')):
			return dir
	return None

def slOpenFile(filePath, mode):
	if not filePath:
		filePath = "-"

	result = None
	if filePath == "-":
		if mode == 'w':
			result = sys.stdout
		elif mode == 'r':
			result = sys.stdin
	else:
		result = open(filePath, mode)

def importConfiguration(input):
	selfLines = slOpenFile(sys.argv[0], 'r').readlines()
	extensionsStart = 0
	for line in selfLines:
		if line == '_SLMAKE EXTENSIONS BEGIN':
			break
		extensionsStart += 1
	if extensionsStart == len(selfLines):
		raise 5

def exportConfiguration(output):
	pass

def importExtension(identifier, input):
	pass

def removeExtension(identifier):
	pass

def listExtensions(all):
	pass

################################################################################
# _SLMAKE EXTENSIONS BEGIN
# _SLMAKE EXTENSIONS END
################################################################################

def main():
	print("platform: " + slPlatform())
	#	selfDirPath = os.path.dirname(path.abspath(argv[0]))
	projectDir = configDir()
	if projectDir:
		fileInput = __builtins__.open(path.join(projectDir, 'config'))
		builder = CBuilder(projectDir)
		parser = OptionParser()
		parser.add_option("--importExtension", dest="importExtension")
		parser.add_option("--removeExtension", dest="removeExtension")
		parser.add_option("--listExtensions", dest="listExtensions")
		parser.add_option("--targetPlatform", dest="targetPlatform")
		(options, args) = parser.parse_args()
		builder.globalDefinitions['targetPlatform'] = 'iosSimulator';
		parser = CParser()
		parser.parseFileInputToBuilder(fileInput, builder)
		builder.performBuild()
	else:
		print("Project directory not found")
	print(sys.argv[0])
	py_compile.compile(sys.argv[0])

if __name__ == "__main__":
	totalTime = time()
	main()
	totalTime = time() - totalTime
	print ("total time: " + str(totalTime))
	print ("build time: " + str(totalBuildTime))
	print ("usefull time ratio: " + str(totalBuildTime / totalTime))
