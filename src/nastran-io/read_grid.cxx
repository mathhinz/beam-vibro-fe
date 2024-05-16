#include "read_grid.hxx"

#include <cmath>
#include <cstdint>
#include <grid.hxx>
#include <optional>
#include <read_util.hxx>
#include <string>
#include <vector>

namespace NastranIO
{

auto readGRID(std::vector<std::string> &card) -> GRID
{

    auto newGrid = GRID{};
    std::optional<uint64_t> id, cp, ps, seid;
    std::optional<double_t> x, y, z;
    std::optional<int64_t> cd;
    std::string errorDetail;

    try
    {
        //Large Field Format
        if (card[0].substr(0, 5) == "GRID*" && card.size() == 2)
        {
            convertToInteger(card[0].substr(8, 16), id);
            convertToInteger(card[0].substr(24, 16), cp);
            convertToDouble(card[0].substr(40, 16), x);
            convertToDouble(card[0].substr(56, 16), y);
            convertToDouble(card[1].substr(8, 16), z);
            convertToInteger(card[1].substr(24, 16), cd);
            convertToInteger(card[1].substr(40, 16), ps);
            convertToInteger(card[1].substr(56, 16), seid);
        }
        //Small Field Format
        else if (card[0].substr(0, 4) == "GRID" && card.size() == 1)
        {
            convertToInteger(card[0].substr(8, 8), id);
            convertToInteger(card[0].substr(16, 8), cp);
            convertToDouble(card[0].substr(24, 8), x);
            convertToDouble(card[0].substr(32, 8), y);
            convertToDouble(card[0].substr(40, 8), z);
            convertToInteger(card[0].substr(48, 8), cd);
            convertToInteger(card[0].substr(56, 8), ps);
            convertToInteger(card[0].substr(64, 8), seid);
        }

        // Mandatory fields
        if (id.has_value() && x.has_value() && y.has_value() && z.has_value())
        {
            newGrid = {id.value(), x.value(), y.value(), z.value()};

            // Optional fields
            if (cp.has_value())
            {
                newGrid.setCP(cp.value());
            }
            if (cd.has_value())
            {
                newGrid.setCD(cd.value());
            }
            if (ps.has_value())
            {
                newGrid.setPS(ps.value());
            }
            if (seid.has_value())
            {
                newGrid.setSEID(seid.value());
            }
        }
        else
        {
            errorDetail =
                "Check for wrong card size or empty mandatory fields: "
                "ID, X, Y or Z";
        }
    }
    catch (...)
    {
        errorDetail = "String to double/integer conversion failed";
    }

    if (newGrid.isEmpty())
    {
        throw CardOutOfFormatException(
            "One or more GRID*/GRID inputs are not correctly formated - " +
            errorDetail);
    }

    return newGrid;
};

}; // namespace NastranIO
