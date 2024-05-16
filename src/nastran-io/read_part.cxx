#include "read_part.hxx"

#include <cmath>
#include <cstdint>
#include <optional>
#include <pbar.hxx>
#include <read_util.hxx>
#include <string>
#include <vector>

namespace NastranIO {

auto readPBAR(std::vector<std::string> &card) -> PBAR {
  auto newPBar = PBAR{};
  std::optional<uint64_t> pid, mid;
  std::optional<double_t> a, i1, i2, j;

  std::string errorDetail;

  try {
    // Large Field Format
    if (card[0].substr(0, 5) == "PBAR*" && card.size() >= 2) {
      convertToInteger(card[0].substr(8, 16), pid);
      convertToInteger(card[0].substr(24, 16), mid);
      convertToDouble(card[0].substr(40, 16), a);
      convertToDouble(card[0].substr(56, 16), i1);
      convertToDouble(card[1].substr(8, 16), i2);
      convertToDouble(card[1].substr(24, 16), j);
    }
    // Small Field Format
    else if (card[0].substr(0, 4) == "PBAR" && card.size() >= 1) {
      convertToInteger(card[0].substr(8, 8), pid);
      convertToInteger(card[0].substr(16, 8), mid);
      convertToDouble(card[0].substr(24, 8), a);
      convertToDouble(card[0].substr(32, 8), i1);
      convertToDouble(card[0].substr(40, 8), i2);
      convertToDouble(card[0].substr(48, 8), j);
    }

    // Mandatory fields
    if (pid.has_value() && mid.has_value() &&
        (a.has_value() || i1.has_value()) && i2.has_value() && j.has_value()) {
      newPBar = {pid.value(), mid.value(), a.value(),
                 i1.value(),  i2.value(),  j.value()};

    } else {
      errorDetail = "Check for wrong card size or empty mandatory fields: "
                    "PID, MID, A, I1, I2 or J";
    }
  } catch (...) {
    errorDetail = "String to double/integer conversion failed";
  }

  if (newPBar.isEmpty()) {
    throw CardOutOfFormatException(
        "One or more PBAR*/PBAR inputs are not correctly formated - " +
        errorDetail);
  }

  return newPBar;
};

}; // namespace NastranIO
