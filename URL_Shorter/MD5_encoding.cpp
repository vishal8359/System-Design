// #include <iostream>
// #include <unordered_map>
// #include <string>
// #include <sstream>
// #include <iomanip>
// // #include <openssl/md5.h>   

// using namespace std;

// class URLShortenerMD5 {
// private:
//     unordered_map<string, string> shortToLong;  // short -> long
//     unordered_map<string, string> longToShort;  // long -> short

//     // Helper: compute MD5 hash
//     string md5(const string& input) {
//         unsigned char digest[MD5_DIGEST_LENGTH];
//         MD5((unsigned char*)input.c_str(), input.size(), digest);

//         stringstream ss;
//         for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
//             ss << hex << setw(2) << setfill('0') << (int)digest[i];
//         }
//         return ss.str();
//     }

//     // Generate short key from MD5 (take first 6 chars)
//     string generateKey(const string& url) {
//         string hash = md5(url);
//         return hash.substr(0, 6);  // First 6 hex chars
//     }

// public:
//     // Shorten a URL
//     string shortenURL(const string& longURL) {
//         if (longToShort.find(longURL) != longToShort.end()) {
//             return longToShort[longURL]; // Already exists
//         }

//         string key = generateKey(longURL);
//         string shortURL = "http://sho.rt/" + key;

//         // Handle collision (rare for demo, but check anyway)
//         if (shortToLong.find(key) != shortToLong.end() && shortToLong[key] != longURL) {
//             shortURL = "Error: Collision occurred!";
//         } else {
//             shortToLong[key] = longURL;
//             longToShort[longURL] = shortURL;
//         }
//         return shortURL;
//     }

//     // Expand short URL back to long URL
//     string expandURL(const string& shortURL) {
//         string prefix = "http://sho.rt/";
//         string key = shortURL.substr(prefix.size());

//         if (shortToLong.find(key) == shortToLong.end()) {
//             return "Error: Short URL not found!";
//         }
//         return shortToLong[key];
//     }
// };

// // ------------------ Demo ------------------
// int main() {
//     URLShortenerMD5 service;

//     string long1 = "https://openai.com/research/";
//     string long2 = "https://www.geeksforgeeks.org/low-level-design-of-url-shortening-service/";

//     string short1 = service.shortenURL(long1);
//     string short2 = service.shortenURL(long2);

//     cout << "Original: " << long1 << "\nShortened: " << short1 << "\n\n";
//     cout << "Original: " << long2 << "\nShortened: " << short2 << "\n\n";

//     cout << "Expanding " << short1 << " -> " << service.expandURL(short1) << "\n";
//     cout << "Expanding " << short2 << " -> " << service.expandURL(short2) << "\n";

//     return 0;
// }
