class CSettingsExpander:
	def __init__(self, settings, additionalDefinitions):
		self.sourceSettings = settings
		self.destSettings = {}
		self.additionalDefinitions = additionalDefinitions
		self.expand()

	def expandedValueForKey(self, key):
		value = self.destSettings.get(key)
		if not value:
			value = self.sourceSettings.get(key)
			if value:
				value = self.expandValue(value)
				self.destSettings[key] = value
			else:
				value = self.additionalDefinitions.get(key)
		return value

	def expandStringValue(self, value):
		pos = value.rfind('$')
		while pos != -1:
			pos += 1
			closingSymbol = None
			if value[pos] == '(':
				closingSymbol = ')'
			elif value[pos] == '{':
				closingSymbol = '}'

			end = -1
			if closingSymbol:
				end = value.find(closingSymbol, pos)
			else:
				if value[pos] in string.ascii_letters:
					end = pos
					while end < len(value):
						if value[end] not in string.ascii_letters and value[end] not in string.digits:
							break
						end += 1

			if end != -1:
				key = None
				suffix = None
				if closingSymbol:
					key = value[pos + 1:end]
					suffix = value[end + 1:]
				else:
					key = value[pos:end]
					suffix = value[end:]
				expandedValue = self.expandedValueForKey(key)
				if expandedValue:
					value = value[:pos - 1] + expandedValue + suffix
			pos = value.rfind('$', 0, pos - 1)
		return value

	def expandValue(self, value):
		if slIsString(value):
			return self.expandStringValue(value)
		elif isinstance(value, list):
			return [ self.expandValue(i) for i in value ]
		return value

	def expand(self):
		for key in self.sourceSettings:
			self.expandedValueForKey(key)
