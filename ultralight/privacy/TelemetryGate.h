#ifndef ULTRALIGHT_PRIVACY_TELEMETRY_GATE_H_
#define ULTRALIGHT_PRIVACY_TELEMETRY_GATE_H_

#include <string>

namespace ultralight {
namespace privacy {

// Centralized privacy gate for all browser-originated network requests.
class TelemetryGate {
 public:
  enum class RequestReason {
    USER_INITIATED,
    WEBSITE_ORIGINATED,
    BROWSER_UPDATE_CHECK,
    EXTENSION_UPDATE_CHECK,
    FILTER_LIST_UPDATE,
    UNKNOWN_TELEMETRY
  };

  // Evaluates a network request and determines if it should be allowed based on
  // the strict local-first privacy policy.
  static bool IsRequestAllowed(const std::string& url, RequestReason reason);

 private:
  // Checks if the URL matches any known telemetry or phone-home endpoints.
  static bool IsKnownTelemetryEndpoint(const std::string& url);
};

}  // namespace privacy
}  // namespace ultralight

#endif  // ULTRALIGHT_PRIVACY_TELEMETRY_GATE_H_
