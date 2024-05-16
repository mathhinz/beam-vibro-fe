#include "read_elem.hxx"

#include <cbar.hxx>
#include <cmath>
#include <cstdint>
#include <optional>
#include <read_util.hxx>
#include <string>
#include <vector>

namespace NastranIO {

auto readCBAR(std::vector<std::string> &card) -> CBAR {
  auto newBar = CBAR{};
  std::optional<uint64_t> eid, pid, ga, gb;
  std::optional<double_t> x1, x2, x3;
  std::string errorDetail;

  try {
    // Large Field Format
    if (card[0].substr(0, 5) == "CBAR*" && card.size() >= 2) {
      convertToInteger(card[0].substr(8, 16), eid);
      convertToInteger(card[0].substr(24, 16), pid);
      convertToInteger(card[0].substr(40, 16), ga);
      convertToInteger(card[0].substr(56, 16), gb);
      convertToDouble(card[1].substr(8, 16), x1);
      convertToDouble(card[1].substr(24, 16), x2);
      convertToDouble(card[1].substr(40, 16), x3);
    }
    // Small Field Formats
    else if (card[0].substr(0, 4) == "CBAR" && card.size() >= 1) {
      convertToInteger(card[0].substr(8, 8), eid);
      convertToInteger(card[0].substr(16, 8), pid);
      convertToInteger(card[0].substr(24, 8), ga);
      convertToInteger(card[0].substr(32, 8), gb);
      convertToDouble(card[0].substr(40, 8), x1);
      convertToDouble(card[0].substr(48, 8), x2);
      convertToDouble(card[0].substr(56, 8), x3);
    }
    // Mandatory fields
    if (eid.has_value() && pid.has_value() && ga.has_value() &&
        gb.has_value() && x1.has_value() && x2.has_value() && x3.has_value()) {

      newBar = {eid.value(),
                pid.value(),
                ga.value(),
                gb.value(),
                {x1.value(), x2.value(), x3.value()}};

    } else {
      errorDetail = "Check for wrong card size or empty mandatory fields: "
                    "EID, PID, GA, GB or X";
    }
  } catch (...) {
    errorDetail = "String to double/integer conversion failed";
  }

  if (newBar.isEmpty()) {
    throw CardOutOfFormatException(
        "One or more CBAR*/CBAR inputs are not correctly formated - " +
        errorDetail);
  }

  return newBar;
};

}; // namespace NastranIO
