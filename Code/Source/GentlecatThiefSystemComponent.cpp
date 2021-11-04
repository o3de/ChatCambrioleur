
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>
#include <AzCore/RTTI/BehaviorContext.h>

#include "GentlecatThiefSystemComponent.h"

namespace GentlecatThief
{
    namespace Internal
    {
        struct GentlecatThiefNotificationBusHandler final
            : public GentlecatThiefNotificationBus::Handler
            , public AZ::BehaviorEBusHandler
        {
            AZ_EBUS_BEHAVIOR_BINDER(GentlecatThiefNotificationBusHandler, "{7CC8F936-8C4A-46A6-9C57-09F0415BF1BF}", AZ::SystemAllocator,
                OnGameStarted, OnYarnBallCollected);

            void OnGameStarted() override
            {
                Call(FN_OnGameStarted);
            }

            void OnYarnBallCollected() override
            {
                Call(FN_OnYarnBallCollected);
            }
        };
    }

    void GentlecatThiefSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<GentlecatThiefSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<GentlecatThiefSystemComponent>("GentlecatThief", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }

        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->EBus<GentlecatThiefRequestBus>("GentlecatThiefRequestBus")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Event("PlayGame", &GentlecatThiefRequests::PlayGame)
                ->Event("CollectYarnBall", &GentlecatThiefRequests::CollectYarnBall)
                ;

            behaviorContext->EBus<GentlecatThiefNotificationBus>("GentlecatThiefNotificationBus")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Handler<Internal::GentlecatThiefNotificationBusHandler>()
                ->Event("OnGameStarted", &GentlecatThiefNotifications::OnGameStarted)
                ->Event("OnYarnBallCollected", &GentlecatThiefNotifications::OnYarnBallCollected)
                ;
        }
    }

    void GentlecatThiefSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("GentlecatThiefService"));
    }

    void GentlecatThiefSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("GentlecatThiefService"));
    }

    void GentlecatThiefSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void GentlecatThiefSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }
    
    GentlecatThiefSystemComponent::GentlecatThiefSystemComponent()
    {
        if (GentlecatThiefInterface::Get() == nullptr)
        {
            GentlecatThiefInterface::Register(this);
        }
    }

    GentlecatThiefSystemComponent::~GentlecatThiefSystemComponent()
    {
        if (GentlecatThiefInterface::Get() == this)
        {
            GentlecatThiefInterface::Unregister(this);
        }
    }

    void GentlecatThiefSystemComponent::PlayGame()
    {
        GentlecatThiefNotificationBus::Broadcast(&GentlecatThiefNotifications::OnGameStarted);
    }

    void GentlecatThiefSystemComponent::CollectYarnBall()
    {
        GentlecatThiefNotificationBus::Broadcast(&GentlecatThiefNotifications::OnYarnBallCollected);
    }

    void GentlecatThiefSystemComponent::Init()
    {
    }

    void GentlecatThiefSystemComponent::Activate()
    {
        GentlecatThiefRequestBus::Handler::BusConnect();
    }

    void GentlecatThiefSystemComponent::Deactivate()
    {
        GentlecatThiefRequestBus::Handler::BusDisconnect();
    }
}
