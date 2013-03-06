

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

outputFile = 'slMake'

import sys, os, shutil

if __name__ == '__main__':
	pathname = os.path.dirname(sys.argv[0])
	outputContent = ''
	for i in index:
		content = open(os.path.join(pathname, i + '.py'), 'r').read()
		outputContent += content
		exec(compile(content, i, 'exec'))
	output = open(os.path.join(pathname, outputFile + '.py'), 'w')
	output.write(outputContent)
	output.close()
