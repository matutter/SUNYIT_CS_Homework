int _secret_alert_variable_def = 1;
void alert(std::string s) {
	if(_secret_alert_variable_def) std::cout << s << endl << flush;
}

void alert(std::string s, int i, std::string s2) {
	if(_secret_alert_variable_def) std::cout << s<<i<<s2 << endl << flush;
}