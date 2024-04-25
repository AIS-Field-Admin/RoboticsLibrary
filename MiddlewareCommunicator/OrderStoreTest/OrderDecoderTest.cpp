#include "CppUnitTest.h"
#include "..\OrderStore\OrderDecoder.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OrderStoreTests
{
    TEST_CLASS(OrderDecoderTests)
    {
    public:

        TEST_METHOD(DecodeValidOrder)
        {
            // Arrange
            std::string validJson = R"({
                                        "OrderId": 123,
                                        "SenderModule": "ModuleA",
                                        "RecipientModule": "ModuleB",
                                        "OrderType": "Type1",
                                        "OrderParameters": "Param1"
                                       })";

            // Act
            Order order = OrderDecoder::DecodeOrder(validJson);

            // Assert
            Assert::AreEqual(123, order.OrderId);
            Assert::AreEqual(std::string("ModuleA"), order.SenderModule);
            Assert::AreEqual(std::string("ModuleB"), order.RecipientModule);
            Assert::AreEqual(std::string("Type1"), order.OrderType);
            Assert::AreEqual(std::string("Param1"), order.OrderParameters);
        }

        TEST_METHOD(DecodeEmptyJson)
        {
            // Arrange
            std::string emptyJson = "";

            // Act
            Order order = OrderDecoder::DecodeOrder(emptyJson);

            // Assert
            Assert::AreEqual(-1, order.OrderId);
            Assert::AreEqual(std::string("Error"), order.SenderModule);
            Assert::AreEqual(std::string("Error"), order.RecipientModule);
            Assert::AreEqual(std::string("JSON_Error"), order.OrderType);
            Assert::AreEqual(std::string("JSON is Empty"), order.OrderParameters);
        }

        TEST_METHOD(DecodeMalformedJson)
        {
            // Arrange
            std::string malformedJson = "{invalid:}";

            // Act
            Order order = OrderDecoder::DecodeOrder(malformedJson);

            // Assert
            Assert::AreEqual(-1, order.OrderId);
            Assert::AreEqual(std::string("Error"), order.SenderModule);
            Assert::AreEqual(std::string("Error"), order.RecipientModule);
            Assert::AreEqual(std::string("JSON_Error"), order.OrderType);
            Assert::AreEqual(std::string("Malformed JSON content"), order.OrderParameters);
        }

        TEST_METHOD(DecodeJsonWithInvalidStructure)
        {
            // Arrange
            std::string invalidStructureJson = R"({"InvalidField": "Value"})";

            // Act
            Order order = OrderDecoder::DecodeOrder(invalidStructureJson);

            // Assert
            Assert::AreEqual(-1, order.OrderId); // Assuming validation fails if required fields are missing
            Assert::AreEqual(std::string("Error"), order.SenderModule);
            Assert::AreEqual(std::string("Error"), order.RecipientModule);
            Assert::AreEqual(std::string("JSON_Error"), order.OrderType);
            // Assuming the error message for a JSON structure that does not meet the required structure
            Assert::AreEqual(std::string("Malformed JSON content"), order.OrderParameters);
        }

        TEST_METHOD(DecodeOrderWithArrayInParameters_ShouldBeMalformed)
        {
            // Arrange
            std::string jsonWithArrayParameters = R"({
                                              "OrderId": 125,
                                              "SenderModule": "ModuleC",
                                              "RecipientModule": "ModuleD",
                                              "OrderType": "Type3",
                                              "OrderParameters": ["Param1", "Param2"]
                                            })";

            // Act
            Order order = OrderDecoder::DecodeOrder(jsonWithArrayParameters);

            // Assert
            Assert::AreEqual(-1, order.OrderId);
            Assert::AreEqual(std::string("Error"), order.SenderModule);
            Assert::AreEqual(std::string("Error"), order.RecipientModule);
            Assert::AreEqual(std::string("JSON_Error"), order.OrderType);
            Assert::AreEqual(std::string("Malformed JSON content"), order.OrderParameters);
        }


        TEST_METHOD(DecodeOrderWithNestedObjectInParameters_ShouldBeMalformed)
        {
            // Arrange
            std::string jsonWithNestedObject = R"({
                                          "OrderId": 124,
                                          "SenderModule": "ModuleA",
                                          "RecipientModule": "ModuleB",
                                          "OrderType": "Type2",
                                          "OrderParameters": {"NestedKey": "NestedValue"}
                                        })";

            // Act
            Order order = OrderDecoder::DecodeOrder(jsonWithNestedObject);

            // Assert
            Assert::AreEqual(-1, order.OrderId);
            Assert::AreEqual(std::string("Error"), order.SenderModule);
            Assert::AreEqual(std::string("Error"), order.RecipientModule);
            Assert::AreEqual(std::string("JSON_Error"), order.OrderType);
            Assert::AreEqual(std::string("Malformed JSON content"), order.OrderParameters);
        }

        TEST_METHOD(DecodeOrderWithMissingOrderId)
        {
            // Arrange
            std::string jsonMissingOrderId = R"({
                                                "SenderModule": "ModuleE",
                                                "RecipientModule": "ModuleF",
                                                "OrderType": "Type4",
                                                "OrderParameters": "Param3"
                                                })";

            // Act
            Order order = OrderDecoder::DecodeOrder(jsonMissingOrderId);

            // Assert
            // Assuming an order with a missing `OrderId` is treated as an error.
            Assert::AreEqual(-1, order.OrderId);
            Assert::AreEqual(std::string("Error"), order.SenderModule);
            Assert::AreEqual(std::string("Error"), order.RecipientModule);
            Assert::AreEqual(std::string("JSON_Error"), order.OrderType);
            Assert::IsTrue(order.OrderParameters.find("Malformed JSON content") != std::string::npos);
        }

        TEST_METHOD(DecodeOrderWithNullFields)
        {
            // Arrange
            std::string jsonWithNullFields = R"({
                                                "OrderId": null,
                                                "SenderModule": null,
                                                "RecipientModule": null,
                                                "OrderType": null,
                                                "OrderParameters": null
                                                })";

            // Act
            Order order = OrderDecoder::DecodeOrder(jsonWithNullFields);

            // Assert
            Assert::AreEqual(-1, order.OrderId); 
            Assert::AreEqual(std::string("Error"), order.SenderModule); 
            Assert::AreEqual(std::string("Error"), order.RecipientModule); 
            Assert::AreEqual(std::string("JSON_Error"), order.OrderType); 
            Assert::AreEqual(std::string("Malformed JSON content"), order.OrderParameters);
        }
    };
}