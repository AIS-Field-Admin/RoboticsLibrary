#include "CppUnitTest.h"
#include <map>
#include <string>

#include "..\OrderStore\Order.h"
#include "..\OrderStore\OrderWrapper.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OrderWrapperTests
{
    TEST_CLASS(OrderWrapperTests)
    {
        public:
            TEST_METHOD(TestPrepareAndSerializeOrder) 
            {
                Order order;
                order.OrderId = 1;
                order.SenderModule = "ModuleA";
                order.RecipientModule = "ModuleB";
                order.OrderType = "TypeX";

                std::map<std::string, std::string> parameters = { {"key", "value"} };
                order.OrderParameters = OrderWrapper::PrepareOrderParameters(parameters);

                nlohmann::json expectedJson;

                expectedJson["OrderId"] = order.OrderId;
                expectedJson["SenderModule"] = order.SenderModule;
                expectedJson["RecipientModule"] = order.RecipientModule;
                expectedJson["OrderType"] = order.OrderType;
                expectedJson["OrderParameters"] = order.OrderParameters;

                std::string expectedJsonString = expectedJson.dump(); 

                std::string result = OrderWrapper::SerializeOrder(order);

                Assert::AreEqual(expectedJsonString, result);  
            }
    };
}

