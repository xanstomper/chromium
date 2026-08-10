#ifndef ULTRALIGHT_PERFORMANCE_TAB_SUSPENDER_H_
#define ULTRALIGHT_PERFORMANCE_TAB_SUSPENDER_H_

#include <vector>
#include <string>

namespace ultralight {
namespace performance {

// Aggressively suspends background tabs to meet memory targets.
class TabSuspender {
 public:
  TabSuspender();
  ~TabSuspender();

  // Evaluates all active WebContents to determine if they should be frozen or discarded.
  void CheckAndSuspendIdleTabs();

  // Prevents suspension for specific critical tabs (e.g., active audio, downloads)
  void ExemptTabFromSuspension(int tab_id, const std::string& reason);

 private:
  std::vector<int> exempt_tab_ids_;
  const int kIdleTimeoutSeconds = 300; // 5 minutes aggressive suspension
  
  bool IsTabPlayingAudio(int tab_id);
  bool IsTabPinned(int tab_id);
  void DiscardTabContents(int tab_id);
};

}  // namespace performance
}  // namespace ultralight

#endif  // ULTRALIGHT_PERFORMANCE_TAB_SUSPENDER_H_
