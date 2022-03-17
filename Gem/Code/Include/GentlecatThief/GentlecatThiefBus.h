
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace GentlecatThief
{
    class GentlecatThiefRequests
    {
    public:
        AZ_RTTI(GentlecatThiefRequests, "{f1d5f18b-4521-467b-a541-1a50e69e56bf}");
        virtual ~GentlecatThiefRequests() = default;

        //! Trigger the game play to begin
        virtual void PlayGame() = 0;

        //! Trigger the collection of a yarn ball
        virtual void CollectYarnBall() = 0;
    };

    class GentlecatThiefBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using GentlecatThiefRequestBus = AZ::EBus<GentlecatThiefRequests, GentlecatThiefBusTraits>;
    using GentlecatThiefInterface = AZ::Interface<GentlecatThiefRequests>;

    //! Game notifications
    class GentlecatThiefNotifications
        : public AZ::EBusTraits
    {
    public:
        //! The game has started (user has pressed "Play")
        virtual void OnGameStarted() {}

        //! A yarn ball has been collected
        virtual void OnYarnBallCollected() {}
    };

    using GentlecatThiefNotificationBus = AZ::EBus<GentlecatThiefNotifications>;

} // namespace GentlecatThief
