mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<long long int> dist(1, 1000000000000000000);
// usage: dist(gen)
