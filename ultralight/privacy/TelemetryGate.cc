#include "TelemetryGate.h"

namespace ultralight {
namespace privacy {

bool TelemetryGate::IsRequestAllowed(const std::string& url, RequestReason reason) {
  // If we identify it as telemetry, block immediately.
  if (IsKnownTelemetryEndpoint(url)) {
    return false;
  }

  // Enforce strict reason-based access
  switch (reason) {
    case RequestReason::USER_INITIATED:
    case RequestReason::WEBSITE_ORIGINATED:
    case RequestReason::BROWSER_UPDATE_CHECK:
    case RequestReason::EXTENSION_UPDATE_CHECK:
    case RequestReason::FILTER_LIST_UPDATE:
      return true; // Explicitly allowed actions
    case RequestReason::UNKNOWN_TELEMETRY:
    default:
      return false; // Block everything else (Zero Background Phone-Home rule)
  }
}

bool TelemetryGate::IsKnownTelemetryEndpoint(const std::string& url) {
  // Hardcoded denylist for common analytics endpoints embedded in chromium
  if (url.find("google-analytics.com") != std::string::npos ||
      url.find("clients2.google.com/service/update2") != std::string::npos ||
      url.find("metrics.icloud.com") != std::string::npos ||
      url.find("crash") != std::string::npos ||
      url.find("telemetry") != std::string::npos) {
    return true;
  }
  return false;
}

}  // namespace privacy
}  // namespace ultralight
