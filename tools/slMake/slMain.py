

index = [ 'slHeader',
		 
		 'slDependencyGraph',
		 'slLogger',

		 'slFilesCollector',

		 'slToolset',
		 'slGCCToolset',
		 'slMacOSXToolset',
		 'slMacOSPlatformFinder',
		 'slWindowsToolset',

		 'slSettingsExpander',

		 'slBuilder',
		 'slParser',
		 'slMakeMain' ]

if __name__ == '__main__':
	for i in index:
		execfile(i + '.py')
