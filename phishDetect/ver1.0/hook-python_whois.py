from PyInstaller.utils.hooks import collect_submodules, collect_data_files

# Collect all submodule from python-whois
hiddenimports = collect_submodules('whois')

# Collect any non-Python files (if exist) within the python-whois package
datas = collect_data_files('whois')