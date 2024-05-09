#pragma once

#include "MainManager.h"

#include "..\OrderStore\OrderReception.h"
#include "..\OrderStore\OrderStorage.h"
#include "InternalOrdersCourier.h"

#include "ExternalModulesManager.h"
#include "OrderDistributionHub.h"



class MainManager {
    public:

        MainManager();

        void ConstructMiddleware(std::string middlewareName,
                                 std::vector<std::shared_ptr<OrderHandler>>& orderHandlers,
                                 std::vector<std::shared_ptr<IExternalModuleCommunicator>>& externalModuleCommunicators,
                                 std::shared_ptr<IOrderReception> orderReception,
                                 std::shared_ptr<IOrderStorage> orderStorage_ParentModule);

        bool Initialise();

        std::queue<std::string> GetParentModuleOrders();

        bool SetOrder(std::string order);

    private:

        std::shared_ptr<IOrderStorage> _orderStorage_ParentModule;
        std::shared_ptr<IOrderStorage> _orderStorage_Middleware;
        std::shared_ptr<IOrderReception> _orderReception;
        std::shared_ptr<IExternalModulesManager> _externalModulesManager;
        std::shared_ptr<OrderDistributionHub> _orderDistributionHub;
        std::shared_ptr<IInternalOrdersCourier> _internalOrdersCourier;

        void registerOrderHandlers(std::vector<std::shared_ptr<OrderHandler>>& orderHandlers);
        void addExternalModuleCommunicators(std::vector<std::shared_ptr<IExternalModuleCommunicator>>& externalModuleCommunicators);
        void startOrderDistribution();
        
};

