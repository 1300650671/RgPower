from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.
src     = Glob('inc/*.h')
src     = Glob('src/*.c')
src     = Glob('src/*.cpp')

if GetDepend('RGPOWER_USING_EXAMPLES'):
	src    += Glob('examples/example_RgPower.c')

path    = [cwd + '/']
path   += [cwd + '/src']

LOCAL_CCFLAGS = ''

group = DefineGroup('RGPOWER', src, depend = ['PKG_USING_AD7746'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')