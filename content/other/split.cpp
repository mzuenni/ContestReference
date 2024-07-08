// Zerlegt s anhand aller Zeichen in delim (verändert s).
vector<string> split(string& s, string delim) {
	vector<string> result; char *token;
	token = strtok(s.data(), delim.c_str());
	while (token != nullptr) {
		result.emplace_back(token);
		token = strtok(nullptr, delim.c_str());
	}
	return result;
}
