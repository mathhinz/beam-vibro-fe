#include "read_mat.hxx"

#include <cmath>
#include <cstdint>
#include <mat1.hxx>
#include <optional>
#include <read_util.hxx>
#include <string>
#include <vector>


namespace NastranIO
{

auto readMAT1(std::vector<std::string> &card) -> MAT1
{

    auto newMat = MAT1{};
    std::optional<uint64_t> mid, mcsid;
    std::optional<double_t> e, g, nu, rho, a, tref, ge, st, sc, ss;
    std::string errorDetail;

    try
    {
        //Large Field Format
        if (card[0].substr(0, 5) == "MAT1*" && card.size() == 3)
        {
            convertToInteger(card[0].substr(8, 16), mid);
            convertToDouble(card[0].substr(24, 16), e);
            convertToDouble(card[0].substr(40, 16), g);
            convertToDouble(card[0].substr(56, 16), nu);
            convertToDouble(card[1].substr(8, 16), rho);
            convertToDouble(card[1].substr(24, 16), a);
            convertToDouble(card[1].substr(40, 16), tref);
            convertToDouble(card[1].substr(56, 16), ge);
            convertToDouble(card[2].substr(8, 16), st);
            convertToDouble(card[2].substr(24, 16), sc);
            convertToDouble(card[2].substr(40, 16), ss);
            convertToInteger(card[2].substr(56, 16), mcsid);
        }
        else if (card[0].substr(0, 5) == "MAT1*" && card.size() == 2)
        {
            convertToInteger(card[0].substr(8, 16), mid);
            convertToDouble(card[0].substr(24, 16), e);
            convertToDouble(card[0].substr(40, 16), g);
            convertToDouble(card[0].substr(56, 16), nu);
            convertToDouble(card[1].substr(8, 16), rho);
            convertToDouble(card[1].substr(24, 16), a);
            convertToDouble(card[1].substr(40, 16), tref);
            convertToDouble(card[1].substr(56, 16), ge);
        }
        //Small Field Format
        else if (card[0].substr(0, 4) == "MAT1" && card.size() == 2)
        {
            convertToInteger(card[0].substr(8, 8), mid);
            convertToDouble(card[0].substr(16, 8), e);
            convertToDouble(card[0].substr(24, 8), g);
            convertToDouble(card[0].substr(32, 8), nu);
            convertToDouble(card[0].substr(40, 8), rho);
            convertToDouble(card[0].substr(48, 8), a);
            convertToDouble(card[0].substr(56, 8), tref);
            convertToDouble(card[0].substr(64, 8), ge);
            convertToDouble(card[1].substr(8, 8), st);
            convertToDouble(card[1].substr(16, 8), sc);
            convertToDouble(card[1].substr(24, 8), ss);
            convertToInteger(card[1].substr(32, 8), mcsid);
        }
        else if (card[0].substr(0, 4) == "MAT1" && card.size() == 1)
        {
            convertToInteger(card[0].substr(8, 8), mid);
            convertToDouble(card[0].substr(16, 8), e);
            convertToDouble(card[0].substr(24, 8), g);
            convertToDouble(card[0].substr(32, 8), nu);
            convertToDouble(card[0].substr(40, 8), rho);
            convertToDouble(card[0].substr(48, 8), a);
            convertToDouble(card[0].substr(56, 8), tref);
            convertToDouble(card[0].substr(64, 8), ge);
        }

        // Mandatory fields
        if (mid.has_value() && e.has_value() &&
            (g.has_value() || nu.has_value()) && rho.has_value())
        {
            if (nu.has_value())
            {
                g = e.value() / (2 * (1 + nu.value()));
            }
            newMat = {mid.value(), e.value(), g.value(), rho.value()};

            // Optional fields
            if (nu.has_value())
            {
                // Value of Nu ignored as it is constrained
            }
            if (a.has_value())
            {
                newMat.setA(a.value());
            }
            if (tref.has_value())
            {
                newMat.setTREF(tref.value());
            }
            if (ge.has_value())
            {
                newMat.setGE(ge.value());
            }
            if (st.has_value())
            {
                newMat.setST(st.value());
            }
            if (sc.has_value())
            {
                newMat.setSC(sc.value());
            }
            if (ss.has_value())
            {
                newMat.setSS(ss.value());
            }
            if (mcsid.has_value())
            {
                newMat.setMCSID(mcsid.value());
            }
        }
        else
        {
            errorDetail =
                "Check for wrong card size or empty mandatory fields: "
                "MID, E, G or RHO";
        }
    }
    catch (...)
    {
        errorDetail = "String to double/integer conversion failed";
    }

    if (newMat.isEmpty())
    {
        throw CardOutOfFormatException(
            "One or more MAT1*/MAT inputs are incorrectly formated - " +
            errorDetail);
    }

    return newMat;
};


}; // namespace NastranIO
