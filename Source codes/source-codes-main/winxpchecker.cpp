WINBOOL CheckForWindowsXP() {
	OSVERSIONINFOA osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	GetVersionExA(&osvi);
	if (osvi.dwMajorVersion == 5) {
		return true;
	}
	return false;
}
// if you skid this, I require you to take down your project that used this
// this rule doesn't apply to my friends, like @SickdowsReal
