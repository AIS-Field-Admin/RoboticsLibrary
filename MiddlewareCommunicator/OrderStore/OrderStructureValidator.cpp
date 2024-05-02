#include "pch.h"
#include "OrderStructureValidator.h"

#include "OrderStructureValidator.h"

bool OrderStructureValidator::Validate(const std::string& orderJson) {
    nlohmann::json json;

    try {
        json = nlohmann::json::parse(orderJson);
    }
    catch (nlohmann::json::parse_error&) {
        return false; // Not valid JSON
    }

    if (!json.is_object()) {
        return false; // JSON is not an object
    }

    if (!json.contains("OrderId") || !json["OrderId"].is_number()) {
        return false; // Missing OrderId or OrderId is not a number
    }

    if (!json.contains("SenderModule") || !json["SenderModule"].is_string()) {
        return false; // Missing SenderModule or SenderModule is not a string
    }

    if (!json.contains("RecipientModule") || !json["RecipientModule"].is_string()) {
        return false; // Missing RecipientModule or RecipientModule is not a string
    }

    if (!json.contains("OrderType") || !json["OrderType"].is_string()) {
        return false; // Missing OrderType or OrderType is not a string
    }

    if (!json.contains("OrderParameters") || !json["OrderParameters"].is_string()) {
        return false; // Missing OrderParameters or OrderParameters is not a string
    }

    // Add additional structure validations here if necessary

    return true; // JSON structure is valid
}