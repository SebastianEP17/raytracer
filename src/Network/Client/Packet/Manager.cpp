#include "Network/Client/Packet/Handlers/Ping.hpp"
#include "Network/Client/Packet/Handlers/Kiss.hpp"
#include "Network/Client/Packet/Handlers/NvmStop.hpp"
#include "Network/Client/Packet/Handlers/Workslave.hpp"
#include "Network/Client/Packet/IHandler.hpp"

#include "Network/Packet/Packet.hpp"

#include "Manager.hpp"
#include "logger/Logger.hpp"

namespace raytracer::network::packet::client
{

    Manager::Manager
    ()
    {
        this->registerHandlers();
    }

    void
    Manager::dispatchPacket
    (
        const Packet &packet,
        app::Client &cli
    )
        const
    {
        LOG_DEBUG("Received Packet " + Packet::fromTypeToString(packet.getType()) + "`");

        const IHandler *handler = this->getHandler(packet.getType());

        if (!handler) {
            LOG_DEBUG("No handler has been registered for this kind of Packet. Ignoring.");
            return; // TODO: Throw exception?
        }

        handler->handle(packet, cli);
    }

    void
    Manager::registerHandlers
    ()
    {
        this->registerHandler(std::make_unique<handler::Ping>());
        this->registerHandler(std::make_unique<handler::Kiss>());
        this->registerHandler(std::make_unique<handler::NvmStop>());
        this->registerHandler(std::make_unique<handler::Workslave>());
    }

    void
    Manager::registerHandler
    (
        std::unique_ptr<IHandler> handler
    )
    {
        const Type trigger = handler->getTrigger();

        this->_handlers.insert({
            trigger,
            std::move(handler)
        });

        LOG_DEBUG(
            "(PacketManager) Registered Packet handler " +
            Packet::fromTypeToString(trigger)
        );
    }

    IHandler *
    Manager::getHandler
    (
        const Type type
    )
        const
    {
        if (!this->_handlers.contains(type)) {
            return nullptr;
        }

        return this->_handlers.at(type).get();
    }

}
