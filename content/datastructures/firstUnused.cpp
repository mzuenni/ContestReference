// Erste natürliche Zahl nicht im set used.
set<int> used;
int unusedCounter = 1;

int get_first_unused() { // Laufzeit: O(log n) amortisiert.
	auto it = used.lower_bound(unusedCounter);
	while (it != used.end() && *it == unusedCounter) {
		it++;
		unusedCounter++;
	}
	used.insert(unusedCounter);
	return unusedCounter++;
}
