class CFilesCollector:
	def __init__(self):
		self.collectedSources = {}
		self.collectedHeaders = {}
		self.sourceExtensions = ['cpp', 'c', 'c++', 'cp']
		if sys.platform == 'darwin':
			self.sourceExtensions.append('m')
			self.sourceExtensions.append('mm')

	def collectHeaders(self, roots):
		return self.collectFilesWithExtensions(roots, ['h'], self.collectedSources)

	def collectSources(self, roots):
		return self.collectFilesWithExtensions(roots, self.sourceExtensions, self.collectedSources)

	def collectAllFiles(self, roots):
		return self.collectFiles(roots, lambda x: True, {})

	def collectFilesWithExtensions(self, roots, extensions, existingRoots):
		dotExtensions = ['.' + ext for ext in extensions]
		def predicate(x):
			for extension in dotExtensions:
				if x.endswith(extension):
					return True
			return False
		return self.collectFiles(roots, predicate, existingRoots)

	def collectFiles(self, roots, predicate, existingRoots):
		result = []
		for root in roots:
			if root in existingRoots:
				result.append([root, existingRoots[root]])
			else:
				newList = self.collectFilesInRoot(root, predicate)
				existingRoots[root] = newList
				result.append([root, newList])
		return result

	def collectFilesInRoot(self, srcroot, predicate):
		result = []
		for root, dirs, files in os.walk(srcroot):
			dirs[:] = [d for d in dirs if d not in ('.svn', 'CVS', '.hg', '.git')]
			for file in files:
				if file != '.DS_Store' and predicate(file):
					result.append(path.join(root[len(srcroot) + 1:], file))
		return result
