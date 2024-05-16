#pragma once
#include <cstdint>
#include <exception>
#include <optional>
#include <string>
#include <string_view>

namespace NastranIO
{

class CardOutOfFormatException : public std::exception
{
public:
    CardOutOfFormatException(std::string_view _message) : message(_message){};
    std::string message;

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

template <typename T>
auto convertToInteger(std::string_view str, std::optional<T> &val) -> void
{
    val = std::nullopt;
    if (str.find_first_not_of(' ') != std::string::npos)
    {
        val = static_cast<T>(std::stoi(str.data()));
    };
}

template <typename T>
auto convertToDouble(std::string_view str, std::optional<T> &val) -> void
{
    val = std::nullopt;
    if (str.find_first_not_of(' ') != std::string::npos)
    {
        auto expPos = str.find_last_of("+-");
        if (0 < expPos && expPos != std::string::npos &&
            (isdigit(str[expPos - 1]) || str[expPos - 1] == '.'))
        {
            std::string sciStr = str.data();
            sciStr.replace(expPos, 1, std::string("e") + sciStr[expPos]);
            val = static_cast<T>(std::stod(sciStr.data()));
        }
        else
        {
            val = static_cast<T>(std::stod(str.data()));
        }
    };
}

auto formatLine(std::string &line, uint64_t lineSize = 80) -> void;

} // namespace NastranIO