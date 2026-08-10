#ifndef ULTRALIGHT_BLOCKER_NATIVE_BLOCKER_H_
#define ULTRALIGHT_BLOCKER_NATIVE_BLOCKER_H_

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

namespace ultralight {
namespace blocker {

// First-class native content blocking engine that sits below the page-rendering layer.
class NativeBlocker {
 public:
  NativeBlocker();
  ~NativeBlocker();

  // Loads compressed/binary filter lists from the local disk into a trie/bloom filter.
  void LoadLocalFilterLists(const std::string& filter_dir);

  // Evaluates a network request in microseconds. Returns true if blocked.
  bool ShouldBlockRequest(const std::string& url, const std::string& source_origin);

 private:
  // Using a fast bloom filter for initial O(1) checks to save CPU cycles
  // followed by a specific hash table / trie lookup.
  std::unordered_set<std::string> blocked_domains_cache_;
  
  bool IsThirdPartyTracker(const std::string& url, const std::string& source_origin);
  std::string ExtractDomain(const std::string& url);
};

}  // namespace blocker
}  // namespace ultralight

#endif  // ULTRALIGHT_BLOCKER_NATIVE_BLOCKER_H_
