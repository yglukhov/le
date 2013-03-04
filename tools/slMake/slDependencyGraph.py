class CDependencyGraph:
	def __init__(self):
		self.mDeps = dict()

	def objectDependsOn(self, object, dependency):
		if object == dependency:
			return True
		for value in self.mDeps.get(object, []):
			if self.objectDependsOn(value, dependency):
				return True
		return False

	def addDependenciesForObject(self, dependencies, object):
		for dependency in dependencies:
			self.addDependencyForObject(dependency, object)

	def addDependencyForObject(self, dependency, object):
		if self.objectDependsOn(object, dependency):
			return False
		if object not in self.mDeps:
			self.mDeps[object] = set()
		self.mDeps[object].add(dependency)

	def allDependenciesForObject(self, object):
		result = set([object])
		self._collectDepsForObject(object, result)
		return result

	def allDependenciesAndObjects(self):
		result = set()
		for obj in self.mDeps:
			result.add(obj)
			result |= self.mDeps[obj]
		return result;

	def unwrappedForObject(self, object):
		return self._unwrappedForObjectsAndDependencies(self.allDependenciesForObject(object))

	def unwrapped(self):
		return self._unwrappedForObjectsAndDependencies(self.allDependenciesAndObjects())


	def _unwrappedForObjectsAndDependencies(self, allObjects):
		orderedResult = list()
		result = set();
		while len(allObjects):
			for it in allObjects:
				add = False
				if it in self.mDeps:
					if self.mDeps[it] <= result:
						add = True
				else:
					add = True
				if add:
					result.add(it)
					orderedResult.append(it)
					allObjects.remove(it)
					break
		return orderedResult

	def _collectDepsForObject(self, object, result):
		for it in self.mDeps.get(object, []):
			result.add(it)
			self._collectDepsForObject(it, result)
