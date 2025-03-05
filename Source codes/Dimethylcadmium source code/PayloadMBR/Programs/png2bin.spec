# -*- mode: python -*-
import sys
a = Analysis(
	['png2bin.py'],
	pathex=[''],
	hiddenimports=[],
	hookspath=None,
	runtime_hooks=None
)

for d in a.datas:
  if 'pyconfig' in d[0]: 
	a.datas.remove(d)
	break

pyz = PYZ(a.pure)
exe = EXE(
	pyz,
	a.scripts,
	a.binaries + []
	if sys.platform == 'win32' else a.binaries,
	a.zipfiles,
	a.datas,
	name='png2bin.exe',
	debug=False,
	strip=None,
	upx=False,
	console=True
)