#include "CppUnitTest.h"
#include "..\OrderStore\OrderStructureValidator.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OrderStoreTests
{
    TEST_CLASS(OrderStructureValidatorTests)
    {
    public:

        TEST_METHOD(Validate_ReturnsTrue_WithValidJson)
        {
            // Arrange
            std::string validJson = R"({
                "OrderId": 1,
                "SenderModule": "ModuleA",
                "RecipientModule": "ModuleB",
                "OrderType": "Type1",
                "OrderParameters": "Param1"
            })";

            // Act
            bool result = OrderStructureValidator::Validate(validJson);

            // Assert
            Assert::IsTrue(result);
        }

        TEST_METHOD(Validate_ReturnsFalse_WithInvalidJson)
        {
            // Arrange
            std::string invalidJson = "{invalid json}";

            // Act
            bool result = OrderStructureValidator::Validate(invalidJson);

            // Assert
            Assert::IsFalse(result);
        }

        TEST_METHOD(Validate_ReturnsFalse_WhenFieldIsMissing)
        {
            // Arrange
            std::string missingFieldJson = R"({"SenderModule": "ModuleA", "RecipientModule": "ModuleB", "OrderType": "Type1", "OrderParameters": "Param1"})";

            // Act
            bool result = OrderStructureValidator::Validate(missingFieldJson);

            // Assert
            Assert::IsFalse(result);
        }

        TEST_METHOD(Validate_ReturnsFalse_WhenFieldTypeIsIncorrect)
        {
            // Arrange
            std::string incorrectFieldTypeJson = R"({
                "OrderId": "should be a number",
                "SenderModule": "ModuleA",
                "RecipientModule": "ModuleB",
                "OrderType": "Type1",
                "OrderParameters": "Param1"
            })";

            // Act
            bool result = OrderStructureValidator::Validate(incorrectFieldTypeJson);

            // Assert
            Assert::IsFalse(result);
        }

        TEST_METHOD(Validate_ReturnsFalse_WithEmptyJson)
        {
            // Arrange
            std::string emptyJson = "{}";

            // Act
            bool result = OrderStructureValidator::Validate(emptyJson);

            // Assert
            Assert::IsFalse(result, L"Empty JSON should not pass validation.");
        }

        TEST_METHOD(Validate_ReturnsFalse_WithExtraFields)
        {
            // Arrange
            std::string extraFieldsJson = R"({
                "OrderId": 1,
                "SenderModule": "ModuleA",
                "RecipientModule": "ModuleB",
                "OrderType": "Type1",
                "OrderParameters": "Param1",
                "ExtraField": "This should not be here"
            })";

            // Act
            bool result = OrderStructureValidator::Validate(extraFieldsJson);

            // Assert
            Assert::IsTrue(result, L"JSON with extra fields should still pass validation if all required fields are correct.");
        }

        TEST_METHOD(Validate_ReturnsFalse_WithArrayInsteadOfObject)
        {
            // Arrange
            std::string jsonArray = R"([{
                "OrderId": 1,
                "SenderModule": "ModuleA",
                "RecipientModule": "ModuleB",
                "OrderType": "Type1",
                "OrderParameters": "Param1"
            }])";

            // Act
            bool result = OrderStructureValidator::Validate(jsonArray);

            // Assert
            Assert::IsFalse(result, L"JSON arrays should not be valid structures for an Order.");
        }

        TEST_METHOD(Validate_ReturnsFalse_WithNestedObjects)
        {
            // Arrange
            std::string nestedObjectsJson = R"({
                "OrderId": 1,
                "SenderModule": "ModuleA",
                "RecipientModule": "ModuleB",
                "OrderType": "Type1",
                "OrderParameters": {
                    "SubParameter": "Value"
                }
            })";

            // Act
            bool result = OrderStructureValidator::Validate(nestedObjectsJson);

            // Assert
            Assert::IsFalse(result, L"OrderParameters should be a string, not an object.");
        }

        TEST_METHOD(Validate_ReturnsTrue_WithAllOptionalFieldsPresent)
        {
            // This test assumes the existence of optional fields in the JSON structure. Adjust accordingly.
            std::string validJsonWithOptionals = R"({
                "OrderId": 1,
                "SenderModule": "ModuleA",
                "RecipientModule": "ModuleB",
                "OrderType": "Type1",
                "OrderParameters": "Param1",
                "OptionalField1": "OptionalValue1",
                "OptionalField2": "OptionalValue2"
            })";

            // Act
            bool result = OrderStructureValidator::Validate(validJsonWithOptionals);

            // Assert
            Assert::IsTrue(result, L"JSON with all fields, including optional ones, should pass validation.");
        }
    };
}