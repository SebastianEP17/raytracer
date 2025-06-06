#pragma once

#include "Network/Client/Packet/IHandler.hpp"

namespace raytracer::network::packet::client::handler
{

    class Kiss final
        : public IHandler
    {
    public:
        void handle(
            const Packet &packet,
            app::Client &cli
        ) const override;

        [[nodiscard]] Type getTrigger()
            const override
        {
            return Type::KISS;
        }
    };

}
