
#pragma once

#include <AzCore/Component/Component.h>

#include <GentlecatThief/GentlecatThiefBus.h>

namespace GentlecatThief
{
    class GentlecatThiefSystemComponent
        : public AZ::Component
        , protected GentlecatThiefRequestBus::Handler
    {
    public:
        AZ_COMPONENT(GentlecatThiefSystemComponent, "{fec72f46-464a-4892-a8a3-7a43b65e8086}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        GentlecatThiefSystemComponent();
        ~GentlecatThiefSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // GentlecatThiefRequestBus interface implementation
        void PlayGame() override;
        void CollectYarnBall() override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
