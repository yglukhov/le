class CLogger:
	def log(self, tag, message, file, line):
		print(tag + ": " + message)
		if file:
			print(file + ": " + str(line))
		sys.stdout.flush()

	def logError(self, message, file = None, line = 0):
		self.log("Error", message, file, line)

	def logWarning(self, message, file = None, line = 0):
		self.log("Warning", message, file, line)

	def logInfo(self, message, file = None, line = 0):
		self.log("Info", message, file, line)

	def logDebug(self, message, file = None, line = 0):
		self.log("Debug", message, file, line)

	def logStartBuildTarget(self, targetName, configuration):
		self.logInfo('Building target "' + targetName + '" with configuration "' + configuration + '"')

log = CLogger()
