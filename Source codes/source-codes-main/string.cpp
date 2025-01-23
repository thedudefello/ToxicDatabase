LPCWSTR unicode() {
	wchar_t uString[32];
	for (int len = 0; len < 32; len++) {
		uString[len] = (wchar_t)rand () % 256 + 1;
	}
	return uString;
}
// rewritten by Tubercomiosis (me)
