#include <bits/stdc++.h>
using namespace std;

class URLShortener {
private:
    // Counter for generating unique IDs
    long long counter;
    
    // Map for storing short -> long mappings
    unordered_map<string, string> shortToLong;
    unordered_map<string, string> longToShort;

    const string base62Chars = 
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Convert numeric ID -> Base62 encoded string
    string encodeBase62(long long num) {
        if (num == 0) return "0";
        string result;
        while (num > 0) {
            result.push_back(base62Chars[num % 62]);
            num /= 62;
        }
        reverse(result.begin(), result.end());
        return result;
    }

    // Decode Base62 string -> numeric ID (not used much here but useful)
    long long decodeBase62(const string &s) {
        long long num = 0;
        for (char c : s) {
            if ('0' <= c && c <= '9')
                num = num * 62 + (c - '0');
            else if ('a' <= c && c <= 'z')
                num = num * 62 + (c - 'a' + 10);
            else if ('A' <= c && c <= 'Z')
                num = num * 62 + (c - 'A' + 36);
        }
        return num;
    }

public:
    URLShortener() : counter(1) {}

    // Encode long URL -> short URL
    string shortenURL(const string &longURL) {
        // If already exists, return existing short URL
        if (longToShort.find(longURL) != longToShort.end()) {
            return longToShort[longURL];
        }

        // Generate new short URL
        string shortKey = encodeBase62(counter++);
        string shortURL = "http://sho.rt/" + shortKey;

        // Save mapping
        shortToLong[shortKey] = longURL;
        longToShort[longURL] = shortURL;

        return shortURL;
    }

    // Decode short URL -> original long URL
    string expandURL(const string &shortURL) {
        // Extract key (remove domain prefix)
        string prefix = "http://sho.rt/";
        string key = shortURL.substr(prefix.size());

        if (shortToLong.find(key) == shortToLong.end()) {
            return "Error: Short URL not found!";
        }
        return shortToLong[key];
    }
};

int main() {
    URLShortener service;

    string longURL1 = "https://www.geeksforgeeks.org/low-level-design-of-url-shortening-service/";
    string longURL2 = "https://www.openai.com/research/";

    // Shorten URLs
    string short1 = service.shortenURL(longURL1);
    string short2 = service.shortenURL(longURL2);

    cout << "Original: " << longURL1 << "\nShortened: " << short1 << "\n\n";
    cout << "Original: " << longURL2 << "\nShortened: " << short2 << "\n\n";

    // Expand back
    cout << "Expanding " << short1 << " -> " << service.expandURL(short1) << "\n";
    cout << "Expanding " << short2 << " -> " << service.expandURL(short2) << "\n";

    return 0;
}
