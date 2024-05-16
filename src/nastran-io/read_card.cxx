
#include "read_card.hxx"

#include <fstream>
#include <read_util.hxx>
#include <string>
#include <vector>

namespace NastranIO {

namespace {

auto checkCardKey(std::string const &key, std::string const &line,
                  std::vector<Card> &cards) -> bool {
  auto const keySize = key.size();
  if (line.substr(0, keySize) == key) {
    auto newCard = Card{};
    newCard.key = key;
    newCard.lines.emplace_back(line);
    newCard.lastLineEnd = line.substr(72, 8);
    cards.emplace_back(newCard);
    return true;
  } else if (!cards.empty() && cards.back().key == key &&
             cards.back().lastLineEnd == line.substr(0, 8) &&
             line.substr(0, 2) == "*C") {
    cards.back().lines.emplace_back(line);
    cards.back().lastLineEnd = line.substr(72, 8);
    return true;
  }
  return false;
}

auto parseLine(std::string line, std::vector<Card> &cards) -> bool {
  // Ensure line has minimum size and no \n\r symbol
  formatLine(line);

  // Check key and add to card if positive
  auto result = bool{false};
  result = result ? result : checkCardKey("CBAR", line, cards);
  result = result ? result : checkCardKey("GRID", line, cards);
  result = result ? result : checkCardKey("MAT1", line, cards);
  result = result ? result : checkCardKey("PBAR", line, cards);

  return result;
}

} // namespace

auto parseCards(std::ifstream &file) -> std::vector<Card> {
  auto cards = std::vector<Card>{};

  std::string line;
  while (std::getline(file, line)) {
    parseLine(line, cards);
  }

  return cards;
};

}; // namespace NastranIO
