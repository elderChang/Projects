# -*- mode: python ; coding: utf-8 -*-
import sys ; sys.setrecursionlimit(300000)

a = Analysis(
    ['whois_web.py','DATAofRF.py','LSTM_Single_Input.py','RandomF.py','WebClassification.py'],
    pathex=[],
    binaries=[('templates','templates')],
    datas=[(r'C:\Users\kookls\AppData\Local\Programs\Python\Python312\Lib\site-packages\whois\data\public_suffix_list.dat',r'whois/data')],
    hiddenimports=['whois','python-whois'],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
) 
pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    [],
    exclude_binaries=True,
    name='whois_web',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=True,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)
coll = COLLECT(
    exe,
    a.binaries,
    a.datas,
    strip=False,
    upx=True,
    upx_exclude=[],
    name='whois_web',
)
