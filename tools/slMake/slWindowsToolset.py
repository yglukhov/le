class CWindowsToolset(CToolset):
	def ratingForBuildEnvironment(self):
		return 0

availableToolsets.append(CWindowsToolset)
